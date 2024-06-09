/** 
 * @brief Asynchronous microphone driver
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
#include "../../sample_t.h"
#include "../debug/debug.h"
#include "microphone.h"
#include "adc_t.h"

#if (SRC == SRC_MICR)

namespace {
    typedef struct amplitudeRange_t {
        sample_t min;
        sample_t max;
    } amplitudeRange_t;

    typedef struct file_scope_variables_t {
        sample_cnt_t cnt;
        amplitudeRange_t range;
        sample_t * samples;
        uint8_t analogPort;
        uint8_t prescaler;
    } file_scope_variables_t;

    file_scope_variables_t volatile _ = {};  // volatile 'cause data updates in ISR
}

    /******************
     * microphone_begin
     ******************/

void
microphone_begin(uint8_t const port)
{
    _.analogPort = port;

    // allocate memory (no freed, 'cause `loop` never stops)
    _.samples = new sample_t[CONFIG_MIDIMIKE_WINDOW_SIZE];
    //ASSERT((_.samples));

    // determine prescaler setting for ADCSRA
    _.prescaler = 0;
    for (uint32_t d = 16e6 / 13; CONFIG_MIDIMIKE_SAMPLE_RATE < d; d /= 2) {
        _.prescaler++;
    }
    
    microphone_start();  // start gathering samples
}

    /******************
     * microphone_start
     ******************
     * Application signals that it no longer needs access to the samples.
     * This driver will reuse the "samples" buffer and start collecting
     * new samples.  Refer to top of file for details
     */

void
microphone_start(void)
{
    _.cnt = 0;

    // start gathering new samples
    // (no need to disable interrupts, after all this interrupt is off, and we're turning it on here)

    ADCSRB =
        ADCSRB_MULTIPLEXER_ENABLE;

    ADMUX =
        ADMUX_REFERENCE_EXT |
        ADMUX_LEFT_ALIGN |
        (ADMUX_INPUT_MASK & _.analogPort);

    ADCSRA =
        _.prescaler |
        ADCSRA_AUTO_TRIGGER_ENABLE |
        ADCSRA_IRQ_ENABLE |
        ADCSRA_CONVERT_ENABLE |
        ADCSRA_CONVERT_START;
}

    /************************
     * microphone_get_samples
     ************************/

samples_t                                                 // returns pointer to array of data samples, NULL on failure
microphone_get_samples(amplitude_t * const amplitudePtr, bool * const clipPtr)
{
    while (ADCSRA & ADCSRA_IRQ_ENABLE) {
        // spin wait until all samples are available
    }

    bool clipping = (_.range.min == SCHAR_MIN) || (_.range.max == SCHAR_MAX);
    *clipPtr = clipping;
    amplitude_t amplitude = (int16_t)_.range.max - _.range.min; // top-top [0..255]

    *amplitudePtr = amplitude/2; // range [0..127]

    return (amplitude / 2 > CONFIG_MIDIMIKE_AUDIBLE_THRESHOLD) && !clipping ? _.samples : NULL;
}

    /*****
     * ISR
     *****/

ISR(ADC_vect)
{
    sample_t const s = ADCH + SCHAR_MIN;  // remove voltage bias by changing range from [0..255] to [-128..127]

        // update min and max, so peak-to-peak value can be determined
    if (_.cnt == 0) {
        _.range.min = SCHAR_MAX;
        _.range.max = SCHAR_MIN;
    }
    if (s < _.range.min) {
        _.range.min = s;
    }
    if (s > _.range.max) {
        _.range.max = s;
    }

    if (_.cnt < CONFIG_MIDIMIKE_WINDOW_SIZE) {
        _.samples[_.cnt++] = s;
    } else {            
        ADCSRA =  // we're done
            _.prescaler |
            ADCSRA_AUTO_TRIGGER_DISABLE |
            ADCSRA_IRQ_DISABLE |
            ADCSRA_CONVERT_ENABLE;
    }
}

#endif