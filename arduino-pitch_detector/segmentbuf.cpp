/**
 * @brief Buffer for note segments
 * @file  segmentbuf.cpp
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 *
 * See cbuf.h for ring buffer implementation
 **/


#include <Arduino.h>
#include <stdint.h>
#include <SPI.h>

#include "config.h"
#include "pitch.h"
#include "cbuf.h"
#include "segment_t.h"
#include "segment.h"
#include "segmentbuf.h"

/*
 * Create a new segment, and initialize the pitch, velocity, onset, offset
 */

segment_t * const
SegmentBuf::noteStart( segmentRelTime_t const  onset,    // relative onset time
                       segmentRelTime_t const  duration, // relative duration time
                       segmentPitch_t const    pitch,
                       segmentEnergy_t const   energy )
{
    // drop the oldest entry if full

    if ( this->ring.isFull() ) {
        this->ring.popAdvanceIdx();
    }

    // add element to ring
    segment_t * const segment = this->ring.pushNextPtr();

    segment->pitch = pitch;
    segment->energy = energy;
    segment->onset = onset;
    segment->duration = duration;
    this->ring.pushAdvanceIdx();  // good enough for now; will be updated as we go on

    return segment;  // piano roll display needs to start showing the note before it is finished
}


/*
 * Finish a segment, and update the offset
 */

segment_t * const
SegmentBuf::noteEnd( segmentRelTime_t const  duration,
                     segmentEnergy_t const   energy,
                     segment_t * const       ring )
{
    ring->energy = energy;
    ring->duration = duration;

    return NULL;
}


segment_t * const
SegmentBuf::headPtr( segmentBufIdx_t const n )
{
    if ( n < this->ring.len() ) {
        return this->ring.getHeadPtr( n );
    }
    return NULL;
}

segment_t * const
SegmentBuf::tailPtr( segmentBufIdx_t const n )
{
    if ( n < this->ring.len() ) {
        return this->ring.getTailPtr( n );
    }
    return NULL;
}

segment_t * const
SegmentBuf::popPtr( void )
{
    if ( this->ring.isEmpty() ) {
        return NULL;
    }
    return this->ring.popPtr();
}

segmentBufIdx_t const
SegmentBuf::len( void )
{
    return this->ring.len();
}
