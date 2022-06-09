#include <stddef.h>

#include "util.h"

char *xprint8(char *dst, uint8_t value)
{
    const char lookup16_[] =
    {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };

    *dst++ = lookup16_[value >> 4];
    *dst++ = lookup16_[UINT8_C(0xF) & value];
    return dst;
}

char *xprint16(char *dst, uint16_t value)
{
    dst = xprint8(dst, value >> 8);
    dst = xprint8(dst, value & UINT8_C(0xFF));
    return dst;
}

char *scopy(char *dst, const char *src, size_t n)
{
    if(NULL == dst || NULL == src || 0 == n) return dst;

    while(0 != n && '\0' != *src)
    {
        *dst++ = *src++;
        --n;
    }
    return dst;
}
