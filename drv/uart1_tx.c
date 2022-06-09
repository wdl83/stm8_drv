#include <stddef.h>

#include "uart1_tx.h"

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

const char *uart1_send_str(const char *str)
{
    return uart1_send_str_r(str, NULL);
}

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
