#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "../../sample_t.h"

class Note;

void staff_init(uint_least8_t tftCS_pin, uint_least8_t dc_pin, uint_least8_t reset_pin);
void staff_draw_note(Pitch & pitch, amplitude_t const amplitude);
