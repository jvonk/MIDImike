/**
 * @brief Show MIDI data on piano roll
 * @file  pianoroll.h
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
#include "segment_t.h"

namespace PianoRoll {

    void begin(
        uint_least8_t tftCS,    // SPI TFT Chip Select
        uint_least8_t dc,       // SPI Data/Command
        uint_least8_t reset );  // SPI Reset

    void
        clear( void );

    void show(
        absoluteTime_t const  lastOffset,    // needed to calculate absolute times
        SegmentBuf * const    segmentBuf );  // midi buffer containing notes

};
