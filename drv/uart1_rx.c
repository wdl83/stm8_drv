#include <stddef.h>

#include "uart1_rx.h"

char *uart1_recv_str(char *begin, const char *const end, char delimiter)
{
    if(NULL == begin || NULL == end) return begin;

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
