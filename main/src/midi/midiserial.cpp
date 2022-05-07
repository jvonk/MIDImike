/**
 * @brief Send recorded notes over MIDI interface
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
 */


#if DST == DST_PIANOROLL

#include <Arduino.h>
#include <stdint.h>
#include <SD.h>

#include "../../config.h"
#include "../../debug.h"
#include "../../sample_t.h"
#include "../../midi_t.h"
#include "../../segment_t.h"
#include "../pitch/pitch.h"
#include "../segment/segmentbuf.h"
#include "midiserial.h"

namespace {

	// send 2 byte MIDI event
	void
	_send2ByteEvent( midiEvent_t const       event,
					 midiInstrument_t const  instrument )
	{
		Serial.write( (static_cast<uint8_t>(event) << 4) | (CONFIG_MIDIMIKE_MIDI_CHANNEL & 0x0F) );
		Serial.write( instrument & 0x7F );
	}


	// send 3 byte MIDI event
	void
	_send3ByteEvent( midiEvent_t const       event,
					 segmentPitch_t const    pitch,
					 segmentEnergy_t const velocity )
	{
		Serial.write( (static_cast<uint8_t>(event) << 4) | (CONFIG_MIDIMIKE_MIDI_CHANNEL & 0x0F) );
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
	programChange( CONFIG_MIDIMIKE_MIDI_INSTRUMENT );

	while ( segment_t const * note = segmentBuf->popPtr() ) {

		delay( note->onset );
		noteOn( note->pitch, note->energy );

		delay( note->duration );
		noteOff(note->pitch, note->energy);

	}
}
#endif
