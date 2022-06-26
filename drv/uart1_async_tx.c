#include <string.h>

#include "uart1_async_tx.h"
#ifdef UART_DBG_CNTRS
#include "uart1_dbg.h"
#endif

typedef struct
{
    const uint8_t *begin;
    const uint8_t *end;
    uart_tx_complete_cb_t complete_cb;
    uintptr_t user_data;
} tx_ctrl_t;

tx_ctrl_t tx1_;

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

static
void on_tx_ready(void)
{
    ASSERT(NULL != tx1_.begin);
    ASSERT(NULL != tx1_.end);

#ifdef UART_DBG_CNTRS
    ++uart1_tx_cntrs()->bits.int_cntr;
#endif /* UART_DBG_CNTRS */

    while(
        tx1_.begin != tx1_.end
        && UART1_TX_READY())
    {
        UART1_TX(*tx1_.begin);
        ++tx1_.begin;
#ifdef UART_DBG_CNTRS
        ++uart1_tx_cntrs()->bits.byte_cntr;
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
