/**
 * @brief Assert handler / memory tools / ..
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
#include "../../config.h"
#include "debug.h"

extern char *__brkval;

int 
debug_freeMemory() {
  char top;
  return &top - __brkval;
}

#if 1

void
debug_assertPrint(char const * const file, int const lineno)
{
	do {
		Serial.print(F("ASSERT at "));
		Serial.print(file);
		Serial.print(F(", "));
		Serial.println(lineno, DEC);
		Serial.flush();
	} while (true);  // should be true for production
	//abort();  // ABORT PROGRAM
}

	// __file is the name passed to the compiler.  Visual Micro passes the full path name,
	// and takes up a lot of memory.  Instead we use the ASSERT macro from debug.h
#define __ASSERT_USE_STDERR
#include <assert.h>
void
__assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
	while (true) {
        (void) __file;
		Serial.print(F(" fatal error, "));
		Serial.print(__func);  // __file takes up to much memory
		Serial.print(":");
		Serial.print(__lineno, DEC);
		Serial.print(F(", assert("));
		Serial.print(__sexp);
		Serial.println(F(")"));
		Serial.flush();
	}
	//abort();  // ABORT PROGRAM
}

void
debug_tryAssert() {
	for (uint8_t i = 0; i < 3; i++) {
		delay(1000);  // wait for a second
	}

	// make assertion failed.
	assert(1 == 2);
}

void
debug_hex_dump(uint8_t const * p,    // pointer to 1st byte to display as hex
			   uint16_t * const pos, // number of bytes already displayed
			   uint16_t const n)     // number of bytes to display
{
	for (uint16_t ii = 0; ii < n; ii++) {
		if (*p < 0x10) {
			Serial.print(F("0"));
		}
		Serial.print(*p, HEX);

		(*pos)++;
		if (!(*pos % 32)) {
			Serial.println();
		} else if (!(*pos % 4)) {
			Serial.print(F(" | "));
		} else {
			Serial.print(F(" "));
		}
		p++;
	}
}

#endif