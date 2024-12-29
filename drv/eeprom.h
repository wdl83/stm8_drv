#pragma once

#include <stddef.h>
#include <stdint.h>

#include "mem.h"
#include "stm8_eeprom.h"
#include "stm8_flash.h"

#define MASS_UNLOCK_EEPROM() \
    do { \
        FLASH_DUKR = UINT8_C(0xAE); \
        FLASH_DUKR = UINT8_C(0x56); \
    } while(0)

#define MASS_LOCK_EEPROM() FLASH_IAPSR &= ~M1(IAPSR_DUL)
#define EEPROM_LOCKED() (FLASH_IAPSR & M1(IAPSR_DUL))
#define EEPROM_WRITE_COMPLETE() (FLASH_IAPSR & M1(IAPSR_EOP))

#define STM8_EEPROM_READ8(offset) STM8_READ8(EEPROM_BASE + offset)
#define STM8_EEPROM_EXTRA_READ8(offset) STM8_READ8(EEPROM_EXTRA_BASE + offset)

void eeprom_write(uintptr_t offset, const uint8_t *begin, const uint8_t *const end);
