#include "stm8_portx.h"

#ifndef PORT_D_BASE
#error "Please define PORTD base address"
#endif

#define PD_ODR                                         STM8_PORT_ODR(PORT_D_BASE)
#define PD_IDR                                         STM8_PORT_IDR(PORT_D_BASE)
#define PD_DDR                                         STM8_PORT_DDR(PORT_D_BASE)
#define PD_CR1                                         STM8_PORT_DR1(PORT_D_BASE)
#define PD_CR2                                         STM8_PORT_DR2(PORT_D_BASE)

#define STM8_PORT_D                                        STM8_PORT(PORT_D_BASE)
