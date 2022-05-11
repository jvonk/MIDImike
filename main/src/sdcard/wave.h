#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
#include "../../config.h"
#include "../../sample_t.h"

uint_least8_t wave_read_samples(File &f, char * const  noteName, sample_t * const samples, amplitude_t * amplitude);