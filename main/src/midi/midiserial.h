#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "../../segment_t.h"

namespace MidiSerial {

	void
		send( SegmentBuf * const  segmentBuf );

	void
		noteOn(segmentPitch_t const pitch,
		       segmentEnergy_t const energy);

	void
		noteOff(segmentPitch_t const pitch,
		        segmentEnergy_t const energy);

	void
		programChange(midiInstrument_t instrument);

};
