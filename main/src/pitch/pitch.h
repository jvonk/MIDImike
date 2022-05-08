#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"
#include "../../segment_t.h"
#include "../../pitch_t.h"

pitch_t pitch_get(char const * const fullname);
pitch_t pitch_get(notenr_t const number, octavenr_t const octave);
pitch_t pitch_get(frequency_t const freq);

char const * pitch_shortname(pitch_t const * const pitch);
octavenr_t pitch_octavenr(pitch_t const * const pitch);
notenr_t pitch_notenr(pitch_t const * const pitch);
segmentPitch_t pitch_segment(pitch_t const * const pitch);
frequency_t pitch_frequency(pitch_t const * const pitch);
segmentPitch_t pitch_freq2segment(frequency_t const freq);

#if DST == DST_SERIAL
void pitch_write_serial_hdr(void);
void pitch_write_serial(pitch_t const * const pitch, char const * const instrument, frequency_t freq, amplitude_t const amplitude);
#endif
