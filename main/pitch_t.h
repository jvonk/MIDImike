#pragma once

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

typedef uint_least8_t  octavenr_t;

typedef struct pitch_t {
    octavenr_t octavenr;
    notenr_t notenr;
} pitch_t;
