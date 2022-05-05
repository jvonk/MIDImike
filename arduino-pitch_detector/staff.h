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
