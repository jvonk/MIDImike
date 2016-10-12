/**
 * @brief Note level segmentation, based on Monty's method, 2000.
 * @file  segment.cpp
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
#include "config.h"
#include "pitch.h"
#include "cbuf.h"
#include "segment_t.h"
#include "segment.h"
#include "segmentbuf.h"
#include "midiserial.h"

namespace {
	segmentEnergy_t const SEGMENT_ENERGY_INCR_THRESHOLD = 40;  // [%]
}

void
Segment::energyInit_( segmentEnergyTrend_t * const trend )
{
	MidiSerial::programChange(Config::MIDI_INSTRUMENT);
	trend->previous = 0;
	trend->state = segmentEnergyState_t::findNegSlope;
}


void
Segment::energyUpdate_( segmentEnergyTrend_t  * const trend,
						segmentEnergy_t const        energy )
{
	switch ( trend->state ) {
		case segmentEnergyState_t::findNegSlope:
			if ( energy < trend->previous ) {  // downward slope started
				trend->min = energy;
				trend->state = segmentEnergyState_t::findPosSlope;
			} else {
				trend->max = energy;
			}
			break;
		case segmentEnergyState_t::findPosSlope:
			if ( energy > trend->previous ) {  // energy increasing again
				if ( energy > ((100 + SEGMENT_ENERGY_INCR_THRESHOLD) * trend->min) / 100 ) {
					trend->state = segmentEnergyState_t::foundPosSlope;  // trend on the rise again
				}
			} else {
				trend->min = energy;
			}
			break;
		case segmentEnergyState_t::foundPosSlope:
			break;
	}
	trend->previous = energy;
}


Segment::Segment( void )
{
	cv.candidate.pitch = 0;
	cv.prevEndTime = millis();
	this->energyInit_( &cv.energyTrend );
	cv.note = NULL;
}

segmentRelTime_t const
Segment::difftime_( absoluteTime_t const t )
{
	absoluteTime_t const t0 = cv.lastEventTime;
	cv.lastEventTime = t;

	// subtraction of two unsigned values will produce the correct answer even if one of them has over flowed
	return t - t0;
}


// Updates:
//   - when an note onset is detected, a note (with offset 0) is added to the midi buffer.
//   - when the amplitude peak is detected, the velocity is updated in the midi buffer.
//   - when the note offset is detected, the 'offset' for the note is updated in the midi buffer.

void
Segment::put( absoluteTime_t const   now,          // absolute current time (at the end of chunk) [msec]
			  segmentPitch_t const   pitch,        // midi pitch measured
			  segmentEnergy_t const  energy,       // energy/loudness measured [0..127]
			  SegmentBuf * const     segmentBuf )  // segment buffer to write note to
{
	absoluteTime_t t = 0;  // init to please compiler
	bool startNewNote = false;
	bool stopCurrentNote = false;

	if ( cv.note ) {
		cv.note->duration = now - cv.lastEventTime;  // update needed for piano roll display
		cv.lastOffset = now;
	}

	// note start/stop
	if ( pitch ) {

		if ( pitch == cv.candidate.pitch ) {

			bool const meetsMinDuration = now - cv.candidate.startTime > Config::MIN_SEGMENT_DURATION;
			bool const noteFollowingRest = !cv.note;
			bool const pitchChanged = cv.candidate.pitch != cv.note->pitch;
			bool const energyIncreasing = cv.energyTrend.state == segmentEnergyState_t::foundPosSlope;

			if ( meetsMinDuration && (noteFollowingRest || pitchChanged || energyIncreasing) ) {
				t = cv.candidate.startTime;
				if ( cv.note ) {               
					stopCurrentNote = true;  // EXISTING NOTE TERMINATED BY THE START OF A NEW NOTE
				}
				startNewNote = true;  // NEW NOTE STARTS AFTER REST
			}
			energyUpdate_( &cv.candidate.energyTrend, energy );

		} else {  // this becomes the new candidate
			cv.candidate.startTime = cv.prevEndTime;
			cv.candidate.pitch = pitch;
			energyInit_( &cv.candidate.energyTrend );
		}

	} else {

		if ( cv.note ) {  // EXISTING NOTE TERMINATED BY REST
			cv.candidate.pitch = 0;
			t = cv.prevEndTime;
			stopCurrentNote = true;
		}
	}

	if ( stopCurrentNote ) {
		MidiSerial::noteOff(cv.note->pitch, 0);
		//MidiSerial::programChange(random(1, 52));
		cv.note = segmentBuf->noteEnd( difftime_( t ), cv.energyTrend.max, cv.note );
		cv.lastOffset = t;

	}

	if ( startNewNote ) {
		MidiSerial::noteOn(pitch, energy);
		if ( segmentBuf->len() == 0 ) {  // first segment should have relative time=0
			cv.lastEventTime = t;
		}
		cv.note = segmentBuf->noteStart( difftime_( t ), now - t, pitch, energy );
		cv.lastOffset = now;
		cv.energyTrend = cv.candidate.energyTrend;

	}

	// update energy level trend (2BD should stop when a new candidate presents itself)
	if ( cv.note ) {
		energyUpdate_( &cv.energyTrend, energy );
	}  else {
		cv.energyTrend.previous = pitch ? energy : 0;
	}
	this->cv.prevEndTime = now;
}


absoluteTime_t const
Segment::getLastOffset( void )
{
	return this->cv.lastOffset;
}

