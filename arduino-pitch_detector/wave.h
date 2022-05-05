#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
#include "config.h"
#include "sample_t.h"

namespace Wave {

	  uint_least8_t                                        // returns 0 if successful
		  readHeader( File &               f,              // file to read from [in]
					  sampleCnt_t * const  pNrOfSamples ); // total number of samples in file [out]


	  uint_least8_t                                     // returns 0 if successful
		  readSamples( File &             f,            // file to read from [in]
					   sampleCnt_t const  nrOfSamples,  // number of samples read [in]
					   samples_t          samples );    // samples read [out]
};
