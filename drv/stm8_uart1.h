#pragma once

#include "stm8.h"

#ifndef UART1_BASE
#error "Please define UART1 base address"
#endif

#define UART1_SR                                  STM8_REGISTER(UART1_BASE, 0x0)
#define SR_TXE 7
#define SR_TC 6
#define SR_RXNE 5
#define SR_IDLE 4
#define SR_OR 3
#define SR_NF 2
#define SR_FE 1
#define SR_PE 0

#define UART1_DR                                 STM8_REGISTER(UART1_BASE, 0x01)
#define UART1_BRR1                               STM8_REGISTER(UART1_BASE, 0x02)
#define UART1_BRR2                               STM8_REGISTER(UART1_BASE, 0x03)

#define UART1_CR1                                STM8_REGISTER(UART1_BASE, 0x04)
#define CR1_R8 7
#define CR1_T8 6
#define CR1_UARTD 5
#define CR1_M 4
#define CR1_WAKE 3
#define CR1_PCEN 2
#define CR1_PS 1
#define CR1_PIEN 0

#define UART1_CR2                                STM8_REGISTER(UART1_BASE, 0x05)
#define CR2_TIEN 7
#define CR2_TCIEN 6
#define CR2_RIEN 5
#define CR2_ILIEN 4
#define CR2_TEN 3
#define CR2_REN 2
#define CR2_RWU 1
#define CR2_SBK 0

#define UART1_CR3                                STM8_REGISTER(UART1_BASE, 0x06)
#define CR3_LINEN 6
#define CR3_STOP2 5
#define CR3_STOP1 4
#define CR3_CLKEN 3
#define CR3_CPOL 2
#define CR3_CPHA 1
#define CR3_LBCL 0

#define UART1_CR4                                STM8_REGISTER(UART1_BASE, 0x07)
#define UART1_CR5                                STM8_REGISTER(UART1_BASE, 0x08)
#define UART1_GTR                                STM8_REGISTER(UART1_BASE, 0x09)
#define UART1_PSCR                               STM8_REGISTER(UART1_BASE, 0x0A)
