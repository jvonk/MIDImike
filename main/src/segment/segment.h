#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../config.h"
#include "../../sample_t.h"
#include "../../segment_t.h"
#include "segmentbuf.h"

typedef enum segment_energystate_t {
    SEGMENT_ENERGYSTATE_FIND_NEG_SLOPE,
    SEGMENT_ENERGYSTATE_FIND_POS_SLOPE,
    SEGMENT_ENERGYSTATE_FOUND_POS_SLOPE
} segment_energystate_t;

typedef struct segment_energytrend_t {
    segment_energystate_t state;
    segment_energy_t      min;
    segment_energy_t      max;
    segment_energy_t      previous;
} segment_energytrend_t;

class SegmentBuf;

class Segment {

    public:
        Segment(void);
        void put(absolute_time_t const now, segment_pitch_t const pitch, segment_energy_t const energy, SegmentBuf * const segmentBuf);
        absolute_time_t get_last_offset(void);

    private:
        struct segment_cv_t {
            struct segment_cv_candidate_t {
                uint_least8_t         count;
                segment_pitch_t       pitch;
                absolute_time_t       start_time;
                segment_energytrend_t energy_trend;
            } candidate;
            segment_energytrend_t  energy_trend;
            struct time_t {
                absolute_time_t  prev_end;
                absolute_time_t  last_offset;
                absolute_time_t  last_event;
            } time;
            segment_t * note;  // current note, NULL if none
        } cv;  // class values

        segmentRelTime_t _diff_time(absolute_time_t const t);
        void _energy_init(segment_energytrend_t * const trend);
        void _energy_update(segment_energytrend_t  * const trend, segment_energy_t const energy);
};
