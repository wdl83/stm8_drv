#include "stm8_portx.h"

#ifndef PORT_C_BASE
#error "Please define PORTC base address"
#endif

#define PC_ODR                                         STM8_PORT_ODR(PORT_C_BASE)
#define PC_IDR                                         STM8_PORT_IDR(PORT_C_BASE)
#define PC_DDR                                         STM8_PORT_DDR(PORT_C_BASE)
#define PC_CR1                                         STM8_PORT_CR1(PORT_C_BASE)
#define PC_CR2                                         STM8_PORT_CR2(PORT_C_BASE)

#define STM8_PORT_C                                        STM8_PORT(PORT_C_BASE)
