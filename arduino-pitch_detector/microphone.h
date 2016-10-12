/**
* @brief Asynchronous microphone driver
* @file  microphone.h
* Platform: Arduino UNO R3 using Arduino IDE
* Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
*
* GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
* (c) Copyright 2015, Coert Vonk
* All rights reserved.  Use of copyright notice does not imply publication.
* All text above must be included in any redistribution
**/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "sample_t.h"

namespace Microphone {

    void
        begin( uint8_t const port );  // 0 for A0

    // Done with samples
    //   Application signals that it no longer needs access to the samples.
    //   This driver will reuse the "samples" buffer and start collecting
    //   new samples.  Refer to top of file for details
    samples_t const     // returns pointer to where new samples will be stored if successful
        update( void );

    samples_t const     // returns pointer to array of data samples, NULL on failure
        getSamples( amplitude_t * const amplitudePtr );

};
