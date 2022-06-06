#pragma once

#include "stm8.h"

#ifndef TIM4_BASE
#error "Please define TIM4 base address"
#endif

#define TIM4_CR1                                  STM8_REGISTER(TIM4_BASE, 0x00)
#define ARPE 7
#define OPM 3
#define URS 2
#define UDIS 1
#define CEN 0

#define TIM4_IER                                  STM8_REGISTER(TIM4_BASE, 0x03)
#define TIE 6
#define UIE 0

#define TIM4_SR                                   STM8_REGISTER(TIM4_BASE, 0x04)
#define TIF 6
#define UIF 0

#define TIM4_EGR                                  STM8_REGISTER(TIM4_BASE, 0x05)
#define TG 6
#define UG 0

#define TIM4_CNTR                                 STM8_REGISTER(TIM4_BASE, 0x06)

#define TIM4_PSCR                                 STM8_REGISTER(TIM4_BASE, 0x07)
#define PSC2 2
#define PSC1 1
#define PSC0 0

#define TIM4_ARR                                  STM8_REGISTER(TIM4_BASE, 0x08)
