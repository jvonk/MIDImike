#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"

void microphone_begin(uint8_t const port);  // 0 for A0
void microphone_start(void);
samples_t microphone_get_samples(amplitude_t * const amplitudePtr);
