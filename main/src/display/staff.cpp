/**
 * @brief Show music notes on tremble clef
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
#include "staffsymbol.h"
#include "staff.h"

#if DST == DST_STAFF

#define COLOR_NOTES (ST7735_BLACK)
#define COLOR_STAFF (0x8410)  // gray encoded as rrrrrggggggbbbbb
#define COLOR_BG (ST7735_WHITE)
#define MAX_NOTES_ON_SCREEN (6)
#define LINES_ON_STAFF (5)
#define GKEY_WIDTH (36)

namespace {

    typedef uint_least8_t hStaffPos_t;
    typedef int16_t vStaffPos_t;  // 2BD not 100% sure if this should be signed

    typedef struct staffnote_t {
        uint_least8_t  posInOctave;  // staff position within octave
        bool           flat;
    } staffnote_t;

    typedef struct display_t {
        int16_t height;
        int16_t width;
    } display_t;

    typedef struct distance_t {
        int16_t bottom2loStaff;
        int16_t top2hiStaff;
        int16_t staffLine2line;
        int16_t note2note;
        int16_t noteRadius;
    } distance_t;

    typedef struct positionHiLo_t {
        vStaffPos_t min;
        vStaffPos_t max;
    } positionHiLo_t;

    typedef struct position_t {
        positionHiLo_t show;
        positionHiLo_t staff;
    } position_t;

    typedef struct staff_t {
        Adafruit_ST7735 * tft;
        staffnote_t const notes[static_cast<int>(NOTENR_COUNT)];
        display_t display;
        distance_t distance;
        position_t position;
    } staff_t;

    static staff_t _ = {
        .tft = NULL,    
        .notes = {  // calculating the values would probably take up more memory
            { 0, false },
            { 1, true  },
            { 1, false },
            { 2, true  },
            { 2, false },
            { 3, false },
            { 4, true  },
            { 4, false },
            { 5, true  },
            { 5, false },
            { 6, true  },
            { 6, false }
        },
        .display = {},
        .distance = {},
        .position = {}
    };
}

// resize screen
static void
_resize(int const width, 
        int const height)
{
    _.display.height = height;
    _.display.width = width;

    // staff in middle 1/3 of screen
    _.distance.bottom2loStaff = _.display.height / 3;  
    _.distance.top2hiStaff = _.display.height / 3;
    _.distance.staffLine2line = (_.display.height -
        _.distance.bottom2loStaff -
        _.distance.top2hiStaff) / (LINES_ON_STAFF - 1);

    _.distance.note2note = (_.display.width - GKEY_WIDTH) / MAX_NOTES_ON_SCREEN;
    _.distance.noteRadius = _.distance.staffLine2line / 2 - 1;
}

static INLINE bool
_isFlat(notenr_t const noteNr)
{
    return _.notes[static_cast<int>(noteNr)].flat;
}

static INLINE vStaffPos_t
_nr2vStaffPos(notenr_t const number,
              octavenr_t const octave)
{
    uint16_t const staffPositionsInOctave = 7;
    return staffPositionsInOctave * octave + _.notes[static_cast<int>(number)].posInOctave;
}

static INLINE vStaffPos_t
_freq2vStaffPos(frequency_t const freq)
{
    segment_pitch_t const segment = Pitch::freq2segment(freq);

    return  _nr2vStaffPos(static_cast<notenr_t>(segment % 12),
        static_cast<octavenr_t>(segment / 12));
}

// horizontal staff position to screen x coordinate
static INLINE int16_t
_hStaffPos2x(int const n)
{
    // 2BD: one could move the notes closer to each other as they shift to the left
    return GKEY_WIDTH + (n * _.distance.note2note + _.distance.note2note / 2);
}

static vStaffPos_t
_getVStaffPos(Pitch & pitch)
{
    return _nr2vStaffPos(pitch.get_notenr(), pitch.get_octavenr());
}

// position on staff to screen y coordinate
static int16_t
_vStaffPos2y(vStaffPos_t const n)
{
    vStaffPos_t const distAbove1stNoteOnStaff = n - _.position.staff.min;  // could be negative!

    return (_.display.height - _.distance.bottom2loStaff) -
        distAbove1stNoteOnStaff * _.distance.staffLine2line / 2;
}

static void
_displayStaff(void)
{
    for (int ii = 0; ii < LINES_ON_STAFF; ii++) {
        _.tft->drawFastHLine(0, _vStaffPos2y(_.position.staff.min + ii * 2),
            _.display.width, COLOR_STAFF);
    }
}

static void
_drawHelperLine(uint16_t const x, vStaffPos_t const positionOnStaff, uint16_t const barColor)
{
    uint16_t len = _.distance.note2note * 4 / 5;

    _.tft->drawFastHLine(x - len/2, 
        _vStaffPos2y(positionOnStaff),
        len, barColor);
}

static void
_drawNote(uint_least8_t const hpos, Pitch & pitch, bool const erase)
{
    vStaffPos_t const n = _getVStaffPos(pitch);
    if (n == 0) {
        return;
    }
    int16_t const x = _hStaffPos2x(hpos);
    int16_t const y = _vStaffPos2y(n);

    uint16_t const noteColor = erase ? COLOR_BG : COLOR_NOTES;
    uint16_t const barColor = erase ? COLOR_BG : COLOR_STAFF;

    vStaffPos_t positionOnStaff = _getVStaffPos(pitch);

    if (positionOnStaff < _.position.show.min) {
        staffsymbol_draw(x, 0, STAFFSYMBOL_NAME_TO_LOW, noteColor);
        return;
    }

    if (positionOnStaff > _.position.show.max) {
        staffsymbol_draw(x, 0, STAFFSYMBOL_NAME_TO_HIGH, noteColor);
        return;
    }

    // draw helper line(s) if needed
    if (positionOnStaff < _.position.staff.min) {
        for (hStaffPos_t jj = positionOnStaff; jj < _.position.staff.min; jj++) {
            if (jj % 2 == 0) {
                _drawHelperLine(x, jj, barColor);
            }
        }
    }
    if (positionOnStaff > _.position.staff.max) {
        for (hStaffPos_t jj = positionOnStaff; jj > _.position.staff.max; jj--) {
            if (jj % 2 == 0) {
                _drawHelperLine(x, jj, barColor);
            }
        }
    }

    // draw flat symbol
    if (_isFlat(pitch.get_notenr())) {
        staffsymbol_draw(x, y, STAFFSYMBOL_NAME_FLAT, noteColor);
    }

    // draw the note itself
    staffsymbol_draw(x, y, STAFFSYMBOL_NAME_NOTE, noteColor);
    //_.tft->fillCircle(x, y, _.distance.noteRadius, noteColor);
}

/**
 * @brief 
 * 
 * @param pitch     Note measured
 * @param amplitude Amplitude measured
 */
void
staff_draw_note(Pitch & pitch)
{
    static boolean        scroll = false;
    static uint_least8_t  curScreenPos = 0;
    static Pitch          notesOnScreen[MAX_NOTES_ON_SCREEN];

        // if screen is full, shift to left

    if (scroll) {
        for (uint_least8_t ii = 0; ii < MAX_NOTES_ON_SCREEN; ii++) {

                // erase old note from screen position
            _drawNote(ii, notesOnScreen[ii], true);

                // draw new note in same screen position 
            if (ii < MAX_NOTES_ON_SCREEN - 1) {
                notesOnScreen[ii] = notesOnScreen[ii + 1];
                _drawNote(ii, notesOnScreen[ii], false);
            }
        }
        _displayStaff();  // draw staff to cover up empty spots
    }
    notesOnScreen[curScreenPos] = pitch;  // remember for later

    _drawNote(curScreenPos, pitch, false);

    if (!scroll) {
        if (curScreenPos == MAX_NOTES_ON_SCREEN - 1) {
            scroll = true;
        } else {
            curScreenPos++;
        }
    }
}

void
staff_init(uint_least8_t tftCS_pin,   // GPIO# for SPI TFT Chip Select
            uint_least8_t dc_pin,     // GPIO# for SPI Data/Command
            uint_least8_t reset_pin)  // GPIO# for SPI Reset
{
    pinMode(tftCS_pin, OUTPUT);
    _.tft = new Adafruit_ST7735(tftCS_pin, dc_pin, reset_pin);
    _.tft->initR(INITR_BLACKTAB);  // initialize ST7735S chip, black tab
    _.tft->fillScreen(COLOR_BG);
    _.tft->setRotation(3);         // (0,0) corresponds to top-right
    _resize(_.tft->width(), _.tft->height());
    _displayStaff();

    _.position = {
        { _freq2vStaffPos(CONFIG_MIDIMIKE_FREQ_MIN), _freq2vStaffPos(CONFIG_MIDIMIKE_FREQ_MAX)},
        { _nr2vStaffPos(NOTENR_E, 4), _nr2vStaffPos(NOTENR_F, 5) }   // 30, 38
    };

    staffsymbol_init(_.tft,
                      _.display.width, _.display.height,
                      _.distance.noteRadius, _.distance.bottom2loStaff, _.distance.top2hiStaff,
                      _vStaffPos2y(_nr2vStaffPos(NOTENR_G, 4)));

#if GKEY != GKEY_NONE
    staffsymbol_draw(_hStaffPos2x(0), 0, (staffSymbolName_t)STAFFSYMBOL_NAME_GKEY, COLOR_STAFF);
#endif
}

#endif