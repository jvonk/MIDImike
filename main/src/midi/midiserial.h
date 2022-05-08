#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../segment_t.h"
#include "../segment/segment.h"

void midiserial_send_notes(SegmentBuf * const segmentBuf);
void midiserial_send_program_change(midiInstrument_t instrument);
void midiserial_send_note_on(segment_pitch_t const pitch, segment_energy_t const energy);
void midiserial_send_note_off(segment_pitch_t const pitch, segment_energy_t const energy);
