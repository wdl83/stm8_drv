#pragma once

#include <stddef.h>

#define TO_STR_IMPL(x) #x
#define TO_STR(x) TO_STR_IMPL(x)

#define STATIC_ASSERT_MSG(cond, msg) \
    typedef struct {uint8_t value : (cond) ? 8 : 0;} static_assert_##msg

#define STATIC_ASSERT_IMPL1(cond, L, C) \
    STATIC_ASSERT_MSG(cond, C##_at_line_##L)

#define STATIC_ASSERT_IMPL2(cond, L, C) \
    STATIC_ASSERT_IMPL1(cond, L, C)

#define STATIC_ASSERT(cond) \
    STATIC_ASSERT_IMPL2(cond, __LINE__, __COUNTER__)
