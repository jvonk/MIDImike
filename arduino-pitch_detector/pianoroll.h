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
