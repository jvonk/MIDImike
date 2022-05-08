/**
 * @brief Show MIDI data on piano roll
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
#include <Adafruit_GFX.h>    // core graphics
#include <Adafruit_ST7735.h> // hardware-specific graphics

#include "../../config.h"
#include "../../sample_t.h"
#include "../pitch/pitch.h"
#include "../segment/segmentbuf.h"
#include "display.h"
#include "pianoroll.h"

#if DST == DST_PIANOROLL
 								 //   rrrr rggg gggb bbbb
#define COLOR_NOTESTART (0xF800) // 0b1111 1000 0000 0000  red
#define COLOR_NOTE (0x0700)      // 0b0000 0111 0000 0000  dark green
#define COLOR_CURSOR (0x001F)    // 0b0000 0000 0001 1111  blue
#define COLOR_ROLLC (0x2104)     // 0b0010 0001 0000 0100  dark gray
#define COLOR_ROLLG (0xC618)     // 0b1100 0110 0001 1000  gray
#define COLOR_ROLLOTHER (0xF79E) // 0b1111 0111 1001 1110  light gray
#define COLOR_BG (0xFFFF)        // 0b1111 1111 1111 1111  white

#define CHAR_WIDTH (6)
#define CHAR_HEIGHT (8)
#define X_FIRSTNOTE (2 * CHAR_WIDTH)
#define PITCH_MIN (Pitch::freq2segment(CONFIG_MIDIMIKE_FREQ_MIN))
#define PITCH_MAX (Pitch::freq2segment(CONFIG_MIDIMIKE_FREQ_MAX))

typedef struct display_t {
	xCoordinate_t width;
	yCoordinate_t height;
} display_t;

typedef struct distance_t {
	yCoordinate_t pitch2pitch;
	yCoordinate_t bottom2loPitch;
} distance_t;

typedef struct msec_t {
	segmentRelTime_t per_pixel;
	segmentRelTime_t on_screen;
	absolute_time_t start;
} msec_t;

typedef struct pianoroll_t {
	Adafruit_ST7735 * tft;
	display_t display;
	distance_t distance;
	msec_t msec;
} pianoroll_t;

static pianoroll_t _pianoroll = {};

static void
_resize(int width, int height)
{
	_pianoroll.display.height = height;
	_pianoroll.display.width = width;

	segment_pitch_t const nrOfPos = PITCH_MAX - PITCH_MIN + 1;

	_pianoroll.distance.pitch2pitch = height / nrOfPos;
	_pianoroll.distance.bottom2loPitch = (height - nrOfPos*_pianoroll.distance.pitch2pitch) / 2;

	xCoordinate_t const sWidth = width - X_FIRSTNOTE;  // screen width [pixels]
	_pianoroll.msec.on_screen = 2912;                 // screen width [msec]
	_pianoroll.msec.per_pixel = _pianoroll.msec.on_screen / sWidth;
}

static INLINE xCoordinate_t        // returns x-coordinate on display [0 .. screen width - 1]
_time2x(absolute_time_t const  t,   // note time
		absolute_time_t const  t0)  // time on left of screen
{
	xCoordinate_t const distance = t - _pianoroll.msec.start > t0 ? (t - _pianoroll.msec.start - t0) / _pianoroll.msec.per_pixel : 0;

	return X_FIRSTNOTE + distance;
}

static INLINE yCoordinate_t           // returns y-coordinate on display
_pitch2y(segment_pitch_t const pitch)  // midi pitch
{
	yCoordinate_t const diff = (pitch - PITCH_MIN) * _pianoroll.distance.pitch2pitch;

	return _pianoroll.display.height - _pianoroll.distance.bottom2loPitch - diff;
}

static void
_displayRoll(xCoordinate_t const xLeft,
			 xCoordinate_t const xWidth)
{
	xCoordinate_t xRight = xLeft + xWidth;

	for (segment_pitch_t ii = PITCH_MIN; ii <= PITCH_MAX; ii++) {

		notenr_t nr = static_cast<notenr_t>(ii % 12);

		bool isC = (nr == NOTENR_C);
		bool isG = (nr == NOTENR_G);

		color_t const color = isC ? COLOR_ROLLC : isG ? COLOR_ROLLG : COLOR_ROLLOTHER;

		xCoordinate_t x = xLeft;
		yCoordinate_t const y = _pitch2y(ii);

		if (x == 0) {
			if (isC || isG) {  // write a few note names on far left

				octavenr_t octave = ii / 12;
				yCoordinate_t const cY = y - CHAR_HEIGHT / 2 + 1;

				_pianoroll.tft->drawChar(0, cY, isC ? 'C' : 'G', color, color, 1);
				_pianoroll.tft->drawChar(CHAR_WIDTH, cY, '0' + octave, color, color, 1);
			}
			x = X_FIRSTNOTE;  // start lines right of the note names
		}
		_pianoroll.tft->drawFastHLine(x, y, xRight - xLeft, color);
	}
}

void
pianoroll_draw(absolute_time_t const  lastOffset,  // needed to calculate absolute times
			   SegmentBuf * const    segmentBuf)  // segment buffer containing notes
{
	absolute_time_t const now = millis();

	absolute_time_t const n = (now - _pianoroll.msec.start) / _pianoroll.msec.on_screen;  // #times cursor wrapped around
	absolute_time_t const t0 = n * _pianoroll.msec.on_screen;  // time corresponding to the most left position on screen
	xCoordinate_t const cursor = _time2x(now, t0);
	uint_least8_t const startLen = 2;  // first two pixels hi-light the note start

	// clear 1/20 of the screen width right of cursor
	xCoordinate_t const wipe = min(_pianoroll.display.width / 20, _pianoroll.display.width - cursor);
	_pianoroll.tft->fillRect(cursor, 0, wipe, _pianoroll.display.height, COLOR_BG);

	// draw line, just ahead of cursor
	_pianoroll.tft->drawFastVLine(cursor + 1, 0, _pianoroll.display.height, COLOR_CURSOR);

	// redraw a msec positions left of cursor.  This is needed because a new
	// note is only recognized after it meets this minimum duration.  Until then, the note is shown
	// as part of the previous note (or rest).
	absolute_time_t const maxLoopTime = 60;  // worst case is ~60msec per chunk [msec], increase if you see empty columns in the piano roll
	absolute_time_t const drawInMsec = min(CONFIG_MIDIMIKE_MIN_SEGMENT_DURATION + maxLoopTime, (cursor - X_FIRSTNOTE)*_pianoroll.msec.per_pixel);
	xCoordinate_t const drawInPixels = (xCoordinate_t)drawInMsec / _pianoroll.msec.per_pixel;                             // 38 msec
	_pianoroll.tft->fillRect(cursor - drawInPixels, 0, drawInPixels, _pianoroll.display.height, COLOR_BG);  // erase, in case the pitch changed
	_displayRoll(cursor - drawInPixels, drawInPixels);

	uint_least8_t ii = 0;
	segment_t const * note;

	absolute_time_t offset = lastOffset;

	while ((note = segmentBuf->head_ptr(ii++)) &&  // there are more notes to show &&
			(offset > now - drawInMsec)) {        // the note should be on screen

		absolute_time_t const onset = offset - note->duration;

		xCoordinate_t const xLeft = _time2x(onset, t0);
		xCoordinate_t const xWidth = _time2x(offset, t0) - xLeft;
		yCoordinate_t const yTop = _pitch2y(note->pitch) + _pianoroll.distance.pitch2pitch / 2;
		yCoordinate_t const yHeight = _pianoroll.distance.pitch2pitch;

		_pianoroll.tft->fillRect(xLeft + startLen, yTop, xWidth - startLen, yHeight, COLOR_NOTE);
		_pianoroll.tft->fillRect(xLeft, yTop, startLen, yHeight, COLOR_NOTESTART);

		offset = onset - note->onset;  // note->onset is a relative time
	}
}

void
pianoroll_clear(void)
{
	_pianoroll.tft->fillScreen(COLOR_BG);
	_displayRoll(0, _pianoroll.display.width);
	_pianoroll.msec.start = millis();
}


void
pianoroll_init(uint_least8_t tftCS_pin,  // GPIO# for SPI TFT Chip Select
			   uint_least8_t dc_pin,     // GPIO# SPI Data/Command
			   uint_least8_t reset_pin)  // GPIO# SPI Reset
{
	pinMode(tftCS_pin, OUTPUT);
	_pianoroll.tft = new Adafruit_ST7735(tftCS_pin, dc_pin, reset_pin);  // instantiate TFT driver
	_pianoroll.tft->initR(INITR_BLACKTAB);  // initialize TFT (ST7735S chip, black tab)
	_pianoroll.tft->setRotation(3);  // make (0,0) corresponds to top-right
	_resize(_pianoroll.tft->width(), _pianoroll.tft->height());
	pianoroll_clear();
}

#endif