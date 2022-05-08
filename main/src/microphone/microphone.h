#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "../../sample_t.h"

void microphone_begin(uint8_t const port);  // 0 for A0

// Done with samples
//   Application signals that it no longer needs access to the samples.
//   This driver will reuse the "samples" buffer and start collecting
//   new samples.  Refer to top of file for details
void microphone_start(void);

samples_t microphone_get_samples(amplitude_t * const amplitudePtr);
