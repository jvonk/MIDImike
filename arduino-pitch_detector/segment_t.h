/**
 * @brief Note level segmentation, based on Monty's method, 2000 type definitions
 * @file  segment_t.h
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "config.h"
#include "sample_t.h"

typedef uint_least16_t segmentRelTime_t;  // relative time from most recent onset/offset [msec], max ~64s
typedef uint_least8_t  segmentPitch_t;    // MIDI pitch#, where middle C (C4) is 60
typedef uint_least8_t  segmentEnergy_t;   // MIDI velocity (loudness) [0-127]
typedef uint64_t       absoluteTime_t;    // matches return type for millis()

struct segment_t {
    segmentPitch_t     pitch;     // MIDI pitch#, where middle C (C4) is 60
    segmentEnergy_t    energy;    // MIDI velocity (loudness) [0-127]
    segmentRelTime_t   onset;     // time since the end (offset) of the previous note [msec]
    segmentRelTime_t   duration;  // time since the onset of this note [msec]
};

enum class segmentEnergyState_t {
    findNegSlope = 0,  // find negative energy slope
    findPosSlope,      // find positive energy slope
    foundPosSlope      // found positive energy slope, new note perhaps?
};
