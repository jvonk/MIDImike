#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
#include "../../config.h"
#include "../../sample_t.h"

uint_least8_t wave_read_hdr(File &f, sample_cnt_t * const sample_count_p);
uint_least8_t wave_read_samples(File &f, sample_cnt_t const sample_cnt, samples_t samples);
