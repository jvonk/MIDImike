#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "../../sample_t.h"

namespace Microphone {

    void
        begin( uint8_t const port );  // 0 for A0

    // Done with samples
    //   Application signals that it no longer needs access to the samples.
    //   This driver will reuse the "samples" buffer and start collecting
    //   new samples.  Refer to top of file for details
    void
        update( void );

    samples_t     // returns pointer to array of data samples, NULL on failure
        getSamples( amplitude_t * const amplitudePtr );

};
