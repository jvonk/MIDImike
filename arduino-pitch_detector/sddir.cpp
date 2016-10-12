/**
 * @brief Iterate through files on SD card
 * @file  sddir.cpp
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 *
 * Note: the functions themselves are non-reentrant
 **/


#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
#include "config.h"
#include "sddir.h"

namespace {
	// maximum level of sub directories to search
#define DIRLEVEL_MAX 2

	sddir_callback_t _callback = NULL;


	// Recursive search for files

	uint_least8_t const
	_walkDirectory( File &dir,                 // directory to start
		            uint_least8_t const lvl )  // current level
	{
		File f;
		uint_least8_t err = 0;
		static char instrumentName[8 + 1 + 3 + 1];

		while ( (f = dir.openNextFile()) && !err && _callback ) {

			if ( f.isDirectory() ) {
				if ( lvl < DIRLEVEL_MAX ) {
					if ( lvl == 0 ) {
						strcpy( instrumentName, f.name() );
					}
					err = _walkDirectory( f, lvl + 1 );  // recursive function call
				} else {
				}
			} else {
				err = _callback( f, instrumentName );  // call back registered function
			}
			f.close();
		}
		return err;
	}

}  // name space


// For each file in Directory

uint_least8_t const                              // returns 0 if successful
SdDir::forEachFile( char const * const dirName,  // directory (and its sub directories) to search
				    sddir_callback_t cb )        // function to call for each file found
{
	_callback = cb;

	File f = SD.open(dirName);
	uint_least8_t err = _walkDirectory(f, 0);

	f.close();
	return err;
}

uint_least8_t const
SdDir::begin( uint_least8_t const cs )
{
	if ( SD.begin( cs ) == false ) {  // declared in SD.cpp
		return 1;
	}
	return 0;
}