#pragma once

#include <stdint.h>

#define STM8_REGISTER(base, offset) (*(volatile uint8_t *)((base) + (offset)))
#define ASSERT(cond)

#define INTERRUPT_ENABLE() __asm__("rim")
#define INTERRUPT_DISABLE() __asm__("sim")

#ifdef STM8S003F3P6
#include "stm8s003f3p6.h"
#else
#error "unsupported device"
#endif
