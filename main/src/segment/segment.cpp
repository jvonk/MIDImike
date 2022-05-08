/**
 * @brief Note level segmentation, based on Monty's method, 2000.
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
#include "../../config.h"
#include "../../segment_t.h"
#include "../pitch/pitch.h"
#include "../midi/midiserial.h"
#include "cbuf.h"
#include "segment.h"
#include "segmentbuf.h"

namespace {
	segment_energy_t const SEGMENT_ENERGY_INCR_THRESHOLD = 40;  // [%]
}

void
Segment::_energy_init(segment_energytrend_t * const trend)
{
	midiserial_send_program_change(CONFIG_MIDIMIKE_MIDI_INSTRUMENT);
	trend->previous = 0;
	trend->state = segment_energystate_t::SEGMENT_ENERGYSTATE_FIND_NEG_SLOPE;
}

void
Segment::_energy_update(segment_energytrend_t * const trend, segment_energy_t const energy)
{
	switch (trend->state) {
		case segment_energystate_t::SEGMENT_ENERGYSTATE_FIND_NEG_SLOPE:
			if (energy < trend->previous) {  // downward slope started
				trend->min = energy;
				trend->state = segment_energystate_t::SEGMENT_ENERGYSTATE_FIND_POS_SLOPE;
			} else {
				trend->max = energy;
			}
			break;
		case segment_energystate_t::SEGMENT_ENERGYSTATE_FIND_POS_SLOPE:
			if (energy > trend->previous) {  // energy increasing again
				if (energy > ((100 + SEGMENT_ENERGY_INCR_THRESHOLD) * trend->min) / 100) {
					trend->state = segment_energystate_t::SEGMENT_ENERGYSTATE_FOUND_POS_SLOPE;  // trend on the rise again
				}
			} else {
				trend->min = energy;
			}
			break;
		case segment_energystate_t::SEGMENT_ENERGYSTATE_FOUND_POS_SLOPE:
			break;
	}
	trend->previous = energy;
}

segmentRelTime_t
Segment::_diff_time(absolute_time_t const t)
{
	absolute_time_t const t0 = cv.time.last_event;
	cv.time.last_event = t;

	// subtraction of two unsigned values will produce the correct answer even if one of them has over flowed
	return t - t0;
}

/**
 * @brief Construct a new Segment:: Segment object
 * 
 */
Segment::Segment(void)
{
	cv.candidate.pitch = 0;
	cv.time.prev_end = millis();
	this->_energy_init(&cv.energy_trend);
	cv.note = NULL;
}

/**
 * @brief Updates: - when an note onset is detected, a note (with offset 0) is added to the midi buffer.
 *                 - when the amplitude peak is detected, the velocity is updated in the midi buffer.
 *                 - when the note offset is detected, the 'offset' for the note is updated in the midi buffer.
 * 
 * @param now         absolute current time (at the end of chunk) [msec]
 * @param pitch       midi pitch measured
 * @param energy      energy/loudness measured [0..127]
 * @param segmentBuf  segment buffer to write note to
 */

void
Segment::put(absolute_time_t const now, segment_pitch_t const pitch, segment_energy_t const energy, SegmentBuf * const segmentBuf)
{
	absolute_time_t t = 0;  // init to please compiler
	bool start_new_note = false;
	bool stop_current_note = false;

	if (cv.note) {
		cv.note->duration = now - cv.time.last_event;  // update needed for piano roll display
		cv.time.last_offset = now;
	}

	// note start/stop
	if (pitch) {

		if (pitch == cv.candidate.pitch) {

			bool const meetsMinDuration = now - cv.candidate.start_time > CONFIG_MIDIMIKE_MIN_SEGMENT_DURATION;
			bool const noteFollowingRest = !cv.note;
			bool const pitchChanged = cv.candidate.pitch != cv.note->pitch;
			bool const energyIncreasing = cv.energy_trend.state == segment_energystate_t::SEGMENT_ENERGYSTATE_FOUND_POS_SLOPE;

			if (meetsMinDuration && (noteFollowingRest || pitchChanged || energyIncreasing)) {
				t = cv.candidate.start_time;
				if (cv.note) {               
					stop_current_note = true;  // EXISTING NOTE TERMINATED BY THE START OF A NEW NOTE
				}
				start_new_note = true;  // NEW NOTE STARTS AFTER REST
			}
			_energy_update(&cv.candidate.energy_trend, energy);

		} else {  // this becomes the new candidate
			cv.candidate.start_time = cv.time.prev_end;
			cv.candidate.pitch = pitch;
			_energy_init(&cv.candidate.energy_trend);
		}

	} else {

		if (cv.note) {  // EXISTING NOTE TERMINATED BY REST
			cv.candidate.pitch = 0;
			t = cv.time.prev_end;
			stop_current_note = true;
		}
	}

	if (stop_current_note) {
		midiserial_send_note_off(cv.note->pitch, 0);
		//midiserial_send_program_change(random(1, 52));
		cv.note = segmentBuf->note_end(_diff_time(t), cv.energy_trend.max, cv.note);
		cv.time.last_offset = t;

	}

	if (start_new_note) {
		midiserial_send_note_on(pitch, energy);
		if (segmentBuf->len() == 0) {  // first segment should have relative time=0
			cv.time.last_event = t;
		}
		cv.note = segmentBuf->note_start(_diff_time(t), now - t, pitch, energy);
		cv.time.last_offset = now;
		cv.energy_trend = cv.candidate.energy_trend;

	}

	// update energy level trend (2BD should stop when a new candidate presents itself)
	if (cv.note) {
		_energy_update(&cv.energy_trend, energy);
	}  else {
		cv.energy_trend.previous = pitch ? energy : 0;
	}
	this->cv.time.prev_end = now;
}

absolute_time_t
Segment::get_last_offset(void)
{
	return this->cv.time.last_offset;
}