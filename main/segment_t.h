#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "config.h"
#include "sample_t.h"

typedef uint64_t       absolute_time_t;    // matches return type for millis()

typedef uint_least16_t segmentRelTime_t;   // relative time from most recent onset/offset [msec], max ~64s
typedef uint_least8_t  segment_pitch_t;    // MIDI pitch#, where middle C (C4) is 60
typedef uint_least8_t  segment_energy_t;   // MIDI velocity (loudness) [0-127]

typedef struct segment_t {
    segment_pitch_t    pitch;    // MIDI pitch#, where middle C (C4) is 60
    segment_energy_t   energy;   // MIDI velocity (loudness) [0-127]
    segmentRelTime_t   onset;     // time since the end (offset) of the previous note [msec]
    segmentRelTime_t   duration;  // time since the onset of this note [msec]
} segment_t;
