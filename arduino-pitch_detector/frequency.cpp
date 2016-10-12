/**
 * @brief Frequency detector, using auto correlation to find frequency (f0) in signal
 * @file  frequency.cpp
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#include <Arduino.h>
#include <stdint.h>
#include <limits.h>
#include "config.h"
#include "debug.h"
#include "microphone.h"
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

	INLINE autoCorr_t const                 // (normalized) auto correlation result
	_autoCorr( samples_t const    samples,  // pointer to signed 8-bit data samples
		       samplesLag_t const lag )     // [in] lag
	{
		// samples[ii] * samples[ii+lag], results in an int16 term
		// sum += term, results in an int32
		// To keep the sum to an int16, each time the term could be divided by nrOfSamples.
		//   to make the division faster, I would round nrOfSamples up to a 2^n boundary. (2BD)

		autoCorr_t ac = 0;

		for ( sampleCnt_t ii = 0; ii < Config::WINDOW_SIZE - lag; ii++ ) {
			ac += ((int16_t)samples[ii] * samples[ii + lag]);
		}
		return ac;
	}

	INLINE float const                 // returns interpolated peak adjustment compared to peak location
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

frequency_t const                                 // returns frequency found, 0 when not found [out]
Frequency::calculate( samples_t const  samples )  // pointer to signed 8-bit data samples [in]
{
	float period = 0;

	if ( samples ) {

		// Search between minimum and maximum frequencies (sampleRate/lagMax, sampleRate/lagMin).
		// For 150 samples and a 9615 S/s, this corresponds to [512 .. 3846 Hz]
		samplesLag_t const lagMin = Config::LAG_MIN; // SAMPLE_LAG_MIN;
		samplesLag_t const lagMax = Config::LAG_MAX;

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
			ac = (float)ac * (float)Config::WINDOW_SIZE / (float)(Config::WINDOW_SIZE - lag);
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
	frequency_t const f = Config::SAMPLE_RATE / period;

	return (period > 0 && f < Config::FREQ_MAX) ? f : 0;
}
#pragma GCC diagnostic pop
