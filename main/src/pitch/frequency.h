#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"

#define CONFIG_MIDIMIKE_LAG_MAX (CONFIG_MIDIMIKE_WINDOW_SIZE / 2)
#define CONFIG_MIDIMIKE_FREQ_MIN (CONFIG_MIDIMIKE_SAMPLE_RATE / CONFIG_MIDIMIKE_LAG_MAX)
#define CONFIG_MIDIMIKE_FREQ_MAX (1568)
#if 0
#define CONFIG_MIDIMIKE_LAG_MIN (CONFIG_MIDIMIKE_SAMPLE_RATE / CONFIG_MIDIMIKE_FREQ_MAX -1)
#endif
#define CONFIG_MIDIMIKE_LAG_MIN (1)

#if 0
#define CONFIG_MIDIMIKE_LAG_MIN (6)                                                       // [samples] (not seconds!), 10 samples gives a +/-5% error rate (before interpolation)
#define CONFIG_MIDIMIKE_LAG_MAX (CONFIG_MIDIMIKE_WINDOW_SIZE / 2)                         // [samples] (not seconds!), at least two periods
#define CONFIG_MIDIMIKE_FREQ_MIN (CONFIG_MIDIMIKE_SAMPLE_RATE / CONFIG_MIDIMIKE_LAG_MAX)  // 96 Hz @ 9615 S/s
#define CONFIG_MIDIMIKE_FREQ_MAX (CONFIG_MIDIMIKE_SAMPLE_RATE / CONFIG_MIDIMIKE_LAG_MIN)  // 1602 Hz @ 9615 S/s and 6 min lag
#endif

frequency_t frequency_calculate(samples_t const samples);
