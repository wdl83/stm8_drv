#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "mem.h"
#include "stm8_uart1.h"

/*----------------------------------------------------------------------------*/
#define UART1_TX_ENABLE() UART1_CR2 |= M1(TEN)
#define UART1_TX_DISABLE() UART1_CR2 &= ~M1(TEN)
#define UART1_TX_ENABLED() (UART1_CR2 & M1(TEN))

#define UART1_RX_ENABLE() UART1_CR2 |= M1( REN)
#define UART1_RX_DISABLE() UART1_CR2 &= ~M1( REN)
#define UART1_RX_ENABLED() (UART1_CR2 & M1(REN))

#define CALC_BR(cpu_clk, bps) ((cpu_clk) / (bps))

#define UART1_BR(br) \
      UART1_BRR1 =  \
      ((uint8_t)((UINT16_C(0x0FF0) & (br)) >> 4)), \
      UART1_BRR2 = \
      ((uint8_t)((UINT16_C(0xF000) & (br)) >> 12)) \
       | ((uint8_t)(UINT16_C(0x00F) & (br)))

#define UART1_TX_READY() (UART1_SR & M1(TXE))
#define UART1_TX_COMPLETE() (UART1_SR & M1(TC))

#define UART1_RX_READY() (UART1_SR & M1(RXNE))

#define UART1_IDLE() (UART1_SR & M1(IDLE))

#define UART1_TX(data) UART1_DR = (data)
#define UART1_RX(data) (data) = UART1_DR
#define UART1_RD() UART1_DR

#define UART1_TX_READY_INT_ENABLE() UART1_CR2 |= M1(TIEN)
#define UART1_TX_READY_INT_DISABLE() UART1_CR2 &= ~M1(TIEN)

#define UART1_TX_COMPLETE_INT_ENABLE() UART1_CR2 |= M1(TCIEN)
#define UART1_TX_COMPLETE_INT_DISABLE() UART1_CR2 &= ~M1(TCIEN)

#define UART1_RX_INT_ENABLE() UART1_CR2 |= M1(RIEN)
#define UART1_RX_INT_DISABLE() UART1_CR2 &= ~M1(RIEN)

#define UART1_PARITY_EVEN() UART1_CR1 &= ~M1(PS), UART1_CR1 |= M2(M, PCEN)
#define UART1_PARITY_ODD() UART1_CR1 |= M2(PCEN, PS)

#define UART1_FRAME_ERROR() (UART1_SR & M1(FE))
#define UART1_OVERRUN_ERROR() (UART1_SR & M1(OR))
#define UART1_PARITY_ERROR() (UART1_SR & M1(PE))
#define UART1_NOISE_FLAG() (UART1_SR & M1(NF))

#define UART1_FOPN_ERRORS() (UART1_SR & M4(FE, OR, PE, NF))
/*----------------------------------------------------------------------------*/
#ifdef USART_DBG_CNTRS
typedef union
{
    struct
    {
        uint8_t byte_cntr : 8;
        uint8_t int_cntr : 8;
    };
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
#endif /* USART_DBG_CNTRS */
/*----------------------------------------------------------------------------*/

typedef union
{
    struct
    {
        uint8_t aborted : 1;
        uint8_t full : 1;
        uint8_t empty : 1;
        uint8_t : 1;
        uint8_t : 1;
        uint8_t frame_error : 1;
        uint8_t overrun_error : 1;
        uint8_t parity_error : 1;
    };

    struct
    {
        uint8_t : 4;
        uint8_t : 1;
        uint8_t fop_errors : 3;
    };

    uint8_t value;
} uart_rxflags_t;

typedef
    char uart_rxflags_str_t[
        1 /* P  : parity error */ +
        1 /* F  : frame error */ +
        1 /* O  : overrun error */ +
        1 /* a  : aborted */ +
        1 /* f  : full */ +
        1 /* e  : empty */ +
        2 /* \n\0 */];

void uart_rxflags_str(uart_rxflags_str_t, const uart_rxflags_t *);

typedef
    char uart_txflags_str_t[
        1 /* \n */ +
        2 /* ?? : byte counter */ +
        2 /* ?? : interrupt counter */ +
        2 /* \n\0 */];

typedef
void (*uart_tx_complete_cb_t)(uintptr_t);

typedef
bool (*uart_rx_pred_cb_t)(const uint8_t *curr, uintptr_t);

typedef
void (*uart_rx_complete_cb_t)(
    uint8_t *begin, const uint8_t *end,
    uart_rxflags_t *,
    uintptr_t user_data);

typedef
void (*uart_rx_recv_cb_t)(
    uint8_t data,
    uart_rxflags_t *,
    uintptr_t user_data);

const char *uart1_send_str_r(const char *begin, const char *const end);
const char *uart1_send_str(const char *str);
char *uart1_recv_str(char *begin, const char *const end, char delimiter);

void uart1_send(const uint8_t *begin, const uint8_t *const end);

void uart1_async_send(
    const uint8_t *begin, const uint8_t *end,
    uart_tx_complete_cb_t,
    uintptr_t);

void uart1_async_recv(
    uint8_t *begin, const uint8_t *end,
    uart_rx_pred_cb_t,
    uart_rx_complete_cb_t,
    uintptr_t);

void uart1_async_recv_complete(void);

/* non-buffering continuous async mode */
void uart1_async_recv_cb(
    uart_rx_recv_cb_t recv_cb,
    uintptr_t user_data);
/*----------------------------------------------------------------------------*/
