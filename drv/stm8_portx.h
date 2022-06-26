#pragma once

#include <stdint.h>

#include "stm8.h"

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t odr0 : 1;
        uint8_t odr1 : 1;
        uint8_t odr2 : 1;
        uint8_t odr3 : 1;
        uint8_t odr4 : 1;
        uint8_t odr5 : 1;
        uint8_t odr6 : 1;
        uint8_t odr7 : 1;
    } bits;
} ODR_t;

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t idr0 : 1;
        uint8_t idr1 : 1;
        uint8_t idr2 : 1;
        uint8_t idr3 : 1;
        uint8_t idr4 : 1;
        uint8_t idr5 : 1;
        uint8_t idr6 : 1;
        uint8_t idr7 : 1;
    } bits;
} IDR_t;

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t ddr0 : 1;
        uint8_t ddr1 : 1;
        uint8_t ddr2 : 1;
        uint8_t ddr3 : 1;
        uint8_t ddr4 : 1;
        uint8_t ddr5 : 1;
        uint8_t ddr6 : 1;
        uint8_t ddr7 : 1;
    } bits;
} DDR_t;

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t c0 : 1;
        uint8_t c1 : 1;
        uint8_t c2 : 1;
        uint8_t c3 : 1;
        uint8_t c4 : 1;
        uint8_t c5 : 1;
        uint8_t c6 : 1;
        uint8_t c7 : 1;
    } bits;
} CR_t;

typedef struct
{
    volatile ODR_t odr;
    volatile IDR_t idr;
    volatile DDR_t ddr;
    volatile CR_t cr1;
    volatile CR_t cr2;
} port_t;

typedef struct
{
    ODR_t odr;
    IDR_t idr;
    DDR_t ddr;
    CR_t cr1;
    CR_t cr2;
} port_data_t;

#define STM8_PORT(base)                                       ((port_t *)(base))

#define STM8_PORT_ODR(base)                            STM8_REGISTER(base, 0x00)
#define STM8_PORT_IDR(base)                            STM8_REGISTER(base, 0x01)
#define STM8_PORT_DDR(base)                            STM8_REGISTER(base, 0x02)
#define STM8_PORT_CR1(base)                            STM8_REGISTER(base, 0x03)
#define STM8_PORT_CR2(base)                            STM8_REGISTER(base, 0x04)

void stm8_port_copy(port_data_t *dst, uint16_t base);
