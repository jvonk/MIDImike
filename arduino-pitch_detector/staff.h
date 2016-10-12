/**
 * @brief Show music notes on tremble clef
 * @file  staff.h
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

class Note;

namespace Staff {

	  void
		  begin( uint_least8_t tftCS,    // SPI TFT Chip Select
		         uint_least8_t dc,       // SPI Data/Command
		         uint_least8_t reset );  // SPI Reset

	  // end() function not needed, 'cause loop() never stops

	  void
		  showNote( Pitch &           pitch,       // pitch measured
		            amplitude_t const amplitude ); // amplitude measured
};
