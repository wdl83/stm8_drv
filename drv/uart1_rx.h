#pragma once

#include <stdint.h>

#include "uart1.h"

char *uart1_recv_str(char *begin, const char *const end, char delimiter);
