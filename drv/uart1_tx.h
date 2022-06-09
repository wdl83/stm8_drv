#pragma once

#include <stdint.h>

#include "uart1.h"

const char *uart1_send_str_r(const char *begin, const char *const end);
const char *uart1_send_str(const char *str);
void uart1_send(const uint8_t *begin, const uint8_t *const end);
