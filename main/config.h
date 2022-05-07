#pragma once

#include "sample_t.h"
#include "segment_t.h"
#include "midi_t.h"

#pragma GCC diagnostic error "-Wall"

#define CONFIG_MIDIMIKE_SERIAL_RATE (31250)        // [baud], must be 31250 for USB-midi, 115200 for HairlessMIDI
#define CONFIG_MIDIMIKE_SAMPLE_RATE (9615)         // 9615, 19231, 38462, 76923, 153846, 307692, 615384}
#define CONFIG_MIDIMIKE_WINDOW_SIZE (200)          // short-time window size (restricted by avail memory)
#define CONFIG_MIDIMIKE_FILE_SEC2SKIP (1)          // [s] #seconds to skip when reading note file
#define CONFIG_MIDIMIKE_AUDIBLE_THRESHOLD (20)     // audible threshold [0 .. 255]
#define CONFIG_MIDIMIKE_MIN_SEGMENT_DURATION (3)   // #times the same freq is detected, before we consider it stable
#define CONFIG_MIDIMIKE_MIDI_CHANNEL (1 -1)        // MIDI output channel# (tx 0-based)
#define CONFIG_MIDIMIKE_MIDI_INSTRUMENT (53 -1)    // * MIDI output instrument# (tx 0-based), 1=Grand Piano 53=Choir Ahhs, 61=French Horn

// values below are calculated
#define CONFIG_MIDIMIKE_LAG_MIN (6)                                                       // [samples] (not seconds!), 10 samples gives a +/-5% error rate (before interpolation)
#define CONFIG_MIDIMIKE_LAG_MAX (CONFIG_MIDIMIKE_WINDOW_SIZE / 2)                         // [samples] (not seconds!), at least two waveforms
#define CONFIG_MIDIMIKE_FREQ_MIN (CONFIG_MIDIMIKE_SAMPLE_RATE / CONFIG_MIDIMIKE_LAG_MAX)  // 96 Hz @ 9615 S/s
#define CONFIG_MIDIMIKE_FREQ_MAX (CONFIG_MIDIMIKE_SAMPLE_RATE / CONFIG_MIDIMIKE_LAG_MIN)  // 1602 Hz @ 9615 S/s and 6 min lag

// show memory usage
#define SHOW_MEMORY_USAGE (0)            

// choice: input source
#define SRC_MICR (1)
#define SRC_FILE (2)
#define SRC (SRC_MICR)

// choice: output destination (must be DST_PIANOROLL for USB-MIDI output)
#define DST_STAFF      (1)
#define DST_PIANOROLL  (2)
#define DST_SERIAL     (3)
#define DST (DST_PIANOROLL)

// enable USB-midi output on the USB connector (requires DST=DST_PIANOROLL, and CONFIG_MIDIMIKE_SERIAL_RATE=31250)
// after changing to USB-midi, connect MOSI2-to-GND and power cycle the Arduino
#define USB_MIDI (1)

// choice: resolution of G-key symbol to show
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

#define INLINE inline
#define ALWAYS_INLINE __attribute__((always_inline))
#define STATIC static
