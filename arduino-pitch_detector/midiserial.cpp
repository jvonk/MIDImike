/**
 * @brief Send recorded notes over MIDI interface
 * @file  midiserial.cpp
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 */


#if DST == DST_PIANOROLL

#include <Arduino.h>
#include <stdint.h>
#include <SD.h>

#include "config.h"
#include "debug.h"
#include "pitch.h"
#include "sample_t.h"
#include "segment_t.h"
#include "segmentbuf.h"
#include "midi_t.h"
#include "midiserial.h"

namespace {

	// send 2 byte MIDI event
	void
	_send2ByteEvent( midiEvent_t const       event,
					 midiInstrument_t const  instrument )
	{
		Serial.write( (static_cast<uint8_t>(event) << 4) | (Config::MIDI_CHANNEL & 0x0F) );
		Serial.write( instrument & 0x7F );
	}


	// send 3 byte MIDI event
	void
	_send3ByteEvent( midiEvent_t const       event,
					 segmentPitch_t const    pitch,
					 segmentEnergy_t const velocity )
	{
		Serial.write( (static_cast<uint8_t>(event) << 4) | (Config::MIDI_CHANNEL & 0x0F) );
		Serial.write( pitch & 0x7F );
		Serial.write( velocity & 0x7F );
	}

} // name space


// Send notes over MIDIserial
void
MidiSerial::programChange( midiInstrument_t instrument )
{
	_send2ByteEvent(midiEvent_t::programChange, instrument);
}
void
MidiSerial::noteOn( segmentPitch_t const pitch,
					segmentEnergy_t const energy )
{
	_send3ByteEvent( midiEvent_t::noteOn, pitch, energy );
}

void
MidiSerial::noteOff( segmentPitch_t const pitch,
					 segmentEnergy_t const energy )
{
	_send3ByteEvent( midiEvent_t::noteOff, pitch, energy );
}

void
MidiSerial::send( SegmentBuf * const  segmentBuf )  // buffer with segmented notes
{
	programChange( Config::MIDI_INSTRUMENT );

	while ( segment_t const * note = segmentBuf->popPtr() ) {

		delay( note->onset );
		noteOn( note->pitch, note->energy );

		delay( note->duration );
		noteOff(note->pitch, note->energy);

	}
}
#endif
