#pragma once

#include "stm8_portx.h"

#ifndef PORT_F_BASE
#error "Please define PORTF base address"
#endif

#define PF_ODR                                         STM8_PORT_ODR(PORT_F_BASE)
#define PF_IDR                                         STM8_PORT_IDR(PORT_F_BASE)
#define PF_DDR                                         STM8_PORT_DDR(PORT_F_BASE)
#define PF_CR1                                         STM8_PORT_CR1(PORT_F_BASE)
#define PF_CR2                                         STM8_PORT_CR2(PORT_F_BASE)

#define STM8_PORT_F                                        STM8_PORT(PORT_F_BASE)
