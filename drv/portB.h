#include "stm8_portx.h"

#ifndef PORT_B_BASE
#error "Please define PORTB base address"
#endif

#define PB_ODR                                         STM8_PORT_ODR(PORT_B_BASE)
#define PB_IDR                                         STM8_PORT_IDR(PORT_B_BASE)
#define PB_DDR                                         STM8_PORT_DDR(PORT_B_BASE)
#define PB_CR1                                         STM8_PORT_CR1(PORT_B_BASE)
#define PB_CR2                                         STM8_PORT_CR2(PORT_B_BASE)

#define STM8_PORT_B                                        STM8_PORT(PORT_B_BASE)
