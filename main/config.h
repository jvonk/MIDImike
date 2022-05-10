#pragma once

#include "sample_t.h"
#include "segment_t.h"
#include "midi_t.h"

#pragma GCC diagnostic error "-Wall"

#define CONFIG_MIDIMIKE_SERIAL_RATE (115200)       // [baud], must be 31250 for USB-midi, 115200 for HairlessMIDI
#define CONFIG_MIDIMIKE_SAMPLE_RATE (9615)         // 9615, 19231, 38462, 76923, ..}
#define CONFIG_MIDIMIKE_WINDOW_SIZE (200)          // short-time window size (restricted by avail memory)
#define CONFIG_MIDIMIKE_FILE_SEC2SKIP (1)          // [s] #seconds to skip when reading note file
#define CONFIG_MIDIMIKE_AUDIBLE_THRESHOLD (20)     // audible threshold [0 .. 255]
#define CONFIG_MIDIMIKE_MIN_SEGMENT_DURATION (3)   // #times the same freq is detected, before we consider it stable
#define CONFIG_MIDIMIKE_MIDI_CHANNEL (1 -1)        // MIDI output channel# (tx 0-based)
#define CONFIG_MIDIMIKE_MIDI_INSTRUMENT (53 -1)    // * MIDI output instrument# (tx 0-based), 1=Grand Piano 53=Choir Ahhs, 61=French Horn

// show memory usage
#define SHOW_MEMORY_USAGE (0)            

// choice: input source
#define SRC_MICR (1)
#define SRC_FILE (2)
#define SRC (SRC_MICR)

// choice: output destination (must be DST_PIANOROLL for USB-MIDI output)
//  DST_SERIAL in combination with SRC_FILE and outputs freq and notes notes recognized, for offline analysis
#define DST_STAFF      (1)
#define DST_PIANOROLL  (2)
#define DST_SERIAL     (3)
#define DST (DST_PIANOROLL)

// enable USB-midi output on the USB connector (requires DST=DST_PIANOROLL, and CONFIG_MIDIMIKE_SERIAL_RATE=31250)
// after changing to USB-midi, connect MOSI2-to-GND and power cycle the Arduino
#define USB_MIDI (0)

// help reduce the number of #if statements in elsewhere
#if SHOW_MEMORY_USAGE
#  define SHOW_MEMORY_USAGE_ONLY(a) do { a; } while (0)
#else
#  define SHOW_MEMORY_USAGE_ONLY(a)
#endif

#define INLINE inline
#define ALWAYS_INLINE __attribute__((always_inline))
#define STATIC static
