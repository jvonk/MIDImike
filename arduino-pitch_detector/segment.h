#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "config.h"
#include "sample_t.h"
#include "segment_t.h"
#include "segmentbuf.h"

struct segmentEnergyTrend_t {
    segmentEnergyState_t state;
    segmentEnergy_t      min;
    segmentEnergy_t      max;
    segmentEnergy_t      previous;
};

class SegmentBuf;

class Segment {

public:

    Segment( void );

    void
        begin( void );

    void
        put( absoluteTime_t const   now,          // absolute current time (at the end of chunk) [msec]
             segmentPitch_t const   pitch,        // midi pitch measured
             segmentEnergy_t const  energy,       // energy/loudness measured [0..127]
             SegmentBuf * const     segmentBuf ); // segment buffer to write note to

    absoluteTime_t
        getLastOffset( void );

private:

    struct SegmentCv_t {
        struct segmentCandidate_t {
            uint_least8_t         count;
            segmentPitch_t        pitch;
            absoluteTime_t        startTime;
            segmentEnergyTrend_t  energyTrend;
        } candidate;

        segmentEnergyTrend_t  energyTrend;

        absoluteTime_t        prevEndTime;
        absoluteTime_t        lastOffset;
        absoluteTime_t        lastEventTime;

        segment_t *           note;     // current note, NULL if none
    } cv;  // class values

    segmentRelTime_t
        difftime_( absoluteTime_t const  t );

    void
        energyInit_( segmentEnergyTrend_t * const  trend );

    void
        energyUpdate_( segmentEnergyTrend_t  * const  trend,
                       segmentEnergy_t const          energy );
};
