#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "uart1.h"

typedef union
{
    struct
    {
        uint8_t aborted : 1;
        uint8_t full : 1;
        uint8_t empty : 1;
        uint8_t reserved : 1;
        uint8_t overrun_error : 1;
        uint8_t noise_flag : 1;
        uint8_t frame_error : 1;
        uint8_t parity_error : 1;
    } bits;

    struct
    {
        uint8_t : 4;
        uint8_t fopn : 4;
    } errors;

    uint8_t value;
} uart_rxflags_t;

typedef
bool (*uart_rx_pred_cb_t)(const uint8_t *curr, uintptr_t);

typedef
void (*uart_rx_complete_cb_t)(
    uint8_t *begin, const uint8_t *end, uart_rxflags_t *, uintptr_t user_data);

typedef
void (*uart_rx_recv_cb_t)(uint8_t data, uart_rxflags_t *, uintptr_t user_data);


void uart1_async_recv(
    uint8_t *begin, const uint8_t *end, uart_rx_pred_cb_t, uart_rx_complete_cb_t, uintptr_t);

void uart1_async_recv_complete(void);
/* non-buffering continuous async mode */
void uart1_async_recv_cb( uart_rx_recv_cb_t recv_cb, uintptr_t user_data);
void uart1_rx_irq(void) __interrupt(IRQ_NO_UART1_RX);
