/** 
 * @brief Asynchronous microphone driver
 * @file  microphone.cpp
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015, Coert Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#include <Arduino.h>
#include <stdint.h>
#include <limits.h>

#include "config.h"
#include "debug.h"
#include "sample_t.h"
#include "microphone.h"
#include "adc_t.h"


namespace {

    struct filevariables_t {
        uint8_t     analogPort;
        uint8_t     prescaler;
        sample_t *  samples;  // updated by ISR
    } static fv;  // file scope variables

    struct amplitudeRange_t {
        sample_t min;
        sample_t max;
    };
    struct isr_t {
        sampleCnt_t ii;
        amplitudeRange_t range;
    };

    isr_t volatile _isr = {  // data updated while interrupt enabled
        0,
        {SCHAR_MAX, SCHAR_MIN}
    };


#if SHOW_SAMPLES
    void
    _plotSamples( samples_t const    samples,       // pointer to 8-bit data samples [in]
                  sampleCnt_t const  nrOfSamples )  // number of data samples [in]
    {
        for ( uint32_t ii = 0; ii < nrOfSamples; ii++ ) {
            int16_t d = (int16_t)samples[ii] - SCHAR_MIN;
            while ( d > 0 ) {
                Serial.print ( " " );
                d = d - 4;
            }
            Serial.println( "*" );
            //Serial.println ( samples[ii], DEC );
        }
    }
#endif
}


void
Microphone::begin( uint8_t const port )
{
    fv.analogPort = port;

    // allocate memory
    //   no free, 'cause loop() never stops
    fv.samples = new sample_t[Config::WINDOW_SIZE];
    ASSERT(( fv.samples ));

    // determine fv.prescaler setting for ADCSRA
    fv.prescaler = 0;
    for ( uint32_t d = 16e6 / 13; Config::SAMPLE_RATE < d; d /= 2 ) {
        fv.prescaler++;
    }

    // start gathering samples
    Microphone::update();
}


samples_t const            // returns pointer to where new samples will be stored if successful
Microphone::update( void )
{
    // init private date for ISR (so we don't have to test for ii==0 inside the ISR)
    ::isr_t volatile * const isr = &_isr;
    isr->ii = 0;
    isr->range.min = SCHAR_MAX;
    isr->range.max = SCHAR_MIN;

    // start gathering new samples
    // (no need to disable interrupts, after all this interrupt is off, and we're turning it on here)

    ADCSRB =
        ADCSRB_MULTIPLEXER_ENABLE;

    ADMUX =
        ADMUX_REFERENCE_EXT |
        ADMUX_LEFT_ALIGN |
        (ADMUX_INPUT_MASK & fv.analogPort);

    ADCSRA =
        fv.prescaler |
        ADCSRA_AUTO_TRIGGER_ENABLE |
        ADCSRA_IRQ_ENABLE |
        ADCSRA_CONVERT_ENABLE |
        ADCSRA_CONVERT_START;

    return 0;
}


// Get Samples

samples_t const               // returns pointer to array of data samples, NULL on failure
Microphone::getSamples( amplitude_t * const amplitudePtr )
{

        // wait until all samples are available

    while ( ADCSRA & ADCSRA_IRQ_ENABLE ) {
    }

#if SHOW_SAMPLES
    _plotSamples ( fv.samples, SAMPLE_COUNT );
#endif
    ::isr_t volatile * const isr = &_isr;

    bool clipping = (isr->range.max == SCHAR_MIN) || (isr->range.max == SCHAR_MAX);
    amplitude_t amplitude = (int16_t)isr->range.max - isr->range.min; // top-top [0..255]

    *amplitudePtr = amplitude/2; // range [0..127]
    return (amplitude / 2 > Config::AUDIBLE_THRESHOLD) && !clipping ? fv.samples : NULL;
}


    /***************************
     * Interrupt Service Routine
     ***************************/

ISR ( ADC_vect )
{
    ::isr_t volatile * const isr = &_isr;
    char const s = ADCH + SCHAR_MIN;  // remove voltage bias by changing range from [0..255] to [-128..127]

        // update min and max, so peak-to-peak value can be determined
    if ( isr->ii == 0 ) {
        isr->range.min = SCHAR_MAX;
        isr->range.max = SCHAR_MIN;
    }
    if ( s < isr->range.min ) {
        isr->range.min = s;
    }
    if ( s > isr->range.max ) {
        isr->range.max = s;
    }

    if ( isr->ii < Config::WINDOW_SIZE ) {
        fv.samples[isr->ii++] = s;
    } else {
            // we're done
        ADCSRA =
            fv.prescaler |
            ADCSRA_AUTO_TRIGGER_DISABLE |
            ADCSRA_IRQ_DISABLE |
            ADCSRA_CONVERT_ENABLE;
    }
}
