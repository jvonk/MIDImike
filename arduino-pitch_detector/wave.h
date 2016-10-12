/**
 * @brief Read WAV audio files
 * @file wave.h
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
#include <SD.h>
#include "config.h"
#include "sample_t.h"

namespace Wave {

	  uint_least8_t const                                  // returns 0 if successful
		  readHeader( File &               f,              // file to read from [in]
					  sampleCnt_t * const  pNrOfSamples ); // total number of samples in file [out]


	  uint_least8_t const                               // returns 0 if successful
		  readSamples( File &             f,            // file to read from [in]
					   sampleCnt_t const  nrOfSamples,  // number of samples read [in]
					   samples_t          samples );    // samples read [out]
};
