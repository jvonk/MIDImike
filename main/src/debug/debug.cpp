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
Debug::freeMemory() {
  char top;
  return &top - __brkval;
}

#if 0

	/********
	 * Assert
	 ********/

void
debug_assertPrint(char const * const file, int const lineno)
{
	do {
		Serial.print("ASSERT at ");
		Serial.print(file);
		Serial.print(", ");
		Serial.println(lineno, DEC);
		Serial.flush();
	} while (true);  // should be true for production
	//abort();  // ABORT PROGRAM
}


#if 0
	// __file is the name passed to the compiler.  Visual Micro passes the full path name,
	// and takes up a lot of memory.  Instead we use the ASSERT macro from debug.h
#define __ASSERT_USE_STDERR
#include <assert.h>
void
__assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
	while (true) {
		Serial.print(" fatal error, ");
		Serial.print(__func);  // __file takes up to much memory
		Serial.print(":");
		Serial.print(__lineno, DEC);
		Serial.print(", assert(");
		Serial.print(__sexp);
		Serial.println(")");
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
#endif


	/*******
	 * Memory
	 ********/

extern unsigned int __data_start;
extern unsigned int __data_end;
extern unsigned int __bss_start;
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void * __brkval;

unsigned int
Debug::getMemFree(void)
{
	int free_memory;
	free_memory = __brkval ? ((unsigned int)&free_memory) - ((unsigned int)__brkval)
		                   : ((unsigned int)&free_memory) - ((unsigned int)&__bss_end);

	return free_memory;
}

void
Debug::getMemInUse(unsigned int const ramend,
				   unsigned int const sp,
				   unsigned int * const dataSize,
				   unsigned int * const bssSize,
				   unsigned int * const heapSize,
				   unsigned int * const stackSize)
{
	*dataSize = (unsigned int)&__data_end - (unsigned int)&__data_start;
	*bssSize = (unsigned int)&__bss_end - (unsigned int)&__bss_start;
	*heapSize = (unsigned int)__brkval - (unsigned int)&__heap_start;
	*stackSize = ramend - sp;
}

void
Debug::showMemUsage(void)
{
	uint16_t data, bss, heap, stack;
	Debug::getMemInUse(RAMEND, SP, &data, &bss, &heap, &stack);

	Serial.print(" data=");  Serial.print(data, DEC);
	Serial.print(" bss=");   Serial.print(bss, DEC);
	Serial.print(" heap=");  Serial.print(heap, DEC);
	Serial.print(" stack="); Serial.print(stack, DEC);
	Serial.print(" free=");  Serial.println(Debug::getMemFree(), DEC);
	Serial.flush();  // ensure delivery
}


	/**********
	 * Hex dump
	 **********/

void
Debug::hexDump(uint8_t const * p,    // pointer to 1st byte to display as hexadecimal
				uint16_t * const pos, // number of bytes already displayed
				uint16_t const n)    // number of bytes to display
{
	for (uint16_t ii = 0; ii < n; ii++) {
		if (*p < 0x10) {
			Serial.print("0");
		}
		Serial.print(*p, HEX);

		(*pos)++;
		if (!(*pos % 32)) {
			Serial.println();
		} else if (!(*pos % 4)) {
			Serial.print(" | ");
		} else {
			Serial.print(" ");
		}
		p++;
	}
}

#endif