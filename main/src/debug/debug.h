#pragma once

#include <Arduino.h>
#include <stdint.h>

// other option is to use __BASE_FILE__
#define ASSERT(x) do { if (!(x)) { debug_assertPrint(__func__, __LINE__); /*blink LED*/} } while (0)

void debug_assertPrint(char const * const func, int const lineno);
void debug_hex_dump(uint8_t const * p, uint16_t * const pos, uint16_t const n);

// help reduce the number of #if statements in elsewhere
#if SHOW_MEMORY_USAGE
#  define SHOW_MEMORY_USAGE_ONLY(a) do { a; } while (0)
#else
#  define SHOW_MEMORY_USAGE_ONLY(a)
#endif
