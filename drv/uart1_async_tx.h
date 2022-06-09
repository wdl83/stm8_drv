#pragma once

#include <stdint.h>

#include "uart1.h"

typedef
void (*uart_tx_complete_cb_t)(uintptr_t);

void uart1_async_send(
    const uint8_t *begin, const uint8_t *end, uart_tx_complete_cb_t, uintptr_t);

void uart1_tx_irq(void) __interrupt(IRQ_NO_UART1_TX);
