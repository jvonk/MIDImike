/**
 * @brief Frequency detector, using auto correlation to find frequency (f0) in signal
 * @file  frequency.h
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
#include "sample_t.h"

namespace Frequency {

	frequency_t const                           // returns frequency found, 0 when not found
		calculate( samples_t const  samples );  // pointer to signed 8-bit data samples [in]

};

