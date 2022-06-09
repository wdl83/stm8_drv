#include <stddef.h>
#include <string.h>

#include "uart1_async_rx.h"
#ifdef UART_DBG_CNTRS
#include "uart1_dbg.h"
#endif

typedef struct
{
    uint8_t *begin;
    const uint8_t *end;
    uint8_t *next;
    uart_rx_pred_cb_t pred_cb;
    uart_rx_complete_cb_t complete_cb;
    uart_rx_recv_cb_t recv_cb;
    uintptr_t user_data;
} rx_ctrl_t;

static
rx_ctrl_t rx1_;
static
uart_rxflags_t rx1_flags_;

void uart1_async_recv(
        uint8_t *begin, const uint8_t *end,
        uart_rx_pred_cb_t pred_cb,
        uart_rx_complete_cb_t complete_cb,
        uintptr_t user_data)
{
    ASSERT(NULL != begin);
    ASSERT(NULL != end);
    ASSERT(end > begin);
    ASSERT(NULL != complete_cb);

    if(
            NULL == rx1_.begin
            && NULL == rx1_.end
            && NULL == rx1_.next
            && NULL == rx1_.pred_cb
            && NULL == rx1_.complete_cb
            && 0 == rx1_.user_data)
    {
        rx1_.begin = begin;
        rx1_.end = end;
        rx1_.next = begin;
        rx1_.pred_cb = pred_cb;
        rx1_.complete_cb = complete_cb;
        rx1_.user_data = user_data;
        if(!UART1_RX_ENABLED()) UART1_RX_ENABLE();
        UART1_RX_INT_ENABLE();
    }
}

static
void rx_complete(void)
{
    if(
        NULL == rx1_.complete_cb
        /* there is no data in buffer */
        || rx1_.begin == rx1_.next) return;

    uint8_t *begin = rx1_.begin;
    const uint8_t *end = rx1_.next;
    uintptr_t user_data = rx1_.user_data;
    uart_rx_complete_cb_t complete_cb = rx1_.complete_cb;

    memset(&rx1_, 0, sizeof(rx_ctrl_t));

    (*complete_cb)(begin, end, &rx1_flags_, user_data);
}

void uart1_async_recv_complete(void)
{
    UART1_RX_INT_DISABLE();
    rx_complete();
}

void uart1_async_recv_cb(
    uart_rx_recv_cb_t recv_cb,
    uintptr_t user_data)
{
    ASSERT(NULL != recv_cb);

    if(
        NULL == rx1_.begin
        && NULL == rx1_.end
        && NULL == rx1_.next
        && NULL == rx1_.pred_cb
        && NULL == rx1_.complete_cb
        && NULL == rx1_.recv_cb
        && 0 == rx1_.user_data)
    {
        rx1_.recv_cb = recv_cb;
        rx1_.user_data = user_data;
        if(!UART1_RX_ENABLED()) UART1_RX_ENABLE();
        UART1_RX_INT_ENABLE();
    }
}

#ifdef UART1_RX_NO_BUFFERING

void uart1_rx_irq(void) __interrupt(IRQ_NO_UART1_RX)
{
#ifdef UART_DBG_CNTRS
    ++uart1_rx_cntrs()->bits.int_cntr;
#endif /* UART_DBG_CNTRS */
    /* non-buffering continuous async mode */
    ASSERT(NULL == rx1_.end);
    ASSERT(NULL == rx1_.next);
    ASSERT(NULL == rx1_.pred_cb);
    ASSERT(NULL == rx1_.complete_cb);
    ASSERT(NULL != rx1_.recv_cb);

#ifdef UART_DBG_CNTRS
    ++uart1_rx_cntrs()->bits.byte_cntr;
#endif /* UART_DBG_CNTRS */
    rx1_flags_.errors.fopn = UART1_FOPN_ERRORS();
    (*rx1_.recv_cb)(UART1_RD(), &rx1_flags_, rx1_.user_data);
}

#else  /* UART1_RX_NO_BUFFERING */

void uart1_rx_irq(void) __interrupt(IRQ_NO_UART1_RX)
{
#ifdef UART_DBG_CNTRS
    ++uart1_rx_cntrs()->bits.int_cntr;
#endif /* UART_DBG_CNTRS */
    /* non-buffering continuous async mode */
    if(NULL != rx1_.recv_cb)
    {
        ASSERT(NULL == rx1_.end);
        ASSERT(NULL == rx1_.next);
        ASSERT(NULL == rx1_.pred_cb);
        ASSERT(NULL == rx1_.complete_cb);

#ifdef UART_DBG_CNTRS
        ++uart1_rx_cntrs()->bits.byte_cntr;
#endif /* UART_DBG_CNTRS */

        rx1_flags_.errors.fopn = UART1_FOPN_ERRORS();
        (*rx1_.recv_cb)(UART1_RD(), &rx1_flags_, rx1_.user_data);
        return;
    }
    /* buffer can not be full on entry to ISR - otherwise
     * data will be lost */
    ASSERT(rx1_.next != rx1_.end);

    while(
        rx1_.next != rx1_.end
        && UART1_RX_READY())
    {
        rx1_flags_.errors.fopn = UART1_FOPN_ERRORS();
        UART1_RX(*rx1_.next);
#ifdef UART_DBG_CNTRS
        ++uart1_rx_cntrs()->bits.byte_cntr;
#endif /* UART_DBG_CNTRS */
        ++rx1_.next;

        if(
            NULL != rx1_.pred_cb
            && (*rx1_.pred_cb)(rx1_.next - 1, rx1_.user_data))
        {
            rx1_flags_.bits.aborted = 1;
            break;
        }
    }

	rx1_flags_.bits.full = rx1_.next == rx1_.end;
	rx1_flags_.bits.empty = !UART1_RX_READY();

    if(
		rx1_flags_.bits.full
		|| rx1_flags_.bits.aborted)
    {
        UART1_RX_INT_DISABLE();
        rx_complete();
    }
}

#endif /* UART1_RX_NO_BUFFERING */
