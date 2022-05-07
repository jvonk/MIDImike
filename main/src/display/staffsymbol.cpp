/**
 * @brief Show symbol on staff
 *
 * Implementation:
 *   Enclosed bmp2c converts Microsoft Bitmap (.bmp) to C-style array
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
#include "../pitch/pitch.h"
#include "staffsymbol.h"

#if DST == DST_STAFF

uint8_t const _symbol_bitmap_flat[] = {
    0x80, 0x80, 0x80, 0x80, 0x90, 0xA8, 0xCC, 0x8C, 0x98, 0xA0, 0xC0, 0x80};

uint8_t const _symbol_bitmap_to_low[] = {
    0xFF, 0x7E, 0x3C, 0x18};

uint8_t const _symbol_bitmap_to_heigh[] = {
    0x18, 0x3C, 0x7E, 0xFF};

uint8_t const _symbol_bitmap_note[] = {
    0x1E, 0x1F, 0xE7, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFE, 0x7F, 0x87, 0x80};

// 2BD this memory hog should be stored in program memory (PROGMEM), instead of SDRAM
uint8_t const _symbol_bitmap_gkey[] = {
#if (GKEY == GKEY_LORES)
    0x00, 0x30, 0x00, 0x70, 0x00, 0xF8, 0x00, 0xF8, 0x01, 0x88, 0x01, 0x84, 0x01, 0x84, 0x01, 0x0C,
    0x01, 0x08, 0x01, 0x18, 0x01, 0x38, 0x01, 0x78, 0x01, 0xF0, 0x01, 0xE0, 0x07, 0xE0, 0x0F, 0xC0,
    0x1F, 0x80, 0x3E, 0x80, 0x3C, 0x80, 0x78, 0x00, 0x70, 0x00, 0xE1, 0xF8, 0xE3, 0xFC, 0xC7, 0xFE,
    0xC7, 0x4E, 0x86, 0x47, 0x84, 0x43, 0xC4, 0x03, 0x44, 0x23, 0x42, 0x22, 0x21, 0x26, 0x10, 0x24,
    0x06, 0x18, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x0C, 0x10, 0x1E, 0x10, 0x1F, 0x10,
    0x1E, 0x10, 0x1E, 0x10, 0x08, 0x20, 0x07, 0x80
#elif (GKEY == GKEY_HIRES)
    0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x3F, 0x80,
    0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0xFF, 0xE0,
    0x00, 0x00, 0xF0, 0x60, 0x00, 0x01, 0xE0, 0x60, 0x00, 0x01, 0xE0, 0x20, 0x00, 0x01, 0xC0, 0x30,
    0x00, 0x01, 0xC0, 0x30, 0x00, 0x01, 0xC0, 0x30, 0x00, 0x01, 0x80, 0x70, 0x00, 0x03, 0x80, 0x70,
    0x00, 0x03, 0x80, 0xF0, 0x00, 0x03, 0x80, 0xE0, 0x00, 0x03, 0x81, 0xE0, 0x00, 0x03, 0x03, 0xE0,
    0x00, 0x01, 0x03, 0xE0, 0x00, 0x01, 0x07, 0xE0, 0x00, 0x01, 0x0F, 0xC0, 0x00, 0x01, 0x1F, 0xC0,
    0x00, 0x01, 0xBF, 0x80, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x03, 0xFE, 0x00,
    0x00, 0x07, 0xFC, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x7F, 0xF0, 0x00,
    0x00, 0xFF, 0xC0, 0x00, 0x01, 0xFF, 0xC0, 0x00, 0x03, 0xFF, 0x40, 0x00, 0x07, 0xFE, 0x40, 0x00,
    0x07, 0xFC, 0x40, 0x00, 0x0F, 0xF0, 0x40, 0x00, 0x1F, 0xE0, 0x60, 0x00, 0x1F, 0xC0, 0x20, 0x00,
    0x3F, 0x80, 0x20, 0x00, 0x3F, 0x00, 0x20, 0x00, 0x7F, 0x00, 0x3C, 0x00, 0x7E, 0x01, 0xFF, 0xE0,
    0x7C, 0x03, 0xFF, 0xF0, 0xFC, 0x07, 0xFF, 0xF8, 0xF8, 0x0F, 0xFF, 0xFC, 0xF0, 0x1F, 0xFF, 0xFC,
    0xF0, 0x1F, 0xFF, 0xFE, 0xF0, 0x3F, 0x10, 0xFE, 0xE0, 0x3C, 0x10, 0x3F, 0xE0, 0x3C, 0x18, 0x1F,
    0xE0, 0x38, 0x18, 0x1F, 0x60, 0x38, 0x18, 0x0F, 0x60, 0x38, 0x08, 0x0F, 0x70, 0x38, 0x08, 0x0F,
    0x70, 0x38, 0x0C, 0x0F, 0x30, 0x18, 0x0C, 0x0F, 0x38, 0x0C, 0x0C, 0x0E, 0x18, 0x04, 0x0C, 0x0E,
    0x0C, 0x02, 0x04, 0x0E, 0x0E, 0x01, 0x04, 0x1C, 0x07, 0x00, 0x04, 0x18, 0x03, 0x80, 0x06, 0x30,
    0x00, 0xE0, 0x06, 0x60, 0x00, 0x3C, 0x03, 0xC0, 0x00, 0x1F, 0xFF, 0x00, 0x00, 0x01, 0xFA, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x78, 0x01, 0x00,
    0x00, 0xFE, 0x01, 0x00, 0x01, 0xFE, 0x01, 0x80, 0x03, 0xFF, 0x01, 0x80, 0x03, 0xFF, 0x01, 0x80,
    0x03, 0xFF, 0x01, 0x80, 0x03, 0xFE, 0x01, 0x00, 0x03, 0xFE, 0x01, 0x00, 0x03, 0xFC, 0x03, 0x00,
    0x01, 0xF0, 0x06, 0x00, 0x00, 0xE0, 0x0C, 0x00, 0x00, 0x78, 0x38, 0x00, 0x00, 0x1F, 0xE0, 0x00
#endif
};

#define FLAT_TO_NOTE_DISTANCE (1)

typedef struct symbolCoordXY_t {
    xCoordinate_t x;
    yCoordinate_t y;
} symbolCoordXY_t;

typedef struct symbolPlace_t {
    bool          relative;
    int_least16_t value;
} symbolPlace_t;

typedef struct symbolPlaceXY_t {
    symbolPlace_t x;
    symbolPlace_t y;
} symbolPlaceXY_t;

typedef struct symbol_t {
    symbolCoordXY_t const        size;
    symbolPlaceXY_t              place;
    symbolCoordXY_t const        enlarge;
    uint_least8_t const * const  bitmap;  // 'cause C++ doesn't support zero length arrays
} symbol_t;

symbol_t _symbols[STAFFSYMBOL_NAME_COUNT] = {
    { 8, 12, {{}, {}}, {1, 1}, _symbol_bitmap_flat},
    { 8,  4, {{}, {}}, {1, 1}, _symbol_bitmap_to_low},
    { 8,  4, {{}, {}}, {1, 1}, _symbol_bitmap_to_heigh},
    {10, 10, {{}, {}}, {1, 1}, _symbol_bitmap_note},
#if GKEY == GKEY_LORES
    {16, 44, {{}, {}}, {2, 2}, _symbol_bitmap_gkey},
#elif GKEY == GKEY_HIRES
    {32, 88, {{}, {}}, {1, 1}, _symbol_bitmap_gkey},
#endif
};

typedef struct my_t {
    Adafruit_ST7735 * tft;
    symbolCoordXY_t displaySize;
    yCoordinate_t noteRadius;
    yCoordinate_t bottom2loStaff;
    yCoordinate_t top2hiStaff;
    yCoordinate_t yG4;
} my_t;

static my_t _my = {};

void
staffsymbol_init(Adafruit_ST7735 * const tft, 
                 xCoordinate_t const displayWidth,
                 yCoordinate_t const displayHeight,
                 yCoordinate_t const noteRadius,
                 yCoordinate_t const bottom2loStaff,  // distance from bottom of screen to low staff line
                 yCoordinate_t const top2hiStaff,     // distance from top of screen to high staff line
                 yCoordinate_t const yG4)             // y position for note G4
{        
    _my = { // save for later
        .tft = tft,
        .displaySize = {
            .x = displayWidth,
            .y = displayHeight
        },
        .noteRadius = noteRadius,
        .bottom2loStaff = bottom2loStaff,
        .top2hiStaff = top2hiStaff,
        .yG4 = yG4
    };

    uint_least8_t const max = staffSymbolName_COUNT;
    
    for (uint_least8_t ii = 0; ii < max; ii++) {  // calculate symbol positions for later

        ::symbol_t const * const s = &_symbols[ii];
        ::symbolPlaceXY_t * const p = &_symbols[ii].place;

        xCoordinate_t width = s->size.x * s->enlarge.x;
        yCoordinate_t height = s->size.y * s->enlarge.y;

        switch (ii) {
            case STAFFSYMBOL_NAME_FLAT:
                p->x.relative = true;
                p->x.value = -(_my.noteRadius + FLAT_TO_NOTE_DISTANCE + width);
                p->y.relative = true;
                p->y.value = -(height / 2);
                break;
            case STAFFSYMBOL_NAME_TO_LOW:
                p->x.relative = true;
                p->x.value = -(width / 2);
                p->y.relative = false;
                p->y.value = _my.displaySize.y - _my.bottom2loStaff / 4 - height / 2;
                break;
            case STAFFSYMBOL_NAME_TO_HIGH:
                p->x.relative = true;
                p->x.value = -(width * s->enlarge.x / 2);
                p->y.relative = false;
                p->y.value = _my.top2hiStaff / 4 - height / 2;
                break;
            case STAFFSYMBOL_NAME_NOTE:
                p->x.relative = true;
                p->x.value = -(width / 2);
                p->y.relative = true;
                p->y.value = -(height / 2);
                break;
#if GKEY != GKEY_NONE
            case STAFFSYMBOL_NAME_GKEY:
                p->x.relative = false;
                p->x.value = 0;
                p->y.relative = false;
                // G4 is 58 pixels from top of the (88 pixel height) image
                p->y.value = _my.yG4 - (height * 58 / 88);
                break;
#endif
                break;
        }
    }
}


void
staffsymbol_draw(xCoordinate_t const     center_x,  // center of note. only used for note and flat
                 yCoordinate_t const     center_y,  // center of note. only used for note and flat
                 staffSymbolName_t const nr,
                 color_t const           color)
{
    symbol_t const * const s = _symbols + static_cast<int>(nr);

    xCoordinate_t const x = s->place.x.value + (s->place.x.relative ? center_x : 0);
    yCoordinate_t const y = s->place.y.value + (s->place.y.relative ? center_y : 0);

    uint8_t mask = 0x80;            // start with the most significant bit
    uint8_t const * b = s->bitmap;  // start with the first byte

    for (uint_least8_t yy = 0; yy < s->size.y; yy++) {
        for (uint_least8_t xx = 0; xx < s->size.x; xx++) {
            if (*b & mask) {
                for (uint_least8_t ye = 0; ye < s->enlarge.y; ye++) {
                    for (uint_least8_t xe = 0; xe < s->enlarge.x; xe++) {
                        _my.tft->drawPixel(x + xx*s->enlarge.x + xe, y + yy*s->enlarge.y + ye, color);
                    }
                }
            }
            mask >>= 1;
            if (mask == 0) {  // move on to the next byte
                mask = 0x80;
                b++;
            }
        }
    }
}

#endif