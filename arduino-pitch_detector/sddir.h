/**
 * @brief Iterate through files on SD card
 * @file  sddir.h
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

	// call back function definition
typedef uint_least8_t const (* sddir_callback_t)(File & f, char * instrument);

namespace SdDir {

	  uint_least8_t const
		  begin( uint_least8_t const cs );          // SD card CS pin

	  uint_least8_t const                           // returns 0 if successful
		  forEachFile( char const * const dirName,  // directory (and its sub directories) to search
					   sddir_callback_t   cb);      // function to call for each file found
};
