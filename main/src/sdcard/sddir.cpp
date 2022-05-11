/**
 * @brief Iterate through files on SD card
 * 
 * Note: the functions themselves are non-reentrant
 *
 * © Copyright 2015-2016,2022 Johan Vonk
 * 
 * This file is part of Arduino_pitch-detector.
 * 
 * Arduino_pitch-detector is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * Arduino_pitch-detector is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Arduino_pitch-detector. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright 2015-2016,2022 Johan Vonk
 **/

#include <Arduino.h>
#include <stdint.h>
#define ENABLE_DEDICATED_SPI (1)
#include <SdFat.h>

#include "../../config.h"
#include "../debug/debug.h"
#include "sddir.h"

// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 0

// SDCARD_SS_PIN is defined for the built-in SD on some boards.
const uint8_t SD_CS_PIN = 4;

#define SPI_CLOCK SD_SCK_MHZ(50)

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif  ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif  // HAS_SDIO_CLASS

// FAT type 0 only
SdFat sd;

#define error(s) sd.errorHalt(&Serial, F(s))



    /************
     * initialize
     ************/

uint_least8_t                           // returns 0 if successful, otherwise returns 1
sddir_init(uint_least8_t const cs_pin)  // GPIO# used for SD Chip Select pin
{
	return !sd.begin(cs_pin);
}

#if (SRC == SRC_FILE)

// maximum level of sub directories to search
#define DIRLEVEL_MAX (2)

    /****************************
     * recursively walk directory
     ****************************/ 

static uint_least8_t                     // returns 0 if successful
_walkDirectory(File & dir,               // directory to start at
               uint_least8_t const lvl,  // current level
               sddir_callback_t cb_fnc)  // function to call for each file
{
	uint_least8_t err = 0;
	static char instrumentName[8 + 1 + 3 + 1];

    File file;
    while (file.openNext(&dir, O_RDONLY)) {
        if (file.isDir()) {
			if (lvl < DIRLEVEL_MAX) {
				if (lvl == 0) {
                    file.getName8(instrumentName, sizeof(instrumentName));
                    //Serial.println(instrumentName);
				}
				err = _walkDirectory(file, lvl + 1, cb_fnc);  // recursive function call
            }
        } else {            
            //file.printName(&Serial);
			err = (*cb_fnc)(file, instrumentName);  // call back registered function
        }
        file.close();
    }

#if 0
	File f;
	while ((f = dir.openNextFile()) && !err && cb_fnc) {

		if (f.isDirectory()) {
			if (lvl < DIRLEVEL_MAX) {
				if (lvl == 0) {
					strcpy(instrumentName, f.name());
				}
				err = _walkDirectory(f, lvl + 1, cb_fnc);  // recursive function call
            }
		} else {
            // Serial.println(f.name());
			err = (*cb_fnc)(f, instrumentName);  // call back registered function
		}
		f.close();
	}
#endif    
	return err;
}

    /****************************
     * for each file in directory
     **************************** 
     * Problems?  Try using a >= 2G formatted as FAT using https://www.sdcard.org/downloads/formatter/
     */

uint_least8_t                                           // returns 0 if successful
sddir_for_each_file_in_dir(char const * const dirName,  // directory (and its sub directories) to search
                           sddir_callback_t cb_fnc)     // function to call for each file found
{
    File dir;

    //Serial.print("for1 free="); Serial.println(Debug::freeMemory());

    if (!dir.open(dirName)){
        error("dir.open failed");
    }

    //Serial.print("for2 free="); Serial.println(Debug::freeMemory());

	uint_least8_t err = _walkDirectory(dir, 0, cb_fnc);

	dir.close();
	return err;
}

#endif

