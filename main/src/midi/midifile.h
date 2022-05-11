#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../segment_t.h"

int_least8_t midifile_init(uint_least8_t const cs);
int_least8_t midifile_write( SegmentBuf * const segmentBuf, char const * const fname);
