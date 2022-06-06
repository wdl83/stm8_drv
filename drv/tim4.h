#pragma once

#include <stddef.h>

#include "mem.h"
#include "stm8_tim4.h"
#include "timx.h"

#define TIM4_ENABLE() TIM4_CR1 |= M1(CEN)
#define TIM4_DISABLE() TIM4_CR1 &= ~M1(CEN)

#define TIM4_AUTO_RELOAD_PRELOAD_ENABLE() TIM4_CR1 |= M1(ARPE)

#define TIM4_CLK_DIV_1() TIM4_PSCR = 0
#define TIM4_CLK_DIV_2() TIM4_PSCR = 1
#define TIM4_CLK_DIV_4() TIM4_PSCR = 2
#define TIM4_CLK_DIV_8() TIM4_PSCR = 3
#define TIM4_CLK_DIV_16() TIM4_PSCR = 4
#define TIM4_CLK_DIV_32() TIM4_PSCR = 5
#define TIM4_CLK_DIV_64() TIM4_PSCR = 6
#define TIM4_CLK_DIV_128() TIM4_PSCR = 7

#define TIM4_RD_CNTR() TIM4_CNTR
#define TIM4_WR_CNTR(value) TIM4_CNTR = (value)

#define TIM4_RD_TOP() TIM4_ARR
#define TIM4_WR_TOP(value) TIM4_ARR = (value)

#define TIM4_INT_ENABLE() TIM4_IER |= M1(UIE)
#define TIM4_INT_DISABLE() TIM4_IER &= ~M1(UIE)
#define TIM4_INT_CLEAR() TIM4_SR &= ~M1(UIF)

/* set/clear timer callback */
void tim4_cb(timer_cb_t cb, uintptr_t user_data);

void tim4_irq(void) __interrupt(IRQ_NO_TIM4);
