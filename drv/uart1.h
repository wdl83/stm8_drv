#pragma once

#include <stddef.h>
#include <stdint.h>

#include "mem.h"
#include "stm8_uart1.h"

/*----------------------------------------------------------------------------*/
#define UART1_TX_ENABLE() UART1_CR2 |= M1(CR2_TEN)
#define UART1_TX_DISABLE() UART1_CR2 &= ~M1(CR2_TEN)
#define UART1_TX_ENABLED() (UART1_CR2 & M1(CR2_TEN))

#define UART1_RX_ENABLE() UART1_CR2 |= M1(CR2_REN)
#define UART1_RX_DISABLE() UART1_CR2 &= ~M1(CR2_REN)
#define UART1_RX_ENABLED() (UART1_CR2 & M1(CR2_REN))

#define CALC_BR(cpu_clk, bps) ((cpu_clk) / (bps))

#define UART1_BR(br) \
      UART1_BRR1 =  \
      ((uint8_t)((UINT16_C(0x0FF0) & (br)) >> 4)), \
      UART1_BRR2 = \
      ((uint8_t)((UINT16_C(0xF000) & (br)) >> 12)) \
       | ((uint8_t)(UINT16_C(0x00F) & (br)))

#define UART1_TX_READY() (UART1_SR & M1(SR_TXE))
#define UART1_TX_COMPLETE() (UART1_SR & M1(SR_TC))

#define UART1_RX_READY() (UART1_SR & M1(SR_RXNE))

#define UART1_IDLE() (UART1_SR & M1(SR_IDLE))

#define UART1_TX(data) UART1_DR = (data)
#define UART1_RX(data) (data) = UART1_DR
#define UART1_RD() UART1_DR

#define UART1_TX_READY_INT_ENABLE() UART1_CR2 |= M1(CR2_TIEN)
#define UART1_TX_READY_INT_DISABLE() UART1_CR2 &= ~M1(CR2_TIEN)

#define UART1_TX_COMPLETE_INT_ENABLE() UART1_CR2 |= M1(CR2_TCIEN)
#define UART1_TX_COMPLETE_INT_DISABLE() UART1_CR2 &= ~M1(CR2_TCIEN)
#define UART1_TX_COMPLETE_INT_ENABLED() (UART1_CR2 & M1(CR2_TCIEN))

#define UART1_RX_INT_ENABLE() UART1_CR2 |= M1(CR2_RIEN)
#define UART1_RX_INT_DISABLE() UART1_CR2 &= ~M1(CR2_RIEN)

#define UART1_PARITY_EVEN() UART1_CR1 &= ~M1(CR1_PS), UART1_CR1 |= M2(CR1_M, CR1_PCEN)
#define UART1_PARITY_ODD() UART1_CR1 |= M2(CR1_PCEN, CR1_PS)

#define UART1_FRAME_ERROR() (UART1_SR & M1(SR_FE))
#define UART1_OVERRUN_ERROR() (UART1_SR & M1(SR_OR))
#define UART1_PARITY_ERROR() (UART1_SR & M1(SR_PE))
#define UART1_NOISE_FLAG() (UART1_SR & M1(SR_NF))

#define UART1_FOPN_ERRORS() (UART1_SR & M4(SR_OR, SR_NF, SR_FE, SR_PE))
