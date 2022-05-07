#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "../../segment_t.h"

namespace MidiFile {

    int_least8_t
        begin( uint_least8_t const cs );

    int_least8_t
        write( SegmentBuf * const  segmentBuf,  // buffer with segmented notes
               char const * const  fname );     // file name to write to on SD card

};
