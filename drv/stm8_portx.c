#include "stm8_portx.h"

void stm8_port_copy(port_data_t *dst, uint16_t base)
{
    dst->odr.value = STM8_REGISTER(base, 0x00);
    dst->idr.value = STM8_REGISTER(base, 0x01);
    dst->ddr.value = STM8_REGISTER(base, 0x02);
    dst->cr1.value = STM8_REGISTER(base, 0x03);
    dst->cr2.value = STM8_REGISTER(base, 0x04);
}
