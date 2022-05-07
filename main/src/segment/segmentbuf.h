#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "cbuf.h"
#include "../../config.h"
#include "../../sample_t.h"
#include "../../segment_t.h"

typedef uint_least8_t segmentBufIdx_t;

class SegmentBuf {

public:

    segmentBufIdx_t
        len( void );

    segment_t *
        noteStart( segmentRelTime_t const  ronset,
                   segmentRelTime_t const  rduration,
                   segmentPitch_t const    pitch,
                   segmentEnergy_t const   velocity );

    segment_t *
        noteEnd( segmentRelTime_t const  duration,
                 segmentEnergy_t const   energy,
                 segment_t * const       ring );

    segment_t *
        headPtr( segmentBufIdx_t const age );

    segment_t *
        tailPtr( segmentBufIdx_t const age);

    segment_t *
        popPtr( void );

private:

    CBUF<segmentBufIdx_t, 32, segment_t> ring;

};
