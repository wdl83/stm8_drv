#include "eeprom.h"
#include "stm8.h"
#include "stm8s003f3.h"
#include <stdint.h>

void eeprom_write(uintptr_t offset, const uint8_t *begin, const uint8_t *const end)
{
    ASSERT(EEPROM_SIZE > offset);
    ASSERT(EEPROM_SIZE > offset + (end - begin));

    uintptr_t addr = EEPROM_BASE + offset;

    /* source: PM0051 Programming manual, page 15/27, Doc ID 14614 Rev 3
     * 3.3 "Unwanted memory access protection" */
    MASS_UNLOCK_EEPROM();

    while (EEPROM_LOCKED()) {}

    /* write data from buffer */
    while(begin != end)
    {
        STM8_WRITE8(addr, *begin);
        ++addr;
        ++begin;
        while (!EEPROM_WRITE_COMPLETE()) {}
    }

    MASS_LOCK_EEPROM();
}
