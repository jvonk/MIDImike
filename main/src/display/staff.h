#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"

void staff_init(uint_least8_t tft_cs_pin, uint_least8_t tft_dc_pin, uint_least8_t reset_pin);
void staff_draw_note(Pitch & pitch);
