#include "stm8_portx.h"

#ifndef PORT_E_BASE
#error "Please define PORTE base address"
#endif

#define PE_ODR                                         STM8_PORT_ODR(PORT_E_BASE)
#define PE_IDR                                         STM8_PORT_IDR(PORT_E_BASE)
#define PE_DDR                                         STM8_PORT_DDR(PORT_E_BASE)
#define PE_CR1                                         STM8_PORT_CR1(PORT_E_BASE)
#define PE_CR2                                         STM8_PORT_CR2(PORT_E_BASE)

#define STM8_PORT_E                                        STM8_PORT(PORT_E_BASE)
