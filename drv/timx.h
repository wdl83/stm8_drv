#pragma once

#include <stdint.h>

typedef void (*timer_cb_t)(uintptr_t user_data);

typedef struct
{
    timer_cb_t cb;
    uintptr_t user_data;
} tim_ctl_t;
