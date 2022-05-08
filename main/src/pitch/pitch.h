#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"
#include "../../segment_t.h"
#include "../../pitch_t.h"

class Pitch {

public:

	// constructors
	Pitch(void);
	Pitch(char const * const fullname);
	Pitch(noteNr_t const number, octaveNr_t const octave);
	Pitch(frequency_t const freq);

	// get
	char const *   getShortName(void) const;
	octaveNr_t     getOctaveNr(void) const;
	noteNr_t       getNoteNr(void) const;
	segmentPitch_t getPitch(void) const;
	frequency_t    getFrequency(void) const;

#if DST == DST_SERIAL
	static void serialOutHeader(void);
	void serialOut(char const * const instrument, Pitch & inPitch, frequency_t freq, amplitude_t const amplitude);
#endif

	static segmentPitch_t freq2pitch(frequency_t const freq);

private:
	struct NoteCv_t {
	  octaveNr_t octaveNr;
	  noteNr_t   noteNr;   // note# within octave
	} cv = {};  // class variables
};
