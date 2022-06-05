#include <string.h>

#include <drv/uart1.h>

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

    str[i++] = flags->bits.overrun_error ? 'O' : '-';
    str[i++] = flags->bits.noise_flag ? 'N' : '-';
    str[i++] = flags->bits.frame_error ? 'F' : '-';
    str[i++] = flags->bits.parity_error ?  'P' : '-';
    str[i++] = flags->bits.aborted ? 'a' : '-';
    str[i++] = flags->bits.full ? 'f' : '-';
    str[i++] = flags->bits.empty ? 'e' : '-';
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
tx_ctrl_t tx1_;
#ifdef UART_DBG_CNTRS
static
uart_cntrs_t tx1_cntrs_;

uart_cntrs_t *uart1_tx_cntrs(void) {return &tx1_cntrs_;}
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
rx_ctrl_t rx1_;
static
uart_rxflags_t rx1_flags_;
#ifdef UART_DBG_CNTRS
static
uart_cntrs_t rx1_cntrs_;

uart_cntrs_t *uart1_rx_cntrs(void) {return &rx1_cntrs_;}
#endif /* UART_DBG_CNTRS */
/*----------------------------------------------------------------------------*/
const char *uart1_send_str_r(const char *begin, const char *const end)
{
    if(NULL == begin) return begin;

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
        NULL == tx1_.begin
        && NULL == tx1_.end
        && NULL == tx1_.complete_cb
        && 0 == tx1_.user_data)
    {
        tx1_.begin = begin;
        tx1_.end = end;
        tx1_.complete_cb = complete_cb;
        tx1_.user_data = user_data;

        if(!UART1_TX_ENABLED()) UART1_TX_ENABLE();
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
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
void uart1_async_recv_complete(void)
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
/*----------------------------------------------------------------------------*/
static
void on_tx_ready(void)
{
    ASSERT(NULL != tx1_.begin);
    ASSERT(NULL != tx1_.end);

#ifdef UART_DBG_CNTRS
    ++tx1_cntrs_.int_cntr;
#endif /* UART_DBG_CNTRS */

    while(
        tx1_.begin != tx1_.end
        && UART1_TX_READY())
    {
        UART1_TX(*tx1_.begin);
        ++tx1_.begin;
#ifdef UART_DBG_CNTRS
        ++tx1_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */
    }

    if(tx1_.begin == tx1_.end)
    {
        UART1_TX_READY_INT_DISABLE();
        UART1_TX_COMPLETE_INT_ENABLE();
    }
}

static
void on_tx_complete(void)
{
    ASSERT(NULL != tx1_.begin);
    ASSERT(NULL != tx1_.end);
    ASSERT(NULL != tx1_.complete_cb);
    ASSERT(tx1_.begin == tx1_.end);

    UART1_TX_COMPLETE_INT_DISABLE();

    uart_tx_complete_cb_t complete_cb = tx1_.complete_cb;
    uintptr_t user_data = tx1_.user_data;

    memset(&tx1_, 0, sizeof(tx_ctrl_t));

    if(NULL != complete_cb) (*complete_cb)(user_data);
}

void uart1_tx_irq(void) __interrupt(IRQ_NO_UART1_TX)
{
    if(UART1_TX_COMPLETE_INT_ENABLED() && UART1_TX_COMPLETE()) on_tx_complete();
    else on_tx_ready();
}
/*----------------------------------------------------------------------------*/
#ifdef UART1_RX_NO_BUFFERING

void uart1_rx_irq(void) __interrupt(IRQ_NO_UART1_RX)
{
#ifdef UART_DBG_CNTRS
    ++rx1_cntrs_.int_cntr;
#endif /* UART_DBG_CNTRS */
    /*------------------------------------------------------------------------*/
    /* non-buffering continuous async mode */
    ASSERT(NULL == rx1_.end);
    ASSERT(NULL == rx1_.next);
    ASSERT(NULL == rx1_.pred_cb);
    ASSERT(NULL == rx1_.complete_cb);
    ASSERT(NULL != rx1_.recv_cb);

#ifdef UART_DBG_CNTRS
        ++rx1_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */

        rx1_flags_.errors.fopn = UART1_FOPN_ERRORS();
        (*rx1_.recv_cb)(UART1_RD(), &rx1_flags_, rx1_.user_data);
}

#else  /* UART1_RX_NO_BUFFERING */

void uart1_rx_irq(void) __interrupt(IRQ_NO_UART1_RX)
{
#ifdef UART_DBG_CNTRS
    ++rx1_cntrs_.int_cntr;
#endif /* UART_DBG_CNTRS */
    /*------------------------------------------------------------------------*/
    /* non-buffering continuous async mode */
    if(NULL != rx1_.recv_cb)
    {
        ASSERT(NULL == rx1_.end);
        ASSERT(NULL == rx1_.next);
        ASSERT(NULL == rx1_.pred_cb);
        ASSERT(NULL == rx1_.complete_cb);
        ASSERT(NULL != rx1_.recv_cb);

#ifdef UART_DBG_CNTRS
        ++rx1_cntrs_.byte_cntr;
#endif /* UART_DBG_CNTRS */

        rx1_flags_.errors.fopn = UART1_FOPN_ERRORS();
        (*rx1_.recv_cb)(UART1_RD(), &rx1_flags_, rx1_.user_data);
        return;
    }
    /*------------------------------------------------------------------------*/

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
        ++rx1_cntrs_.byte_cntr;
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
/*----------------------------------------------------------------------------*/
