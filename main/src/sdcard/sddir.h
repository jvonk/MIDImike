#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SdFat.h>

typedef uint_least8_t (* sddir_callback_t)(File & f, char * instrument);

uint_least8_t sddir_init(uint_least8_t const cs_pin);
uint_least8_t sddir_for_each_file_in_dir(char const * const dir_name, sddir_callback_t cb);
