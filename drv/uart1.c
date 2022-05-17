#include <string.h>

//#include <drv/assert.h>
#include <drv/uart1.h>
//#include <drv/util.h>

/*----------------------------------------------------------------------------*/
#ifdef UART_DBG_CNTRS
void uart_cntrs_str(uart_cntrs_str_t str, const uart_cntrs_t *cntrs)
{
    if(
        NULL == str
        || NULL == cntrs) return;

    str = xprint8(str, cntrs->byte_cntr);
    str = xprint8(str, cntrs->int_cntr);
    *str++ = '\n';
    *str = '\0';
}
#endif /* UART_DBG_CNTRS */
/*----------------------------------------------------------------------------*/
void uart_rxflags_str(uart_rxflags_str_t str, const uart_rxflags_t *flags)
{
    if(
        NULL == str
        || NULL == flags) return;

    uint8_t i = 0;

    str[i++] = flags->parity_error ?  'P' : '-';
    str[i++] = flags->frame_error ? 'F' : '-';
    str[i++] = flags->overrun_error ? 'O' : '-';
    str[i++] = flags->aborted ? 'a' : '-';
    str[i++] = flags->full ? 'f' : '-';
    str[i++] = flags->empty ? 'e' : '-';
    str[i++] = '\n';
    str[i++] = '\0';
}
/*----------------------------------------------------------------------------*/
typedef struct
{
    const uint8_t *begin;
    const uint8_t *end;
    uart_tx_complete_cb_t complete_cb;
    uintptr_t user_data;
} tx_ctrl_t;

static
tx_ctrl_t tx0_;
#ifdef UART_DBG_CNTRS
static
uart_cntrs_t tx0_cntrs_;

uart_cntrs_t *uart1_tx_cntrs(void) {return &tx0_cntrs_;}
#endif /* UART_DBG_CNTRS */

/*----------------------------------------------------------------------------*/
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
rx_ctrl_t rx0_;
static
uart_rxflags_t rx0_flags_;
#ifdef UART_DBG_CNTRS
static
uart_cntrs_t rx0_cntrs_;

uart_cntrs_t *uart1_rx_cntrs(void) {return &rx0_cntrs_;}
#endif /* UART_DBG_CNTRS */
/*----------------------------------------------------------------------------*/
const char *uart1_send_str_r(const char *begin, const char *const end)
{
    if(NULL == begin) return begin;

//    UART1_TX_ENABLE();

    while(
        NULL == end && *begin != '\0'
        || NULL != end && begin != end)
    {
        /* wait for UART HW to be ready */
        while(!UART1_TX_READY()) {}
        UART1_TX(*begin);
        ++begin;
    }

    while(!UART1_TX_COMPLETE()) {}
//    UART1_TX_DISABLE();
    return begin;
}
/*----------------------------------------------------------------------------*/
const char *uart1_send_str(const char *str)
{
    return uart1_send_str_r(str, NULL);
}
/*----------------------------------------------------------------------------*/
char *uart1_recv_str(char *begin, const char *const end, char delimiter)
{
    if(
        NULL == begin
        || NULL == end) return begin;

    UART1_RX_ENABLE();

    while(begin != end)
    {
        /* wait for UART HW to be ready */
        while(!UART1_RX_READY()) {}
        UART1_RX(*begin);
        ++begin;

        /* special character received */
        if(*(begin - 1) == delimiter) break;
    }

    UART1_RX_DISABLE();

    return begin;
}
/*----------------------------------------------------------------------------*/
void uart1_send(const uint8_t *begin, const uint8_t *const end)
{
    if(
        NULL == begin
        || NULL == end
        || begin == end) return;

    UART1_TX_ENABLE();

    while(begin != end)
    {
        while(!UART1_TX_READY()) {}
        UART1_TX(*begin);
        ++begin;
    }

    while(!UART1_TX_COMPLETE()) {}
    UART1_TX_DISABLE();
}
/*----------------------------------------------------------------------------*/
void uart1_async_send(
        const uint8_t *begin, const uint8_t *end,
        uart_tx_complete_cb_t complete_cb,
        uintptr_t user_data)
{
    ASSERT(NULL != begin);
    ASSERT(NULL != end);
    ASSERT(end > begin);

    if(
        NULL == tx0_.begin
        && NULL == tx0_.end
        && NULL == tx0_.complete_cb
        && 0 == tx0_.user_data)
    {
        tx0_.begin = begin;
        tx0_.end = end;
        tx0_.complete_cb = complete_cb;
        tx0_.user_data = user_data;

        if(!UART1_TX_ENABLED()) UART1_TX_ENABLE();
        /* as soon as UDRE (UART Data Register Empty) interrupt is enabled
         * it will fire, so dont write data to UDR (data race) */
        UART1_TX_READY_INT_ENABLE();
    }
}
/*----------------------------------------------------------------------------*/
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
            NULL == rx0_.begin
            && NULL == rx0_.end
            && NULL == rx0_.next
            && NULL == rx0_.pred_cb
            && NULL == rx0_.complete_cb
            && 0 == rx0_.user_data)
    {
        rx0_.begin = begin;
        rx0_.end = end;
        rx0_.next = begin;
        rx0_.pred_cb = pred_cb;
        rx0_.complete_cb = complete_cb;
        rx0_.user_data = user_data;
        if(!UART1_RX_ENABLED()) UART1_RX_ENABLE();
        UART1_RX_INT_ENABLE();
    }
}
/*----------------------------------------------------------------------------*/
static
void rx_complete(void)
{
    if(
        NULL == rx0_.complete_cb
        /* there is no data in buffer */
        || rx0_.begin == rx0_.next) return;

    uint8_t *begin = rx0_.begin;
    const uint8_t *end = rx0_.next;
    uintptr_t user_data = rx0_.user_data;
    uart_rx_complete_cb_t complete_cb = rx0_.complete_cb;

    memset(&rx0_, 0, sizeof(rx_ctrl_t));

    (*complete_cb)(begin, end, &rx0_flags_, user_data);
}
/*----------------------------------------------------------------------------*/
void uart1_async_recv_complete(void) __critical
{
    UART1_RX_INT_DISABLE();
    rx_complete();
}
/*----------------------------------------------------------------------------*/
void uart1_async_recv_cb(
    uart_rx_recv_cb_t recv_cb,
    uintptr_t user_data)
{
    ASSERT(NULL != recv_cb);

    if(
        NULL == rx0_.begin
        && NULL == rx0_.end
        && NULL == rx0_.next
        && NULL == rx0_.pred_cb
        && NULL == rx0_.complete_cb
        && NULL == rx0_.recv_cb
        && 0 == rx0_.user_data)
    {
        rx0_.recv_cb = recv_cb;
        rx0_.user_data = user_data;
        if(!UART1_RX_ENABLED()) UART1_RX_ENABLE();
        UART1_RX_INT_ENABLE();
    }
}
/*----------------------------------------------------------------------------*/
static
void on_tx_ready(void)
{
    ASSERT(NULL != tx0_.begin);
    ASSERT(NULL != tx0_.end);

#ifdef UART_DBG_CNTRS
    ++tx0_cntrs_.int_cntr;
#endif /* UART_DBG_CNTRS */

    while(
        tx0_.begin != tx0_.end
        && UART1_TX_READY())
    {
        UART1_TX(*tx0_.begin);
        ++tx0_.begin;
#ifdef UART_DBG_CNTRS
        ++tx0_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */
    }

    if(tx0_.begin == tx0_.end)
    {
        UART1_TX_READY_INT_DISABLE();
        UART1_TX_COMPLETE_INT_ENABLE();
    }
}

static
void on_tx_complete(void)
{
    ASSERT(NULL != tx0_.begin);
    ASSERT(NULL != tx0_.end);
    ASSERT(NULL != tx0_.complete_cb);
    ASSERT(tx0_.begin == tx0_.end);

    UART1_TX_COMPLETE_INT_DISABLE();

    uart_tx_complete_cb_t complete_cb = tx0_.complete_cb;
    uintptr_t user_data = tx0_.user_data;

    memset(&tx0_, 0, sizeof(tx_ctrl_t));

    if(NULL != complete_cb) (*complete_cb)(user_data);
}

static
void uart1_tx_irq(void) __interrupt(IRQ_NO_UART1_TX)
{
    if(UART1_TX_COMPLETE()) on_tx_complete();
    on_tx_ready();
}
/*----------------------------------------------------------------------------*/
#ifdef UART1_RX_NO_BUFFERING

static
void on_rx_ready(void)
{
#ifdef UART_DBG_CNTRS
    ++rx0_cntrs_.int_cntr;
#endif /* UART_DBG_CNTRS */
    /*------------------------------------------------------------------------*/
    /* non-buffering continuous async mode */
    ASSERT(NULL == rx0_.end);
    ASSERT(NULL == rx0_.next);
    ASSERT(NULL == rx0_.pred_cb);
    ASSERT(NULL == rx0_.complete_cb);
    ASSERT(NULL != rx0_.recv_cb);

#ifdef UART_DBG_CNTRS
        ++rx0_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */

        rx0_flags_.fop_errors = UART1_FOP_ERRORS();
        (*rx0_.recv_cb)(UART1_RD(), rx0_flags_, rx0_.user_data);
}

#else  /* UART1_RX_NO_BUFFERING */

static
void on_rx_ready(void)
{
#ifdef UART_DBG_CNTRS
    ++rx0_cntrs_.int_cntr;
#endif /* UART_DBG_CNTRS */
    /*------------------------------------------------------------------------*/
    /* non-buffering continuous async mode */
    if(NULL != rx0_.recv_cb)
    {
        ASSERT(NULL == rx0_.end);
        ASSERT(NULL == rx0_.next);
        ASSERT(NULL == rx0_.pred_cb);
        ASSERT(NULL == rx0_.complete_cb);
        ASSERT(NULL != rx0_.recv_cb);

#ifdef UART_DBG_CNTRS
        ++rx0_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */

        rx0_flags_.fop_errors = UART1_FOPN_ERRORS();
        (*rx0_.recv_cb)(UART1_RD(), &rx0_flags_, rx0_.user_data);
        return;
    }
    /*------------------------------------------------------------------------*/

    /* buffer can not be full on entry to ISR - otherwise
     * data will be lost */
    ASSERT(rx0_.next != rx0_.end);

    while(
        rx0_.next != rx0_.end
        && UART1_RX_READY())
    {
        rx0_flags_.fop_errors = UART1_FOPN_ERRORS();

        UART1_RX(*rx0_.next);
#ifdef UART_DBG_CNTRS
        ++rx0_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */
        ++rx0_.next;

        if(
            NULL != rx0_.pred_cb
            && (*rx0_.pred_cb)(rx0_.next - 1, rx0_.user_data))
        {
            rx0_flags_.aborted = 1;
            break;
        }
    }

	rx0_flags_.full = rx0_.next == rx0_.end;
	rx0_flags_.empty = !UART1_RX_READY();

    if(
		rx0_flags_.full
		|| rx0_flags_.aborted)
    {
        UART1_RX_INT_DISABLE();
        rx_complete();
    }
}
#endif /* UART1_RX_NO_BUFFERING */

static
void uart1_rx_irq(void) __interrupt(IRQ_NO_UART1_RX)
{
    on_rx_ready();
}
/*----------------------------------------------------------------------------*/
