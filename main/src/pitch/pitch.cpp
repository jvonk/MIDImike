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

namespace {
	typedef struct note_t {
		char const * const name;
		frequency_t const  freq;
		frequency_t const  freq_max; // up to, but not including
	} note_t;

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
}

Pitch::Pitch(void)
{
	_.notenr = NOTENR_C;
	_.octavenr = 0;
}

/**
 * @brief Construct a new Pitch:: Pitch object
 * 
 * @param fullname Note name w/ octave# e.g. "Gb4"
 */
Pitch::Pitch(char const * const fullname)
{
	// get octave# from the last char
	uint_fast8_t len = strlen(fullname);
	_.octavenr = fullname[len - 1] - '0';

	// chars before octave# are the note name itself
	bool found = false;
	note_t const * nn = _notes;
	uint_least8_t max = static_cast<int>(NOTENR_COUNT);

	for (uint_least8_t ii = 0; ii < max && !found; ii++, nn++) {
		if ((nn->name[0] == fullname[0]) &&
			((nn->name[1] == '\0' && len < 3) ||
			(nn->name[1] == fullname[1]))) {
			_.notenr = static_cast<notenr_t>(ii);
			found = true;
		}
	}
	if (!found) {
		_.octavenr = 0;
		_.notenr = NOTENR_C;
	}
}

/**
 * @brief Construct a new Pitch:: Pitch object
 * 
 * @param freq Frequency
 */
Pitch::Pitch(frequency_t const freq)
{
	frequency_t f = freq;

	if (f) { //2BD:  f > FREQ_MIN && f < FREQ_MAX) {

			// scale down frequency to octave 0, noting the # of octaves shifted
		_.octavenr = 0;

		while (f >= _notes[NOTENR_COUNT - 1].freq_max) {
			_.octavenr++;
			f /= 2;
		}
		for (uint_least8_t ii = 0; ii < NOTENR_COUNT; ii++) {
			if (f < _notes[ii].freq_max) {
				_.notenr = static_cast<notenr_t>(ii);
				break;
			}
		}

	} else {
		_.notenr = NOTENR_C;
		_.octavenr = 0;
	}
}

/**
 * @brief Construct a new Pitch:: Pitch object
 * 
 * @param number  Note number within the octave
 * @param octave  Octave number
 */
Pitch::Pitch(notenr_t const number,
			octavenr_t const octave)
{
	if (number < NOTENR_COUNT) {
		_.notenr = number;
		_.octavenr = octave;
	} else {
		_.notenr = NOTENR_C;
		_.octavenr = 0;
	}
}

char const *
Pitch::get_shortname(void)
{
	return _notes[_.notenr].name;
}

frequency_t
Pitch::get_frequency(void)
{
	uint8_t const notesCnt = sizeof(_notes) / sizeof(_notes[0]);
	uint_least8_t const idx = static_cast<uint_least8_t>(_.notenr);

	if (idx >= notesCnt ||
		(_.notenr == NOTENR_C && _.octavenr == 0)) {
		return 0;
	}
	float freq = _notes[idx].freq;

	uint_least8_t octave = _.octavenr;
	while (octave) {
		freq *= 2;
		octave--;
	}
	return freq;
}

notenr_t
Pitch::get_notenr(void)
{
	return _.notenr;
}

octavenr_t
Pitch::get_octavenr(void)
{
	return _.octavenr;
}

segment_pitch_t
Pitch::get_segment(void)
{
	return _.octavenr * 12 + static_cast<segment_pitch_t>(_.notenr);
}

segment_pitch_t
Pitch::freq2segment(frequency_t const freq)  // returns the midi pitch for a given frequency
{
	return freq < CONFIG_MIDIMIKE_FREQ_MIN ? 0 : 69.0 + 12.0 * log(freq / 440.0) / log(2);
}

void
Pitch::write_serial_hdr(void)
{
	Serial.println("");
	Serial.print("instrument samplefreq buffsize noteoctave freq => ");
	Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE);
	Serial.print(" ");
	Serial.println(CONFIG_MIDIMIKE_WINDOW_SIZE);
}

/**
 * @brief 
 * 
 * @param instrument Instrument name
 * @param in_pitch   Note from file
 * @param freq       Frequency measured
 */
void
Pitch::write_serial(char const * const instrument, Pitch & in_pitch, frequency_t freq)
{
	Serial.print(instrument); Serial.print(" ");
	Serial.print(CONFIG_MIDIMIKE_SAMPLE_RATE); Serial.print(" ");
	Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE); Serial.print(" ");

	// the value it shoud be (do not show for microphone input)
	if (in_pitch.get_frequency()) {
		Serial.print(in_pitch.get_shortname());
		Serial.print(in_pitch.get_octavenr());
		if (strlen(in_pitch.get_shortname()) < 2) {
			Serial.print(" ");
		}
		Serial.print(" ");
		Serial.print(this->get_frequency());
	}

	// value measured
	if (this->get_segment() > 0) {
		Serial.print(" => ");
		Serial.print(freq);
		Serial.print(" ");
		Serial.print(this->get_shortname());
		Serial.print(this->get_octavenr());
		if (strlen(this->get_shortname()) < 2) {
			Serial.print(" ");
		}
	}
	Serial.println();
}
