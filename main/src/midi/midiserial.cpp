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


#include <Arduino.h>
#include <stdint.h>
#include <SdFat.h>

#include "../../config.h"
#include "../../sample_t.h"
#include "../../segment_t.h"
#include "../pitch/pitch.h"
#include "../segment/segment.h"
#include "../segment/segmentbuf.h"
#include "midi_t.h"
#include "midiserial.h"

static void
_send_2byte_event(midiEvent_t const       event,
				  midiInstrument_t const  instrument)
{
	Serial.write((static_cast<uint8_t>(event) << 4) | (CONFIG_MIDIMIKE_MIDI_CHANNEL & 0x0F));
	Serial.write(instrument & 0x7F);
}

static void
_send_3byte_event(midiEvent_t const      event,
				  segment_pitch_t const  pitch,
				  segment_energy_t const velocity)
{
	Serial.write((static_cast<uint8_t>(event) << 4) | (CONFIG_MIDIMIKE_MIDI_CHANNEL & 0x0F));
	Serial.write(pitch & 0x7F);
	Serial.write(velocity & 0x7F);
}

void
midiserial_send_note_on(segment_pitch_t const pitch,
                        segment_energy_t const energy)
{
	_send_3byte_event(MIDIEVENT_NOTE_ON, pitch, energy);
}

void
midiserial_send_note_off(segment_pitch_t const pitch,
                         segment_energy_t const energy)
{
	_send_3byte_event(MIDIEVENT_NOTE_OFF, pitch, energy);
}

void
midiserial_send_program_change(midiInstrument_t instrument)
{
	_send_2byte_event(MIDIEVENT_PROGRAM_CHANGE, instrument);
}

void
midiserial_send_notes(SegmentBuf * const segmentBuf)  // buffer with segmented notes
{
	midiserial_send_program_change(CONFIG_MIDIMIKE_MIDI_INSTRUMENT);

	while (segment_t const * note = segmentBuf->pop_ptr()) {

		delay(note->onset);
		midiserial_send_note_on(note->pitch, note->energy);

		delay(note->duration);
		midiserial_send_note_off(note->pitch, note->energy);
	}
}
