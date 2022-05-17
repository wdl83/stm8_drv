#pragma once

#include "stm8.h"

#ifndef UART1_BASE
#error "Please define UART1 base address"
#endif

/* Internal clock register */
#define CLK_ICKR                                    STM8_REGISTER(CLK_BASE, 0x0)
#define REGAH 5
#define LSIRDY 4
#define LSIEN 3
#define FHW 2
#define HSIRDY 1
#define HSIEN 0

/* External clock register */
#define CLK_ECKR                                    STM8_REGISTER(CLK_BASE, 0x1)
#define HSERDY 1
#define HSEEN 0

// reserved                                         STM8_REGISTER(CLK_BASE, 0x2)

/* Clock master status register */
#define CLK_CMSR                                    STM8_REGISTER(CLK_BASE, 0x3)
#define HSI_SRC 0xE1
#define LSI_SRC 0xD2
#define HSE_SRC 0xB4

/* Clock master switch register */
#define CLK_SWR                                     STM8_REGISTER(CLK_BASE, 0x4)

/* Switch control register */
#define CLK_SWCR                                    STM8_REGISTER(CLK_BASE, 0x5)
#define SWIF 3
#define SWIEN 2
#define SWEN 1
#define SWBSY 0

/* Clock divider register */
#define CLK_CKDIVR                                  STM8_REGISTER(CLK_BASE, 0x6)
#define HSIDIV1 4
#define HSIDIV0 3
#define CPUDIV2 2
#define CPUDIV1 1
#define CPUDIV0 0

/* Peripheral clock gating register 1 */
#define CLK_PCKENR1                                 STM8_REGISTER(CLK_BASE, 0x7)

/* Clock security system register */
#define CLK_CSSR                                    STM8_REGISTER(CLK_BASE, 0x8)
#define CSSD 3
#define CSSDIE 2
#define AUX 1
#define CSSEN 0

/* Configurable clock output register */
#define CLK_CCOR                                    STM8_REGISTER(CLK_BASE, 0x9)
#define CCOBSY 6
#define CCORDY 5
#define CCOSEL3 4
#define CCOSEL2 3
#define CCOSEL1 2
#define CCOSEL0 1
#define CCOEN 0

/* Peripheral clock gating register 2 */
#define CLK_PCKENR2                                 STM8_REGISTER(CLK_BASE, 0xA)

// reserved                                         STM8_REGISTER(CLK_BASE, 0xB)

/* HSI clock calibration trimming register */
#define CLK_HSITRIMR                                STM8_REGISTER(CLK_BASE, 0xC)
#define HSITRIM3 3
#define HSITRIM2 2
#define HSITRIM1 1
#define HSITRIM0 0

/* SWIM clock control register */
#define CLK_SWIMCCT                                 STM8_REGISTER(CLK_BASE, 0xD)
#define SWIMCLK 0
