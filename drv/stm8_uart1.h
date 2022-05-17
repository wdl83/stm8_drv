#pragma once

#include "stm8.h"

#ifndef UART1_BASE
#error "Please define UART1 base address"
#endif

#define UART1_SR                                  STM8_REGISTER(UART1_BASE, 0x0)
#define TXE 7
#define TC 6
#define RXNE 5
#define IDLE 4
#define OR 3
#define NF 2
#define FE 1
#define PE 0

#define UART1_DR                                 STM8_REGISTER(UART1_BASE, 0x01)
#define UART1_BRR1                               STM8_REGISTER(UART1_BASE, 0x02)
#define UART1_BRR2                               STM8_REGISTER(UART1_BASE, 0x03)

#define UART1_CR1                                STM8_REGISTER(UART1_BASE, 0x04)
#define R8 7
#define T8 6
#define UARTD 5
#define M 4
#define WAKE 3
#define PCEN 2
#define PS 1
#define PIEN 0

#define UART1_CR2                                STM8_REGISTER(UART1_BASE, 0x05)
#define TIEN 7
#define TCIEN 6
#define RIEN 5
#define ILIEN 4
#define TEN 3
#define REN 2
#define RWU 1
#define SBK 0

#define UART1_CR3                                STM8_REGISTER(UART1_BASE, 0x06)
#define LINEN 6
#define STOP2 5
#define STOP1 4
#define CLKEN 3
#define CPOL 2
#define CPHA 1
#define LBCL 0

#define UART1_CR4                                STM8_REGISTER(UART1_BASE, 0x07)
#define UART1_CR5                                STM8_REGISTER(UART1_BASE, 0x08)
#define UART1_GTR                                STM8_REGISTER(UART1_BASE, 0x09)
#define UART1_PSCR                               STM8_REGISTER(UART1_BASE, 0x0A)
