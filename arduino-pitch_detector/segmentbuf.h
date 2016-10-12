/**
 * @brief Buffer for note segments
 * @file  segmentbuf.h
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
#include "config.h"
#include "sample_t.h"
#include "cbuf.h"
#include "segment_t.h"

typedef uint_least8_t segmentBufIdx_t;

class SegmentBuf {

public:

    segmentBufIdx_t const
        len( void );

    segment_t * const
        noteStart( segmentRelTime_t const  ronset,
                   segmentRelTime_t const  rduration,
                   segmentPitch_t const    pitch,
                   segmentEnergy_t const   velocity );

    segment_t * const
        noteEnd( segmentRelTime_t const  duration,
                 segmentEnergy_t const   energy,
                 segment_t * const       ring );

    segment_t * const
        headPtr( segmentBufIdx_t const age );

    segment_t * const
        tailPtr( segmentBufIdx_t const age);

    segment_t * const
        popPtr( void );

private:

    CBUF<segmentBufIdx_t, 32, segment_t> ring;

};
