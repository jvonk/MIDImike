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

namespace {

    struct _colors_t {
        uint16_t const notes;
        uint16_t const staff;
        uint16_t const background;
    } _colors = {
        ST7735_BLACK,
        0x8410, // gray encoded as rrrrrggggggbbbbb
        ST7735_WHITE
    };

    uint_least8_t const MAX_NOTES_ON_SCREEN = 6;

    Adafruit_ST7735 * _tft;

    uint_least8_t const LINES_ON_STAFF = 5;
    uint_least8_t const GKEY_WIDTH = 36;

    struct note_t {
        uint_least8_t  posInOctave;  // staff position within octave
        bool           flat;
    };

    // note: calculating the values would probably take up more memory
    note_t const _notes[static_cast<int>(noteNr_t::COUNT)] = {
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
    };

    typedef uint_least8_t hStaffPos_t;

    struct _display_t {
        int16_t height;
        int16_t width;
    } _display;

    struct _distance_t {
        int16_t bottom2loStaff;
        int16_t top2hiStaff;
        int16_t staffLine2line;
        int16_t note2note;
        int16_t noteRadius;
    } _distance;

    typedef int16_t vStaffPos_t;  // 2BD not 100% sure if this should be signed

    struct _positionHiLo_t {
        vStaffPos_t min;
        vStaffPos_t max;
    };

    vStaffPos_t _nr2vStaffPos( noteNr_t const number, octaveNr_t const octave );
    vStaffPos_t _freq2vStaffPos( frequency_t const freq );

    struct _position_t {
        _positionHiLo_t show;
        _positionHiLo_t staff;
    } const _position = {
        {_freq2vStaffPos(CONFIG_MIDIMIKE_FREQ_MIN ), _freq2vStaffPos( CONFIG_MIDIMIKE_FREQ_MAX )},
        { _nr2vStaffPos( noteNr_t::E, 4 ), _nr2vStaffPos( noteNr_t::F, 5 ) }   // 30, 38
    };



    /*****************
     * Local functions
     *****************/


    // resize screen
    void
    _resize( int const  width, 
             int const  height )
    {
        _display.height = height;
        _display.width = width;

        // staff in middle 1/3 of screen
        _distance.bottom2loStaff = _display.height / 3;  
        _distance.top2hiStaff = _display.height / 3;
        _distance.staffLine2line = (_display.height -
            _distance.bottom2loStaff -
            _distance.top2hiStaff) / (LINES_ON_STAFF - 1);

        _distance.note2note = (_display.width - GKEY_WIDTH) / MAX_NOTES_ON_SCREEN;
        _distance.noteRadius = _distance.staffLine2line / 2 - 1;
    }


    INLINE bool
    _isFlat(noteNr_t const noteNr)
    {
        return _notes[static_cast<int>(noteNr)].flat;
    }


    INLINE vStaffPos_t
    _nr2vStaffPos(noteNr_t const number,
                  octaveNr_t const octave)
    {
        uint16_t const staffPositionsInOctave = 7;
        return staffPositionsInOctave * octave + _notes[static_cast<int>(number)].posInOctave;
    }

    INLINE vStaffPos_t
    _freq2vStaffPos( frequency_t const freq )
    {
        segmentPitch_t const pitch = Pitch::freq2pitch( freq );

        return  _nr2vStaffPos( static_cast<noteNr_t>(pitch % 12),
            static_cast<octaveNr_t>(pitch / 12) );
    }


    // horizontal staff position to screen x coordinate
    INLINE int16_t
    _hStaffPos2x( int const n )
    {
        // 2BD: one could move the notes closer to each other as they shift to the left
        return GKEY_WIDTH + (n * _distance.note2note + _distance.note2note / 2);
    }


    vStaffPos_t
    _getVStaffPos(Pitch & pitch )
    {
        return _nr2vStaffPos( pitch.getNoteNr(), pitch.getOctaveNr() );
    }

    // position on staff to screen y coordinate
    int16_t
    _vStaffPos2y( vStaffPos_t const n )
    {
        vStaffPos_t const distAbove1stNoteOnStaff = n - _position.staff.min;  // could be negative!

        return ( _display.height - _distance.bottom2loStaff ) -
            distAbove1stNoteOnStaff * _distance.staffLine2line / 2;
    }


    void
    _displayStaff( void )
    {
        for ( int ii = 0; ii < LINES_ON_STAFF; ii++ ) {
            _tft->drawFastHLine( 0, _vStaffPos2y( _position.staff.min + ii * 2 ),
                _display.width, _colors.staff );
        }
    }


    void
    _drawHelperLine( uint16_t const    x,
                     vStaffPos_t const positionOnStaff,
                     uint16_t const    barColor )
    {
        uint16_t len = _distance.note2note * 4 / 5;

        _tft->drawFastHLine(x - len/2, 
            _vStaffPos2y(positionOnStaff),
            len, barColor);
    }


    void
    _drawNote( uint_least8_t const hpos,
               Pitch & pitch,
               bool const erase )
    {
        vStaffPos_t const n = _getVStaffPos(pitch);
        if ( n == 0 ) {
            return;
        }
        int16_t const x = _hStaffPos2x( hpos );
        int16_t const y = _vStaffPos2y( n );

        uint16_t const noteColor = erase ? _colors.background : _colors.notes;
        uint16_t const barColor = erase ? _colors.background : _colors.staff;


        vStaffPos_t positionOnStaff = _getVStaffPos(pitch);

        if ( positionOnStaff < _position.show.min ) {
            StaffSymbol::draw( x, 0, (staffSymbolName_t)staffSymbolName_t::toLow, noteColor );
            return;
        }

        if ( positionOnStaff > _position.show.max ) {
            StaffSymbol::draw( x, 0, (staffSymbolName_t)staffSymbolName_t::toHigh, noteColor );
            return;
        }

        // draw helper line(s) if needed
        if ( positionOnStaff < _position.staff.min ) {
            for ( hStaffPos_t jj = positionOnStaff; jj < _position.staff.min; jj++ ) {
                if ( jj % 2 == 0 ) {
                    _drawHelperLine( x, jj, barColor );
                }
            }
        }
        if ( positionOnStaff > _position.staff.max ) {
            for ( hStaffPos_t jj = positionOnStaff; jj > _position.staff.max; jj-- ) {
                if (jj % 2 == 0) {
                    _drawHelperLine( x, jj, barColor );
                }
            }
        }

        // draw flat symbol
        if ( _isFlat( pitch.getNoteNr() ) ) {
            StaffSymbol::draw( x, y, (staffSymbolName_t)staffSymbolName_t::flat, noteColor );
        }

        // draw the note itself
        StaffSymbol::draw( x, y, (staffSymbolName_t)staffSymbolName_t::note, noteColor );
        //_tft->fillCircle( x, y, _distance.noteRadius, noteColor );
    }

} // name space


void
Staff::showNote( Pitch &           pitch,        // note measured
                 amplitude_t const amplitude )   // amplitude measured
{
    (void)amplitude;
    static boolean        scroll = false;
    static uint_least8_t  curScreenPos = 0;
    static Pitch          notesOnScreen[MAX_NOTES_ON_SCREEN];

        // if screen is full, shift to left

    if ( scroll ) {
        for ( uint_least8_t ii = 0; ii < MAX_NOTES_ON_SCREEN; ii++ ) {

                // erase old note from screen position
            _drawNote( ii, notesOnScreen[ii], true );

                // draw new note in same screen position 
            if ( ii < MAX_NOTES_ON_SCREEN - 1 ) {
                notesOnScreen[ii] = notesOnScreen[ii + 1];
                _drawNote( ii, notesOnScreen[ii], false );
            }
        }
        _displayStaff();  // draw staff to cover up empty spots
    }
    notesOnScreen[curScreenPos] = pitch;  // remember for later

    _drawNote( curScreenPos, pitch, false );

    if ( !scroll ) {
        if ( curScreenPos == MAX_NOTES_ON_SCREEN - 1 ) {
            scroll = true;
        } else {
            curScreenPos++;
        }
    }
}


void
Staff::begin( uint_least8_t tftCS,   // SPI TFT Chip Select
              uint_least8_t dc,      // SPI Data/Command
              uint_least8_t reset )  // SPI Reset
{
    pinMode( tftCS, OUTPUT );
    _tft = new Adafruit_ST7735( tftCS, dc, reset );
    _tft->initR( INITR_BLACKTAB );  // initialize ST7735S chip, black tab
    _tft->fillScreen( _colors.background );
    _tft->setRotation( 3 );         // (0,0) corresponds to top-right
    _resize( _tft->width(), _tft->height() );
    _displayStaff();

    StaffSymbol::begin( _tft,
                      _display.width, _display.height,
                      _distance.noteRadius, _distance.bottom2loStaff, _distance.top2hiStaff,
                      _vStaffPos2y( _nr2vStaffPos( noteNr_t::G, 4 ) ));

#if GKEY != GKEY_NONE
    StaffSymbol::draw( _hStaffPos2x( 0 ), 0, (staffSymbolName_t)staffSymbolName_t::gKey, _colors.staff );
#endif
}

#endif