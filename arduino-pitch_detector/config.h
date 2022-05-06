#pragma once

#include "sample_t.h"
#include "segment_t.h"
#include "midi_t.h"

#pragma GCC diagnostic error "-Wall"

namespace Config {
    unsigned long const SERIAL_RATE = 31250;           // [baud], must be 31250 for USB-midi, 115200 for HairlessMIDI
    sampleRate_t const SAMPLE_RATE = 9615;             // 9615, 19231, 38462, 76923, 153846, 307692, 615384}
    sampleCnt_t const WINDOW_SIZE = 200;               // short-time window size (restricted by avail memory)
    sampleCnt_t const FILE_SEC2SKIP = 1;               // [s] #seconds to skip when reading note file
    amplitude_t const AUDIBLE_THRESHOLD = 20;          // audible threshold [0 .. 255]
    segmentRelTime_t const MIN_SEGMENT_DURATION = 3;   // #times the same freq is detected, before we consider it stable
    midiChannel_t const MIDI_CHANNEL = 1 -1;           // MIDI output channel# (tx 0-based)
    midiInstrument_t const MIDI_INSTRUMENT = static_cast<midiInstrument_t>(53 -1); // * MIDI output instrument# (tx 0-based), 1=Grand Piano 53=Choir Ahhs, 61=French Horn

    // values below are calculated
    sampleCnt_t const LAG_MIN = 6;                       // [samples] (not seconds!), 10 samples gives a +/-5% error rate (before interpolation)
    sampleCnt_t const LAG_MAX = WINDOW_SIZE / 2;         // [samples] (not seconds!), at least two waveforms
    frequency_t const FREQ_MIN = SAMPLE_RATE / LAG_MAX;  // 96 Hz @ 9615 S/s
    frequency_t const FREQ_MAX = SAMPLE_RATE / LAG_MIN;  // 1602 Hz @ 9615 S/s and 6 min lag
}

// show memory usage
#define SHOW_MEMORY_USAGE (0)            

// input source
#define SRC_MICR (1)
#define SRC_FILE (2)
#define SRC (SRC_MICR)

// output destination (must be DST_PIANOROLL for USB-MIDI output)
#define DST_STAFF      (1)
#define DST_PIANOROLL  (2)
#define DST_SERIAL     (3)
#define DST (DST_PIANOROLL)

// enable USB-midi output on the USB connector (requires DST=DST_PIANOROLL, and Config::SERIAL_RATE=31250)
// after changing to USB-midi, connect MOSI2-to-GND and power cycle the Arduino
#define USB_MIDI (1)

// resolution of G-key symbol to show
#if DST == DST_STAFF
# define GKEY_NONE  (1)
# define GKEY_LORES (2)     /* requires ~88 bytes of SDRAM */
# define GKEY_HIRES (3)     /* requires ~362 bytes of SDRAM */
# define GKEY (GKEY_LORES)
#endif

// debug option: simple ASCII plot of samples waveform on serial monitor
#define SHOW_SAMPLES (0)

// help reduce the number of #if statements in other files
#if SHOW_MEMORY_USAGE
#  define SHOW_MEMORY_USAGE_ONLY(a) do { a; } while (0)
#else
#  define SHOW_MEMORY_USAGE_ONLY(a)
#endif

// extra level of indirection allows the preprocessor to expand the macro
// before they are converted to strings
#if 0
# define STR_HELPER(x) #x
# define STR(x) STR_HELPER(x)
#endif

    // historic relics ;-)
#ifdef DEBUG_ICE
# define INLINE
# if 0
#  define STATIC
# endif
#else
# define INLINE inline
# define ALWAYS_INLINE __attribute__((always_inline))
# if 0
#  define STATIC static
# endif
#endif

