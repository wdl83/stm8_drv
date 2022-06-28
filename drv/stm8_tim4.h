#pragma once

#include "stm8.h"

#ifndef TIM4_BASE
#error "Please define TIM4 base address"
#endif

#define TIM4_CR1                                  STM8_REGISTER(TIM4_BASE, 0x00)
#define CR1_ARPE 7
#define CR1_OPM 3
#define CR1_URS 2
#define CR1_UDIS 1
#define CR1_CEN 0

#define TIM4_IER                                  STM8_REGISTER(TIM4_BASE, 0x03)
#define IER_TIE 6
#define IER_UIE 0

#define TIM4_SR                                   STM8_REGISTER(TIM4_BASE, 0x04)
#define SR_TIF 6
#define SR_UIF 0

#define TIM4_EGR                                  STM8_REGISTER(TIM4_BASE, 0x05)
#define EGR_TG 6
#define EGR_UG 0

#define TIM4_CNTR                                 STM8_REGISTER(TIM4_BASE, 0x06)

#define TIM4_PSCR                                 STM8_REGISTER(TIM4_BASE, 0x07)
#define PSCR_PSC2 2
#define PSCR_PSC1 1
#define PSCR_PSC0 0

#define TIM4_ARR                                  STM8_REGISTER(TIM4_BASE, 0x08)
