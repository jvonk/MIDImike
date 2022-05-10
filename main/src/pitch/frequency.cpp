/**
 * @brief Frequency detector, using auto correlation to find frequency (f0) in signal
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
#include <limits.h>
#include "../../config.h"
#include "../microphone/microphone.h"
#include "frequency.h"

typedef enum state_t {
	STATE_FIND_POS_SLOPE = 0,
	STATE_FIND_NEG_SLOPE,
	STATE_FOUND_PEAK,
} state_t;

typedef sample_cnt_t samplesLag_t;
typedef int32_t autoCorr_t;

// calculate auto correlation for "lag"

static INLINE autoCorr_t               // (normalized) auto correlation result
_auto_corr(samples_t const    samples,  // pointer to signed 8-bit data samples
  		   samplesLag_t const lag)      // lag
{
	// samples[ii] * samples[ii+lag], results in an int16 term
	// sum += term, results in an int32
	// To keep the sum to an int16, each time the term could be divided by nrOfSamples.
	//   to make the division faster, I would round nrOfSamples up to a 2^n boundary. (2BD)

	autoCorr_t ac = 0;

	for (sample_cnt_t ii = 0; ii < CONFIG_MIDIMIKE_WINDOW_SIZE - lag; ii++) {
		ac += ((int16_t)samples[ii] * samples[ii + lag]);
	}
	return ac;
}

static INLINE float                       // returns interpolated peak adjustment compared to peak location
_quad_interp_adj(autoCorr_t const left,   // sample value left of the peak
			     autoCorr_t const mid,    // sample value at the peak
			     autoCorr_t const right)  // sample value right of the peak
{
	float const adj = (float)0.5 * (right - left) / (2 * mid - left - right);
	return adj;
}

#define INTERPOLATE (0)
#define NORMALIZE (0)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"

frequency_t                                    // returns frequency found, 0 when not found [out]
frequency_calculate(samples_t const  samples)  // pointer to signed 8-bit data samples [in]
{
	if (!samples) {
		return 0;
	}

	float period = 0;
	autoCorr_t const acMax = _auto_corr(samples, 0);  // initial peak = measure of the energy in the signal
	autoCorr_t const acThreshold = (float)acMax * (NORMALIZE ? 4/5 : 2/3);  // threshold below we ignore peaks
	autoCorr_t acPrev = acMax;
	state_t state = STATE_FIND_POS_SLOPE;   // ensure C++11 is enabled

	for (samplesLag_t lag = CONFIG_MIDIMIKE_LAG_MIN;
 		 (lag < CONFIG_MIDIMIKE_LAG_MAX) && (state != STATE_FOUND_PEAK); lag++) {

		autoCorr_t ac = _auto_corr(samples, lag);  // unnormalized autocorrelation for time "lag"

		if (NORMALIZE) {  // normalize for introduced zeros			
			ac = (float)ac * (float)CONFIG_MIDIMIKE_WINDOW_SIZE / (float)(CONFIG_MIDIMIKE_WINDOW_SIZE - lag);
		}

		// find peak after the initial maximum
		switch (state) {
			case STATE_FIND_POS_SLOPE:
				if ((ac > acThreshold) && (ac > acPrev)) {
					state = STATE_FIND_NEG_SLOPE;
				}
				break;
			case STATE_FIND_NEG_SLOPE:
				if (ac <= acPrev) {
					state = STATE_FOUND_PEAK;
					if (INTERPOLATE) {
						period = lag - 1 + _quad_interp_adj(
							_auto_corr(samples, lag - 2), 
							acPrev, ac);
					} else {
						period = lag - 1;  // we got 1 past it
					}
				}
				break;
		}
		acPrev = ac;
	}

	if (state != STATE_FOUND_PEAK) {
		Serial.println("peak not found");
		return 0;
	}

	frequency_t const f = (float)CONFIG_MIDIMIKE_SAMPLE_RATE / period;

	//Serial.print(period); Serial.print(", ");
	//Serial.print(f); Serial.print(", ");
	bool const ok = f < CONFIG_MIDIMIKE_FREQ_MAX;
	return ok ? f : 0;
}
#pragma GCC diagnostic pop
