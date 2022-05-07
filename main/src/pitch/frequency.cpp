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

namespace {

	enum class State {
		findPosSlope = 0,
		findNegSlope,
		secondPeak,
	};

	typedef sampleCnt_t samplesLag_t;
	typedef int32_t autoCorr_t;

	 // Calculate auto correlation for "lag"

	INLINE autoCorr_t                       // (normalized) auto correlation result
	_autoCorr( samples_t const    samples,  // pointer to signed 8-bit data samples
		       samplesLag_t const lag )     // [in] lag
	{
		// samples[ii] * samples[ii+lag], results in an int16 term
		// sum += term, results in an int32
		// To keep the sum to an int16, each time the term could be divided by nrOfSamples.
		//   to make the division faster, I would round nrOfSamples up to a 2^n boundary. (2BD)

		autoCorr_t ac = 0;

		for ( sampleCnt_t ii = 0; ii < CONFIG_MIDIMIKE_WINDOW_SIZE - lag; ii++ ) {
			ac += ((int16_t)samples[ii] * samples[ii + lag]);
		}
		return ac;
	}

	INLINE float                             // returns interpolated peak adjustment compared to peak location
	_quadInterpAdj( autoCorr_t const left,   // sample value left of the peak
	                autoCorr_t const mid,    // sample value at the peak
					autoCorr_t const right ) // sample value right of the peak
	{
		float const adj = (float)0.5 * (right - left) / (2 * mid - left - right);
		return adj;
	}

} // name space


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#define INTERPOLATE (1)
#define NORMALIZE (0)

frequency_t                                       // returns frequency found, 0 when not found [out]
Frequency::calculate( samples_t const  samples )  // pointer to signed 8-bit data samples [in]
{
	float period = 0;

	if ( samples ) {

		// Search between minimum and maximum frequencies (sampleRate/lagMax, sampleRate/lagMin).
		// For 150 samples and a 9615 S/s, this corresponds to [512 .. 3846 Hz]
		samplesLag_t const lagMin = CONFIG_MIDIMIKE_LAG_MIN; // SAMPLE_LAG_MIN;
		samplesLag_t const lagMax = CONFIG_MIDIMIKE_LAG_MAX;

		// determine threshold below we ignore peaks
		autoCorr_t const acMax = _autoCorr( samples, 0 );  // initial peak = measure of the energy in the signal
#if NORMALIZE
		autoCorr_t const acThreshold = (float)acMax * 4/5;      // or .71 empirical value
#else
		autoCorr_t const acThreshold = (float)acMax * 2/3;      // empirical value
#endif
		autoCorr_t acPrev = 0;
		State state = State::findPosSlope;   // ensure C++11 is enabled

		for ( samplesLag_t lag = lagMin; (lag < lagMax) && (state != State::secondPeak); lag++ ) {

			// unnormalized autocorrelation for time "lag"
			autoCorr_t ac = _autoCorr( samples, lag );
#if NORMALIZE
			// normalize for introduced zeros
			ac = (float)ac * (float)CONFIG_MIDIMIKE_WINDOW_SIZE / (float)(CONFIG_MIDIMIKE_WINDOW_SIZE - lag);
#endif
			// find peak after the initial maximum
			switch ( state ) {
				case State::findPosSlope:
					if ( (ac > acThreshold) && (ac > acPrev) ) {
						state = State::findNegSlope;
					}
					break;
				case State::findNegSlope:
					if ( ac <= acPrev ) {
						state = State::secondPeak;
#if INTERPOLATE
						period = lag - 1 + _quadInterpAdj( _autoCorr( samples, lag - 2 ),
							acPrev, ac );
#else
						period = lag - 1;
#endif
					}
					break;
			}
			acPrev = ac;
		}
	}
	frequency_t const f = CONFIG_MIDIMIKE_SAMPLE_RATE / period;

	return (period > 0 && f < CONFIG_MIDIMIKE_FREQ_MAX) ? f : 0;
}
#pragma GCC diagnostic pop
