#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../config.h"
#include "../../sample_t.h"
#include "../../segment_t.h"
#include "cbuf.h"

typedef uint_least8_t segmentBufIdx_t;

class SegmentBuf {
    public:
        segmentBufIdx_t len(void);
        segment_t * note_start(segmentRelTime_t const ronset, segmentRelTime_t const rduration, segment_pitch_t const pitch, segment_energy_t const velocity);
        segment_t * note_end(segmentRelTime_t const duration, segment_energy_t const energy, segment_t * const ring);
        segment_t * head_ptr(segmentBufIdx_t const age);
        segment_t * tail_ptr(segmentBufIdx_t const age);
        segment_t * pop_ptr(void);
    private:
        CBUF<segmentBufIdx_t, 32, segment_t> ring;
};
