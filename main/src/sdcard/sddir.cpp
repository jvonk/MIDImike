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
#include <SD.h>

#include "../../config.h"
#include "sddir.h"

// maximum level of sub directories to search
#define DIRLEVEL_MAX (2)

sddir_callback_t _callback = NULL;

static uint_least8_t
_walkDirectory(File &dir,                // directory to start
			   uint_least8_t const lvl)  // current level
{
	File f;
	uint_least8_t err = 0;
	static char instrumentName[8 + 1 + 3 + 1];

	while ((f = dir.openNextFile()) && !err && _callback) {

		if (f.isDirectory()) {
			if (lvl < DIRLEVEL_MAX) {
				if (lvl == 0) {
					strcpy(instrumentName, f.name());
				}
				err = _walkDirectory(f, lvl + 1);  // recursive function call
			} else {
			}
		} else {
			err = _callback(f, instrumentName);  // call back registered function
		}
		f.close();
	}
	return err;
}

// for each file in Directory

uint_least8_t                                    // returns 0 if successful
sddir_for_each_file(char const * const dirName,  // directory (and its sub directories) to search
				    sddir_callback_t cb)         // function to call for each file found
{
	_callback = cb;

	File f = SD.open(dirName);
	uint_least8_t err = _walkDirectory(f, 0);

	f.close();
	return err;
}

uint_least8_t
sddir_init(uint_least8_t const cs_pin)
{
	if (SD.begin(cs_pin) == false) {
		return 1;
	}
	return 0;
}
