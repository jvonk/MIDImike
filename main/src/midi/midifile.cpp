/**
 * @brief Write notes to MIDI file
 * 
 * © Copyright 2015-2016,2022 Johan Vonk
 * 
 * This file is part of Arduino_pitch-detector.
 * 
 * Arduino_pitch-detector is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * Arduino_pitch-detector is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Arduino_pitch-detector. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright 2015-2016,2022 Johan Vonk
 **/

#include <Arduino.h>
#include <stdint.h>
#include <SD.h>

#include "../../config.h"
#include "../../sample_t.h"
#include "../pitch/pitch.h"
#include "../segment/segmentbuf.h"
#include "midi_t.h"
#include "midiserial.h"
#include "midifile.h"

#if (FILE == FILE_MIDI)

midiMetaLen_t const META_TEMPOCHANGE_LEN = 3;
midiMetaLen_t const META_TRACKEND_LEN = 0;

// work towards 1 tick per msec
#define BEATS_PER_MIN (125)
#define TICKS_PER_BEAT (1000 / BEATS_PER_MIN)

static bool                            // returns true on success, false otherwise
_write_bytes(File & f,                 // file to append to
             void const * const data,  // data to write
             size_t const dataLen)     // length of data to write
{
    return f.write((uint8_t *)data, dataLen) == dataLen;
}

static bool                // returns `true` on success, `false` otherwise
_write_midi_hdr(File & f)  // file to append to
{
    // for example 4D 54 68 64 08 00 00 00 00 00 00 00 01 00 60 00
    // where type="MHdr" len=8(0x00000008) format=0(0x00) tracks=1(0x0001) ticksPerQnote=(0x0060)

    midiHeader_t const header = {
        {{'M', 'T', 'h', 'd'}, sizeof(midiHeader_t) - sizeof(midiChunkHdr_t)},
        {0, 1, TICKS_PER_BEAT}
    };
    return _write_bytes(f, &header, sizeof(header));
}

static bool                                 // returns `true` on success, `false` otherwise
_write_midi_track_begin(File & f,           // file to append to
                        uint32_t tracklen)  // number of bytes to follow
{
    // for example 4D 54 72 6B 03 00 00 00, where type="MTrk", len=3(0x00000003)

    midiChunkHdr_t const track = {{'M', 'T', 'r', 'k'}, tracklen};

    return _write_bytes(f, &track, sizeof(track));
}

static bool                                         // returns `true` on success, `false` otherwise
_write_midi_tracktempo_event(File & f,              // file to append to 
                             uint32_t const tempo)  // tempo [usec/quaternote]
{
    midiMeta_t const event = {
        .sysEx = MIDI_SYSEX_TAG_META,
        .type = MIDI_META_TYPE_SET_TEMPO,
        .len = META_TEMPOCHANGE_LEN,
        .value = {
            (uint8_t)((tempo >> 16) & 0xFF),
            (uint8_t)((tempo >> 8) & 0xFF),
            (uint8_t)((tempo >> 0) & 0xFF)
        }
    };
    return _write_bytes(f, &event, 3 + META_TEMPOCHANGE_LEN);
}

static bool                      // returns `true` on success, `false` otherwise
_write_midi_integer(File & f,    // file to append to
                    uint32_t d)  // value to write
{
    // MIDI lengths are stored as variable length integers, between one and four bytes long.
    // Each byte only uses the lower 7-bits, with the MSB set if there is another length byte following.
    // The bytes are in big endian order.

    uint32_t buffer = d & 0x7F;

    while ((d >>= 7) != 0) {
        buffer <<= 8;
        buffer |= ((d & 0x7F) | 0x80);
    }
    while (true) {
        size_t const len = sizeof(uint8_t);
        if (_write_bytes(f, &buffer, len) == false) {
            return false;
        }
        if (buffer & 0x80) {
            buffer >>= 8;
        } else {
            break;
        }
    }
    return true;
}

static INLINE uint32_t
_msec2ticks(uint32_t const ms)
{
    return (uint64_t)ms * BEATS_PER_MIN * TICKS_PER_BEAT / 60000;
}

static bool                                              // returns `true` on success, `false` otherwise
_write_midi_note_event(File & f,                         // file to append to
                       midiTime_t const delay,           // delay compared to prior event (0 if none) [msec]
                       midiEvent_t const eventNr,        // note event
                       segment_pitch_t const pitch,      // note pitch
                       segment_energy_t const velocity)  // note velocity
{
    // for example 00 19 3E 38, where delay=0(0x00), event=NOTE_ON(0x19), pitch=0x3E, velocity=0x38, or
    //             81 01 18 3E 38, where delay=...(0x8101), event=NOTE_OFF(0x18), pitch=0x3E velocity=0x3B

    _write_midi_integer(f, _msec2ticks(delay));

    uint8_t const n1 = static_cast<uint8_t>(eventNr) & 0x0F;
    uint8_t const n2 = CONFIG_MIDIMIKE_MIDI_CHANNEL & 0x0F;

    midiEventNote_t event = {n1, n2, pitch, velocity};
    size_t const len = sizeof(event);

    return _write_bytes(f, &event, len);
}

static bool                      // returns true on success, false otherwise
_write_midi_track_end(File & f)  // file to append to
{
    // e.g. FF 2F 00, where sysEx=meta(0xFF), endoftrack(0x2F) len=0(0x00)

    midiMeta_t const end = {
        .sysEx = MIDI_SYSEX_TAG_META,
        .type = MIDI_META_TYPE_TRACK_END,
        .len = META_TRACKEND_LEN,
        .value = {0x00, 0x00, 0x00}
    };
    return _write_bytes(f, &end, 3 + META_TRACKEND_LEN);
}

    /****************
     * midifile_write
     ****************/
    
int_least8_t
midifile_write(SegmentBuf * const segmentBuf,  // buffer with segmented notes
               char const * const fname)       // file name to write to on SD card
{
    File f = SD.open(fname, FILE_WRITE);
    if (!f) {
        return -1;
    }

    // write header

    if (_write_midi_hdr(f) == false) {
        return -2;
    }

    // write track

    if (_write_midi_track_begin(f, META_TEMPOCHANGE_LEN + segmentBuf->len() * sizeof(midiEventNote_t)) == false ||
         _write_midi_tracktempo_event(f, 60000000UL / BEATS_PER_MIN) == false) {  // 60000000 usec/min
        return -3;
    }

    uint_least8_t ii = 0;
    while (segment_t const * note = segmentBuf->tail_ptr(ii++)) {
        if (_write_midi_note_event(f, note->onset, MIDIEVENT_NOTE_ON, note->pitch, note->energy) == false ||
             _write_midi_note_event(f, note->duration, MIDIEVENT_NOTE_OFF, note->pitch, note->energy) == false) {
            return -4;
        }
    }

    if (_write_midi_track_end(f) == false) {
        return -5;
    }

    f.close();
    return 0;
}

#endif