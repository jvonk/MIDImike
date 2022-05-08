#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"

#if 0
class Note;
#endif

void staff_init(uint_least8_t tftCS_pin, uint_least8_t dc_pin, uint_least8_t reset_pin);
void staff_draw_note(pitch_t const * const pitch, amplitude_t const amplitude);
