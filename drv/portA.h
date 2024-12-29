#pragma once

#include "stm8_portx.h"

#ifndef PORT_A_BASE
#error "Please define PORTA base address"
#endif

#define PA_ODR                                         STM8_PORT_ODR(PORT_A_BASE)
#define PA_IDR                                         STM8_PORT_IDR(PORT_A_BASE)
#define PA_DDR                                         STM8_PORT_DDR(PORT_A_BASE)
#define PA_CR1                                         STM8_PORT_CR1(PORT_A_BASE)
#define PA_CR2                                         STM8_PORT_CR2(PORT_A_BASE)

#define STM8_PORT_A                                        STM8_PORT(PORT_A_BASE)
