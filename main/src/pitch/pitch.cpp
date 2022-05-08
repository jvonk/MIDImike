/**
 * @brief Pitch Class, maps between frequency and note pitch
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
#include <string.h>

#include "../../config.h"
#include "pitch.h"

typedef struct note_t {
	char const * const name;
	frequency_t const  freq;
	frequency_t const  freq_max; // up to, but not including
} note_t;

// note: calculating the values would probably take up more memory
static note_t const _notes[NOTENR_COUNT] = {
	{"C",  16.35159783, 16.83073622},
	{"Db", 17.32391444, 17.83154388},
	{"D",  18.35404799, 18.89186265},
	{"Eb", 19.44543648, 20.01523126},
	{"E",  20.60172231, 21.20539885},
	{"F",  21.82676446, 22.46633748},
	{"Gb", 23.12465142, 23.80225543},
	{"G",  24.49971475, 25.21761119},
	{"Ab", 25.95654360, 26.71712838},
	{"A",  27.50000000, 28.30581151},
	{"Bb", 29.13523509, 29.98896265},
	{"B",  30.86770633, 31.77219916}
};

// constructors

pitch_t 
pitch_get(char const * const fullname)  // note name w/ octave# e.g. "Gb4"
{
	pitch_t pitch;

	// get octave# from the last char
	uint_fast8_t len = strlen(fullname);
	pitch.octavenr = fullname[len - 1] - '0';

	// chars before octave# are the note name itself
	bool found = false;
	note_t const * nn = _notes;
	uint_least8_t max = static_cast<int>(NOTENR_COUNT);

	for (uint_least8_t ii = 0; ii < max && !found; ii++, nn++) {
		if ((nn->name[0] == fullname[0]) &&
			((nn->name[1] == '\0' && len < 3) ||
			(nn->name[1] == fullname[1]))) {
			pitch.notenr = static_cast<notenr_t>(ii);
			found = true;
		}
	}

	if (!found) {
		pitch.octavenr = 0;
		pitch.notenr = NOTENR_C;
	}
	return pitch;
}

pitch_t 
pitch_get(frequency_t const freq)
{
	pitch_t pitch;
	frequency_t f = freq;

	if (f) { //2BD:  f > FREQ_MIN && f < FREQ_MAX) {

			// scale down frequency to octave 0, noting the # of octaves shifted
		pitch.octavenr = 0;

		while (f >= _notes[NOTENR_COUNT - 1].freq_max) {
			pitch.octavenr++;
			f /= 2;
		}
		for (uint_least8_t ii = 0; ii < NOTENR_COUNT; ii++) {
			if (f < _notes[ii].freq_max) {
				pitch.notenr = static_cast<notenr_t>(ii);
				break;
			}
		}

	} else {
		pitch.notenr = NOTENR_C;
		pitch.octavenr = 0;
	}
	return pitch;
}

pitch_t 
pitch_get(notenr_t const number,    // note# with the octave
		  octavenr_t const octave)  // octave#
{
	pitch_t pitch;

	if (number < NOTENR_COUNT) {
		pitch.notenr = number;
		pitch.octavenr = octave;
	} else {
		pitch.notenr = NOTENR_C;
		pitch.octavenr = 0;
	}
	return pitch;
}

// public methods

char const *
pitch_shortname(pitch_t const * const pitch)
{
	int const idx = pitch->notenr;

	return _notes[idx].name;
}

frequency_t
pitch_frequency(pitch_t const * const pitch)
{
	uint8_t const notesCnt = sizeof(_notes) / sizeof(_notes[0]);
	uint_least8_t const idx = static_cast<uint_least8_t>(pitch->notenr);

	if (idx >= notesCnt ||
		(pitch->notenr == NOTENR_C && pitch->octavenr == 0)) {
		return 0;
	}
	float freq = _notes[idx].freq;

	uint_least8_t octave = pitch->octavenr;
	while (octave) {
		freq *= 2;
		octave--;
	}
	return freq;
}

notenr_t
pitch_notenr(pitch_t const * const pitch)
{
	return pitch->notenr;
}

octavenr_t
pitch_octavenr(pitch_t const * const pitch)
{
	return pitch->octavenr;
}

segmentPitch_t
pitch_segment(pitch_t const * const pitch)
{
	return pitch->octavenr * 12 + static_cast<segmentPitch_t>(pitch->notenr);
}

segmentPitch_t
pitch_freq2segment(frequency_t const freq)  // returns the midi pitch for a given frequency
{
	return freq < CONFIG_MIDIMIKE_FREQ_MIN ? 0 : 69.0 + 12.0 * log(freq / 440.0) / log(2);
}

#if DST == DST_SERIAL

void
pitch_write_serial_hdr(void)
{
	Serial.println("");
	Serial.print("instrument samplefreq buffsize noteoctave freq => ");
	Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE);
	Serial.print(" ");
	Serial.println(CONFIG_MIDIMIKE_WINDOW_SIZE);
}

void
pitch_write_serial(pitch_t const * const pitch,       // note from file
				   char const * const    instrument,  // instrument name
				   frequency_t           freq,        // frequency measured
				   amplitude_t const     amplitude)   // amplitude measured
{
	(void) amplitude;
	Serial.print(instrument); Serial.print(" ");
	Serial.print(CONFIG_MIDIMIKE_SAMPLE_RATE); Serial.print(" ");
	Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE); Serial.print(" ");

	if (pitch_frequency(pitch)) {  // do not show for microphone input
		Serial.print(pitch_shortname(pitch));
		Serial.print(pitch_octavenr(pitch));
		if (strlen(pitch_shortname(pitch)) < 2) {
			Serial.print(" ");
		}
		Serial.print(" ");
		Serial.print(pitch_frequency(pitch));
	}

	if (pitch_segment(pitch) > 0) {
		Serial.print(" => ");
		Serial.print(freq);
		Serial.print(" ");
		Serial.print(pitch_shortname(pitch));
		Serial.print(pitch_octavenr(pitch));
		if (strlen(pitch_shortname(pitch)) < 2) {
			Serial.print(" ");
		}
	}
	Serial.println();
}
#endif
