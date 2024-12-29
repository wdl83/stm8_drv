#pragma once

#include "mem.h"
#include "stm8_flash.h"

#define MASS_UNLOCK_FLASH() \
    do { \
        FLASH_PUKR = UINT8_C(0x56); \
        FLASH_PUKR = UINT8_C(0xAE); \
    } while(0)

#define MASS_LOCK_FLASH() FLASH_IAPSR &= ~M1(IAPSR_PUL)
