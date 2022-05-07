#pragma once

#include <Arduino.h>
#include <stdint.h>

	// call back function definition
typedef uint_least8_t (* sddir_callback_t)(File & f, char * instrument);

namespace SdDir {

	  uint_least8_t
		  begin( uint_least8_t const cs );          // SD card CS pin

	  uint_least8_t                         // returns 0 if successful
		  forEachFile( char const * const dirName,  // directory (and its sub directories) to search
					   sddir_callback_t   cb);      // function to call for each file found
};
