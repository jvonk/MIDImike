/**
 * @brief Send notes over MIDI interface
 * @file midiserial.h
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "segment_t.h"

namespace MidiSerial {

	/**
	@brief Send notes over MIDIserial
	@param   [in]   segmentBuf    Buffer with segmented notes
	**/
	void
		send( SegmentBuf * const  segmentBuf );

	void
		noteOn(segmentPitch_t const pitch,
		       segmentEnergy_t const energy);

	void
		noteOff(segmentPitch_t const pitch,
		        segmentEnergy_t const energy);

	void
		programChange(midiInstrument_t instrument);

};
