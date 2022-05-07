/**
 * @brief Buffer for note segments
 * 
 * See cbuf.h for ring buffer implementation
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
#include <SPI.h>

#include "cbuf.h"
#include "../../config.h"
#include "../../segment_t.h"
#include "../pitch/pitch.h"
#include "segment.h"
#include "segmentbuf.h"

/*
 * Create a new segment, and initialize the pitch, velocity, onset, offset
 */

segment_t *
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

segment_t *
SegmentBuf::noteEnd( segmentRelTime_t const  duration,
                     segmentEnergy_t const   energy,
                     segment_t * const       ring )
{
    ring->energy = energy;
    ring->duration = duration;

    return NULL;
}


segment_t *
SegmentBuf::headPtr( segmentBufIdx_t const n )
{
    if ( n < this->ring.len() ) {
        return this->ring.getHeadPtr( n );
    }
    return NULL;
}

segment_t *
SegmentBuf::tailPtr( segmentBufIdx_t const n )
{
    if ( n < this->ring.len() ) {
        return this->ring.getTailPtr( n );
    }
    return NULL;
}

segment_t *
SegmentBuf::popPtr( void )
{
    if ( this->ring.isEmpty() ) {
        return NULL;
    }
    return this->ring.popPtr();
}

segmentBufIdx_t
SegmentBuf::len( void )
{
    return this->ring.len();
}
