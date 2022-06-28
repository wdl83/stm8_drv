#pragma once

#include "stm8.h"

#ifndef TIM2_BASE
#error "Please define TIM2 base address"
#endif

/*----------------------------------------------------------------------------*/
#define TIM2_CR1                                  STM8_REGISTER(TIM2_BASE, 0x00)
#define ARPE 7
#define OPM 3
#define URS 2
#define UDIS 1
#define CEN 0
/*----------------------------------------------------------------------------*/
#define TIM2_IER                                  STM8_REGISTER(TIM2_BASE, 0x03)
#define TIE 6
#define CC3IE 3
#define CC2IE 2
#define CC1IE 1
#define UIE 0
/*----------------------------------------------------------------------------*/
#define TIM2_SR1                                  STM8_REGISTER(TIM2_BASE, 0x04)
#define TIF 6
#define CC3IF 3
#define CC2IF 2
#define CC1IF 1
#define UIF 0
/*----------------------------------------------------------------------------*/
#define TIM2_SR2                                  STM8_REGISTER(TIM2_BASE, 0x05)
#define CC3OF 3
#define CC2OF 2
#define CC1OF 1
/*----------------------------------------------------------------------------*/
#define TIM2_EGR                                  STM8_REGISTER(TIM2_BASE, 0x06)
#define TG 6
#define CC3G 3
#define CC2G 2
#define CC1G 1
#define UG 0
/*----------------------------------------------------------------------------*/
#define TIM2_CCMR1                                STM8_REGISTER(TIM2_BASE, 0x07)
/* channel configured in output */
#define OC1M2 6
#define OC1M1 5
#define OC1M0 4
#define OC1PE 3
/* channel configured in input */
#define IC1F3 7
#define IC1F2 6
#define IC1F1 5
#define IC1F0 4
#define IC1PSC1 3
#define IC1PSC0 2
/* common */
#define CCS1S1 1
#define CCS1S0 0
/*----------------------------------------------------------------------------*/
#define TIM2_CCMR2                                STM8_REGISTER(TIM2_BASE, 0x08)
/* channel configured in output */
#define OC2M2 6
#define OC2M1 5
#define OC2M0 4
#define OC2PE 3
/* channel configured in input */
#define IC2F3 7
#define IC2F2 6
#define IC2F1 5
#define IC2F0 4
#define IC2PSC1 3
#define IC2PSC0 2
/* common */
#define CCS2S1 1
#define CCS2S0 0
/*----------------------------------------------------------------------------*/
#define TIM2_CCMR3                                STM8_REGISTER(TIM2_BASE, 0x09)
/* channel configured in output */
#define OC3M2 6
#define OC3M1 5
#define OC3M0 4
#define OC3PE 3
/* channel configured in input */
#define IC3F3 7
#define IC3F2 6
#define IC3F1 5
#define IC3F0 4
#define IC3PSC1 3
#define IC3PSC0 2
/* common */
#define CCS3S1 1
#define CCS3S0 0
/*----------------------------------------------------------------------------*/
#define TIM2_CCER1                                STM8_REGISTER(TIM2_BASE, 0x0A)
#define CC2P 5
#define CC2E 4
#define CC1P 1
#define CC1E 0
/*----------------------------------------------------------------------------*/
#define TIM2_CCER2                                STM8_REGISTER(TIM2_BASE, 0x0B)
#define CC3P 1
#define CC3E 0
/*----------------------------------------------------------------------------*/
#define TIM2_CNTRH                                STM8_REGISTER(TIM2_BASE, 0x0C)
#define TIM2_CNTRL                                STM8_REGISTER(TIM2_BASE, 0x0D)
/*----------------------------------------------------------------------------*/
#define TIM2_PSCR                                 STM8_REGISTER(TIM2_BASE, 0x0E)
#define PSC3 3
#define PSC2 2
#define PSC1 1
#define PSC0 0
/*----------------------------------------------------------------------------*/
#define TIM2_ARRH                                 STM8_REGISTER(TIM2_BASE, 0x0F)
#define TIM2_ARRL                                 STM8_REGISTER(TIM2_BASE, 0x10)
/*----------------------------------------------------------------------------*/
#define TIM2_CCR1H                                STM8_REGISTER(TIM2_BASE, 0x11)
#define TIM2_CCR1L                                STM8_REGISTER(TIM2_BASE, 0x12)
/*----------------------------------------------------------------------------*/
#define TIM2_CCR2H                                STM8_REGISTER(TIM2_BASE, 0x13)
#define TIM2_CCR2L                                STM8_REGISTER(TIM2_BASE, 0x14)
/*----------------------------------------------------------------------------*/
#define TIM2_CCR3H                                STM8_REGISTER(TIM2_BASE, 0x15)
#define TIM2_CCR3L                                STM8_REGISTER(TIM2_BASE, 0x16)
/*----------------------------------------------------------------------------*/
