#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "sample_t.h"
#include "segment_t.h"
#include "pitch_t.h"

class Pitch {

public:

	// constructors
	Pitch( void );
	Pitch( char const * const fullname );
	Pitch( noteNr_t const number, octaveNr_t const octave );
	Pitch( frequency_t const freq );

	// get
	char const *    getShortName( void ) const;  // get note name (w/o octave#)
	octaveNr_t      getOctaveNr( void ) const;   // get octave number
	noteNr_t        getNoteNr( void ) const;     // get note number
	segmentPitch_t  getPitch( void ) const;      // get midi pitch
	frequency_t     getFrequency( void ) const;  // get frequency

#if DST == DST_SERIAL
	static void
		serialOutHeader( void );

	void
		serialOut( char const * const  instrument,   // instrument name
		           Pitch &             inPitch,      // note from file
				   frequency_t         freq,         // frequency measured
				   amplitude_t const   amplitude );  // amplitude measured
#endif

	static segmentPitch_t
		freq2pitch( frequency_t const freq ); // calculate midi pitch from frequency

private:
	struct NoteCv_t {
	  octaveNr_t octaveNr;
	  noteNr_t   noteNr;   // note# within octave
	} cv;  // class variables
};
