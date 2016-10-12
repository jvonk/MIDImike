/**
 * @brief MIDI type definitions
 * @file midi_t.h
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "mapping.h"


/***************
 * MIDI commands
 ***************
 *
 * see 
 *   http://www.cs.cmu.edu/~music/cmsip/readings/MIDI%20tutorial%20for%20programmers.html
 *   http://www.midi.org/techspecs/midimessages.php
 */

enum class midiEvent_t : uint8_t PACK8 {
	noteOff = 0x8,
	noteOn = 0x9,
	programChange = 0xC
};

typedef uint8_t midiChannel_t;


// MIDI File Format
//
//   MIDI formats files use IFF type-length-value chunks.  This structure allows new chunk
//   types to be introduced.
//   Integers are stored most-significant-byte-first.
//   A MIDI File always starts with a header chunk, and is followed by one or more track
//   chunks:
//     MThd <length of header data><header data>
//     MTrk <length of track data><track data>


uint_least8_t const FOURCC_LEN = 4;
typedef char midiFourcc_t[FOURCC_LEN];


// MIDI header
//
//   The header chunk gives some basic information about the data in the file.
//     <Header Chunk> = <type> <len> <format> <numTracks> <ticksPerNote>
//   see http://www.music.mcgill.ca/~ich/classes/mumt306/midiformat.pdf

typedef uint32_t midiLen_t;

struct midiChunkHdr_t {
	midiFourcc_t    type;  // four cc type ("MHdr")
	midiLen_t       len;   // #bytes of data to follow
} PACK8;

struct midiHeader_t {
	midiChunkHdr_t  hdr;            // chunk type and length
	struct midiHeaderValue_t {
		int32_t     type;           // format type (0 = one, single multi-channel track)
		uint16_t    numTracks;      // # of tracks (1 for format type 0 )
		uint16_t    ticksPerQnote;  // # of MIDI delta time ticks in a quarter
	} PACK(uint8_t) value;
} PACK8;


// MIDI track
//
//   The track chunks (type MTrk) are where actual music data is stored. Each track chunk 
//   is stream of event.
//     <Track Chunk> = <chunk type> <length> <MTrk event>+
//   Track events include
//     - MIDI events --- any MIDI channel message
//                         <varlen encoded delta-time><....>
//     - meta event ---- non-MIDI information (for this format, or sequencers)
//                         FF <type> <length> <bytes>, such as
//                         FF 51 03 tttttt, to set Tempo (in microseconds per MIDI
//                         quarter-note)
//
//   Delta-time is stored as a variable-length quantity. It represents the amount of time before
//   the following event.If the first event in a track occurs at the very beginning of a track,
//   or if two events occur simultaneously, a delta - time of zero is used.
//   Variable-length numbers are represented 7 bits per byte, most significant bits first.  All
//   bytes except the last have bit 7 set, and the last byte has bit 7 clear.


// MIDI events

struct midiEventNote_t {
	uint8_t channel : 4; // MIDI channel # (0..15)
	uint8_t event : 4;   // MIDI event # (note on, note off, instrument change, ..)
	uint8_t pitch;       // MIDI note number to key-on (0..127)
	uint8_t velocity;    // how hard to press the note (0..127)
} PACK8;


enum class midiSysExTag_t : uint8_t PACK8 {
	meta = 0xFF
};


enum class midiMetaType_t : uint8_t PACK8 {
	setTempo = 0x51,
	trackEnd = 0x2F
};


typedef uint32_t midiTime_t;   // [msec], wraps at ~64 seconds
typedef uint8_t midiMetaLen_t;

struct midiMeta_t {
	midiSysExTag_t  sysEx;     // sysEx tag, 0xFF for META data
	midiMetaType_t  type;      // type
	midiMetaLen_t   len;       // len (really a variable length, but we only have values < 0x7F)
	uint8_t         value[3];  // len indicates length, the size 3 is just a max
} PACK8;

midiMetaLen_t const META_TEMPOCHANGE_LEN = 3;
midiMetaLen_t const META_TRACKEND_LEN = 0;

typedef uint_least8_t midiInstrument_t;
