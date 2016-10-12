/**
 * @brief Sample type definitions and helpers
 * @file  sample_t.h
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

typedef char           sample_t;      // one sample
typedef sample_t *     samples_t;     // chunk containing samples
typedef uint_least16_t sampleCnt_t;   // number of samples in chunk
typedef uint_least16_t sampleRate_t;  // sample rate in samples/sec

typedef uint8_t        amplitude_t;   // signal amplitude
typedef float          frequency_t;   // signal frequency
