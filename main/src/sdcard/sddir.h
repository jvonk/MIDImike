#pragma once

#include <Arduino.h>
#include <stdint.h>

typedef uint_least8_t (* sddir_callback_t)(File & f, char * instrument);

uint_least8_t init(uint_least8_t const cs_pin);
uint_least8_t for_each_file(char const * const dirName, sddir_callback_t cb);
