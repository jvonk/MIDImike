#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SdFat.h>
#include "../../config.h"
#include "../../sample_t.h"

uint_least8_t wave_read_samples(File &f, char * const  note_name, size_t note_name_len, sample_t * const samples, amplitude_t * amplitude);