#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "config.h"

typedef int8_t         sample_t;      // one sample
typedef sample_t *     samples_t;     // chunk containing samples
typedef uint_least16_t sample_cnt_t;  // number of samples in chunk
typedef uint_least16_t sampleRate_t;  // sample rate in samples/sec

typedef uint8_t        amplitude_t;   // signal amplitude
typedef float          frequency_t;   // signal frequency
