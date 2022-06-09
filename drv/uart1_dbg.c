#include "uart1_dbg.h"
#include "util.h"

void uart_cntrs_str(uart_cntrs_str_t str, const uart_cntrs_t *cntrs)
{
    if(
        NULL == str
        || NULL == cntrs) return;

    str = xprint8(str, cntrs->bits.byte_cntr);
    str = xprint8(str, cntrs->bits.int_cntr);
    *str++ = '\n';
    *str = '\0';
}

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

static
uart_cntrs_t tx1_cntrs_;

uart_cntrs_t *uart1_tx_cntrs(void) {return &tx1_cntrs_;}


static
uart_cntrs_t rx1_cntrs_;

uart_cntrs_t *uart1_rx_cntrs(void) {return &rx1_cntrs_;}
