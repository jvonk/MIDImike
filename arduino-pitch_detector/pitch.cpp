/**
 * @brief Pitch Class, maps between frequency and note pitch
 * @file pitch.cpp
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "pitch.h"

namespace {

	struct note_t {
		char const * const   name;
		frequency_t const    freq;
		frequency_t const    freqMax; // up to, but not including
	};

	// note: calculating the values would probably take up more memory
	note_t const _notes[static_cast<int>(noteNr_t::COUNT)] = {
		{"C", 16.35159783, 16.83073622},
		{"Db", 17.32391444, 17.83154388},
		{"D", 18.35404799, 18.89186265},
		{"Eb", 19.44543648, 20.01523126},
		{"E", 20.60172231, 21.20539885},
		{"F", 21.82676446, 22.46633748},
		{"Gb", 23.12465142, 23.80225543},
		{"G", 24.49971475, 25.21761119},
		{"Ab", 25.95654360, 26.71712838},
		{"A", 27.5, 28.30581151},
		{"Bb", 29.13523509, 29.98896265},
		{"B", 30.86770633, 31.77219916}
	};

}  // name space


Pitch::Pitch( void )
{
	cv.noteNr = noteNr_t::C;
	cv.octaveNr = 0;
}


Pitch::Pitch( char const * const fullname )  // construct based on note name w/ octave# e.g. "Gb4"
{
	// get octave# from the last char
	uint_fast8_t len = strlen( fullname );
	cv.octaveNr = fullname[len - 1] - '0';

	// chars before octave# are the note name itself
	bool found = false;
	note_t const * nn = _notes;
	uint_least8_t max = static_cast<int>(noteNr_t::COUNT);

	for ( uint_least8_t ii = 0; ii < max && !found; ii++, nn++ ) {
		if ( (nn->name[0] == fullname[0]) &&
			((nn->name[1] == '\0' && len < 3) ||
			(nn->name[1] == fullname[1])) ) {
			cv.noteNr = static_cast<noteNr_t>(ii);
			found = true;
		}
	}

	if ( !found ) {
		cv.noteNr = noteNr_t::C;
		cv.octaveNr = 0;
	}
}


Pitch::Pitch( frequency_t const freq )  // construct based on frequency
{
	frequency_t f = freq;

	if ( f ) { //2BD:  f > FREQ_MIN && f < FREQ_MAX ) {

			// scale down frequency to octave 0, noting the # of octaves shifted
		cv.octaveNr = 0;
		uint_least8_t const notesCnt = sizeof( _notes ) / sizeof( _notes[0] );

		while ( f >= _notes[notesCnt - 1].freqMax ) {
			cv.octaveNr++;
			f /= 2;
		}
		for ( uint_least8_t ii = 0; ii < notesCnt; ii++ ) {
			if ( f < _notes[ii].freqMax ) {
				cv.noteNr = static_cast<noteNr_t>(ii);
				break;
			}
		}

	} else {
		cv.noteNr = noteNr_t::C;
		cv.octaveNr = 0;
	}
}


Pitch::Pitch( noteNr_t const number,    // note# with the octave
			  octaveNr_t const octave ) // octave#
{
	if ( number < noteNr_t::COUNT ) {
		cv.noteNr = number;
		cv.octaveNr = octave;
	} else {
		cv.noteNr = noteNr_t::C;
		cv.octaveNr = 0;
	}
}


char const * const
Pitch::getShortName( void ) const
{
	int const idx = static_cast<int>(cv.noteNr);

	return _notes[idx].name;
}

#if DST == DST_SERIAL

void
Pitch::serialOutHeader(void)
{
	Serial.println( "" );
	Serial.print( "instrument samplefreq buffsize noteoctave freq => " );
	Serial.print( Config::WINDOW_SIZE );
	Serial.print( " " );
	Serial.println( Config::WINDOW_SIZE );
}


void
Pitch::serialOut( char const * const  instrument,   // instrument name
				  Pitch &             inPitch,      // note from file
				  frequency_t         freq,         // frequency measured
				  amplitude_t const   amplitude )   // amplitude measured
{
	Serial.print( instrument ); Serial.print( " " );
	Serial.print( Config::SAMPLE_RATE ); Serial.print( " " );
	Serial.print( Config::WINDOW_SIZE ); Serial.print( " " );

	if ( inPitch.getFrequency() ) {  // do not show for microphone input
		Serial.print( inPitch.getShortName() );
		Serial.print( inPitch.getOctaveNr() );
		if ( strlen( inPitch.getShortName() ) < 2 ) {
			Serial.print( " " );
		}
		Serial.print( " " );
		Serial.print( inPitch.getFrequency() );
	}

	if ( this->getPitch() > 0 ) {
		Serial.print( " => " );
		Serial.print( freq );
		Serial.print( " " );
		Serial.print( this->getShortName() );
		Serial.print( this->getOctaveNr() );
		if ( strlen( this->getShortName() ) < 2 ) {
			Serial.print( " " );
		}
	}
	Serial.println();
}

#endif


frequency_t const
Pitch::getFrequency( void ) const
{
	uint8_t const notesCnt = sizeof(_notes) / sizeof(_notes[0]);
	uint_least8_t const idx = static_cast<uint_least8_t>(cv.noteNr);

	if ( idx >= notesCnt ||
		( cv.noteNr == noteNr_t::C && cv.octaveNr == 0) ) {
		return 0;
	}
	float freq = _notes[idx].freq;

	uint_least8_t octave = cv.octaveNr;
	while ( octave ) {
		freq *= 2;
		octave--;
	}
	return freq;
}


noteNr_t const
Pitch::getNoteNr( void ) const
{
	return cv.noteNr;
}

octaveNr_t const
Pitch::getOctaveNr( void ) const
{
	return cv.octaveNr;
}

segmentPitch_t const
Pitch::getPitch( void ) const
{
	return cv.octaveNr * 12 + static_cast<segmentPitch_t>(cv.noteNr);
}

segmentPitch_t const
Pitch::freq2pitch( frequency_t const freq )  // returns the midi pitch for a given frequency
{
	return freq < Config::FREQ_MIN ? 0 : 69.0 + 12.0 * log( freq / 440.0 ) / log( 2 );
}
