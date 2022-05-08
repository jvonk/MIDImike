#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../sample_t.h"
#include "../../segment_t.h"
#include "../../pitch_t.h"

typedef uint_least8_t  octavenr_t;

typedef enum notenr_t {
    NOTENR_C = 0,
    NOTENR_Db,
    NOTENR_D,
    NOTENR_Eb,
    NOTENR_E,
    NOTENR_F,
    NOTENR_Gb,
    NOTENR_G,
    NOTENR_Ab,
    NOTENR_A,
    NOTENR_Bb,
    NOTENR_B,
    NOTENR_COUNT
} notenr_t;

class Pitch {

    public:
        Pitch(void);
        Pitch(char const * const fullname);
        Pitch(notenr_t const number, octavenr_t const octave);
        Pitch(frequency_t const freq);
        char const * get_shortname();
        octavenr_t get_octavenr();
        notenr_t get_notenr();
        segment_pitch_t get_segment();
        frequency_t get_frequency();
        static segment_pitch_t freq2segment(frequency_t const freq);
#if DST == DST_SERIAL
        static void write_serial_hdr(void);
        void write_serial(char const * const instrument, Pitch & in_pitch, frequency_t freq);
#endif

    private:
        struct class_variables_t {
            octavenr_t octavenr;
            notenr_t notenr;
        } _ = {};
};
