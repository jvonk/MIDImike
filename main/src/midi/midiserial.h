#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../../segment_t.h"

void midiserial_send_notes(SegmentBuf * const  segmentBuf);
void midiserial_send_program_change(midiInstrument_t instrument);
void midiserial_send_note_on(segmentPitch_t const pitch, segmentEnergy_t const energy);
void midiserial_send_note_off(segmentPitch_t const pitch, segmentEnergy_t const energy);
