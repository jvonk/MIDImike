/**
 * @brief Write notes to MIDI file
 * @file  midifile.h
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

namespace MidiFile {

    int_least8_t const
        begin( uint_least8_t const cs );

    int_least8_t const
        write( SegmentBuf * const  segmentBuf,  // buffer with segmented notes
               char const * const  fname );     // file name to write to on SD card

};
