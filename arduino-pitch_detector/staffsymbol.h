/**
 * @brief Show symbol on staff
 * @file  staffsymbol.h
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <Adafruit_GFX.h>    // core graphics
#include <Adafruit_ST7735.h> // hardware-specific graphics
#include "config.h"
#include "coordinate_t.h"

# if DST == DST_STAFF

enum class staffSymbolName_t {
    flat = 0,
    toLow,
    toHigh,
    note
# if GKEY != GKEY_NONE
    ,gKey
# endif
    ,COUNT
};
uint_least8_t const staffSymbolName_COUNT = static_cast<int>(staffSymbolName_t::COUNT);

namespace StaffSymbol {

    void
        begin( Adafruit_ST7735 * tft,
               xCoordinate_t const displayWidth,
               yCoordinate_t const displayHeight,
               yCoordinate_t const noteRadius,
               yCoordinate_t const bottom2loStaff,  // distance from bottom of screen to low staff line
               yCoordinate_t const top2hiStaff,     // distance from top of screen to high staff line
               yCoordinate_t const yG4 );           // y position for note G4

    // end() method not needed, 'cause loop() never stops

    void
        draw( xCoordinate_t const      x_,  // center of note. only used for note and flat
              yCoordinate_t const      y_,  // center of note. only used for note and flat
              staffSymbolName_t const  nr,
              color_t const            color );
};

# endif
