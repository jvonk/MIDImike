#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "sample_t.h"

namespace Frequency {

	frequency_t                                 // returns frequency found, 0 when not found
		calculate( samples_t const  samples );  // pointer to signed 8-bit data samples [in]

};

