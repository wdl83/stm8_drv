#pragma once

#include <stddef.h>
#include <stdint.h>

#ifndef UART_DBG_CNTRS
#error "Please define UART_DBG_CNTRS"
#endif

#include "uart1_async_rx.h"

typedef union
{
    struct
    {
        uint8_t byte_cntr : 8;
        uint8_t int_cntr : 8;
    }   bits;
    uint16_t value;
} uart_cntrs_t;

typedef
    char uart_cntrs_str_t[
        2 /* ?? : byte counter */ +
        2 /* ?? : interrupt counter */ +
        2 /* \n\0 */];

uart_cntrs_t *uart1_tx_cntrs(void);
uart_cntrs_t *uart1_rx_cntrs(void);
void uart_cntrs_str(uart_cntrs_str_t, const uart_cntrs_t *);



typedef
    char uart_txflags_str_t[
        1 /* \n */ +
        2 /* ?? : byte counter */ +
        2 /* ?? : interrupt counter */ +
        2 /* \n\0 */];

typedef
    char uart_rxflags_str_t[
        1 /* O  : overrun error */ +
        1 /* N  : noise flag */ +
        1 /* F  : frame error */ +
        1 /* P  : parity error */ +
        1 /* a  : aborted */ +
        1 /* f  : full */ +
        1 /* e  : empty */ +
        1 /* \0 */];

void uart_rxflags_str(uart_rxflags_str_t, const uart_rxflags_t *);
