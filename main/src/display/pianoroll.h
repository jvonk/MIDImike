#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../segment_t.h"

void pianoroll_init(uint_least8_t tftCS_pin, uint_least8_t dc_pin, uint_least8_t reset_pin);
void pianoroll_clear(void);
void pianoroll_draw(absolute_time_t const lastOffset, SegmentBuf * const segmentBuf);
