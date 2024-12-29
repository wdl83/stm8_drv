#pragma once

#include <stddef.h>

#include "mem.h"
#include "stm8_tim2.h"
#include "timx.h"

#define TIM2_ENABLE() TIM2_CR1 |= M1(CEN)
#define TIM2_DISABLE() TIM2_CR1 &= ~M1(CEN)

#define TIM2_AUTO_RELOAD_PRELOAD_ENABLE() TIM2_CR1 |= M1(ARPE)

#define TIM2_CLK_DIV_1()      TIM2_PSCR =  0
#define TIM2_CLK_DIV_2()      TIM2_PSCR =  1
#define TIM2_CLK_DIV_4()      TIM2_PSCR =  2
#define TIM2_CLK_DIV_8()      TIM2_PSCR =  3
#define TIM2_CLK_DIV_16()     TIM2_PSCR =  4
#define TIM2_CLK_DIV_32()     TIM2_PSCR =  5
#define TIM2_CLK_DIV_64()     TIM2_PSCR =  6
#define TIM2_CLK_DIV_128()    TIM2_PSCR =  7
#define TIM2_CLK_DIV_256()    TIM2_PSCR =  8
#define TIM2_CLK_DIV_512()    TIM2_PSCR =  9
#define TIM2_CLK_DIV_1K()     TIM2_PSCR = 10
#define TIM2_CLK_DIV_2K()     TIM2_PSCR = 11
#define TIM2_CLK_DIV_4K()     TIM2_PSCR = 12
#define TIM2_CLK_DIV_8K()     TIM2_PSCR = 13
#define TIM2_CLK_DIV_16K()    TIM2_PSCR = 14
#define TIM2_CLK_DIV_32K()    TIM2_PSCR = 15

#define TIM2_RD_CNTR() (((uint16_t)TIM2_CNTRH << 8) | TIM2_CNTRL)
#define TIM2_WR_CNTR(value) \
    do { \
        TIM2_CNTRH = (value) >> 8; \
        TIM2_CNTRL = (value); \
    } while(0)

#define TIM2_RD_TOP() (((uint16_t)TIM2_ARRL << 8) | TIM2_ARRH)
#define TIM2_WR_TOP(value) \
    do { \
        TIM2_ARRH = (value) >> 8; \
        TIM2_ARRL = (value); \
    } while(0)

#define TIM2_INT_ENABLE() TIM2_IER |= M1(UIE)
#define TIM2_INT_DISABLE() TIM2_IER &= ~M1(UIE)
#define TIM2_INT_CLEAR() TIM2_SR1 &= ~M1(UIF)
/* capture/compare */
#define TIM2_CC3_INT_CLEAR() TIM2_SR1 &= ~M1(CC3IF)
#define TIM2_CC2_INT_CLEAR() TIM2_SR1 &= ~M1(CC2IF)
#define TIM2_CC1_INT_CLEAR() TIM2_SR1 &= ~M1(CC1IF)
/* capture/compare overcapture */
#define TIM2_CC3_OCF_CLEAR() TIM2_SR2 &= ~M1(CC3OF)
#define TIM2_CC2_OCF_CLEAR() TIM2_SR2 &= ~M1(CC2OF)
#define TIM2_CC1_OCF_CLEAR() TIM2_SR2 &= ~M1(CC1OF)

/* set/clear timer callback */
void tim2_cb(timer_cb_t cb, uintptr_t user_data);

void tim2_irq(void) __interrupt(IRQ_NO_TIM2);
