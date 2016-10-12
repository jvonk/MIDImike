/**
 * @brief Assert handler / memory tools / ..
 * @file  debug.cpp
 *
 * Platform: Arduino UNO R3 using Arduino IDE
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015, Coert Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#include <Arduino.h>
#include <stdint.h>
#include "config.h"
#include "debug.h"


	/********
	 * Assert
	 ********/

void
Debug::assertPrint( char const * const file, int const lineno)
{
	do {
		Serial.print( "ASSERT at " );
		Serial.print( file );
		Serial.print( ", " );
		Serial.println( lineno, DEC );
		Serial.flush();
	} while ( true );  // should be true for production
	//abort();  // ABORT PROGRAM
}

#if 0
	// __file is the name passed to the compiler.  Visual Micro passes the full path name,
	// and takes up a lot of memory.  Instead we use the ASSERT macro from debug.h
#define __ASSERT_USE_STDERR
#include <assert.h>
void
__assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
	while ( true ) {
		Serial.print( " fatal error, " );
		Serial.print( __func );  // __file takes up to much memory
		Serial.print( ":" );
		Serial.print( __lineno, DEC );
		Serial.print( ", assert(" );
		Serial.print( __sexp );
		Serial.println( ")" );
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

unsigned int const
Debug::getMemFree( void )
{
	int free_memory;
	free_memory = __brkval ? ((unsigned int)&free_memory) - ((unsigned int)__brkval)
		: ((unsigned int)&free_memory) - ((unsigned int)&__bss_end);

	return free_memory;
}


void
Debug::getMemInUse( unsigned int const ramend,
					unsigned int const sp,
					unsigned int * const dataSize,
					unsigned int * const bssSize,
					unsigned int * const heapSize,
					unsigned int * const stackSize )
{
	*dataSize = (unsigned int)&__data_end - (unsigned int)&__data_start;
	*bssSize = (unsigned int)&__bss_end - (unsigned int)&__bss_start;
	*heapSize = (unsigned int)__brkval - (unsigned int)&__heap_start;
	*stackSize = ramend - sp;
}

void
Debug::showMemUsage( void )
{
	uint16_t data, bss, heap, stack;
	Debug::getMemInUse( RAMEND, SP, &data, &bss, &heap, &stack );

	Serial.print( " data=" );  Serial.print( data, DEC );
	Serial.print( " bss=" );   Serial.print( bss, DEC );
	Serial.print( " heap=" );  Serial.print( heap, DEC );
	Serial.print( " stack=" ); Serial.print( stack, DEC );
	Serial.print( " free=" );  Serial.println( Debug::getMemFree(), DEC );
	Serial.flush();  // ensure delivery
}


	/**********
	 * Hex dump
	 **********/

void
Debug::hexDump( uint8_t const * p,    // pointer to 1st byte to display as hexadecimal
				uint16_t * const pos, // number of bytes already displayed
				uint16_t const n )    // number of bytes to display
{
	for ( uint16_t ii = 0; ii < n; ii++ ) {
		if ( *p < 0x10 ) {
			Serial.print( "0" );
		}
		Serial.print( *p, HEX );

		(*pos)++;
		if ( !(*pos % 32) ) {
			Serial.println();
		} else if ( !(*pos % 4) ) {
			Serial.print( " | " );
		} else {
			Serial.print( " " );
		}
		p++;
	}
}


#if 0
void
_printUint16( uint16_t v )
{
	uint8_t const msB = v >> 8;
	uint8_t const lsB = v & 0xFF;
	if ( msB < 16 ) {
		Serial.print( "0" );
	}
	Serial.print( msB, HEX );
	if ( lsB < 16 ) {
		Serial.print( "0" );
	}
	Serial.print( lsB, HEX );
	Serial.print( " " );
}
#endif



