#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SdFat.h>
#include "../pitch/pitch.h"

uint_least8_t calcnote_from_file(File & f, char * instrument);
void calcnote_write_serial_hdr(void);
void calcnote_write_serial(char const * const instrument, Pitch & in_pitch, Pitch & measured_pitch, frequency_t freq);
