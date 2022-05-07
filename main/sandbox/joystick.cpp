/**
 * @brief Analog input driver for joystick on Adafruit 1.8" TFT shield
 * @file  joystick.cpp
 * $Id$
 * see https://coertvonk.com/category/sw/arduino/pitch-detector
 *
 * (c)Copyright 2015 by Coert Vonk
 * All rights reserved.Use of copyright notice does not imply publication.
 *
 * Implementation details:
 *
 *   First read the value for the joystick (on TFT shield)
 *   Read twice.  The first values is garbage.  Probably due to the high impedance output of the voltage
 *   divider taking to long to charge the S/H capacitor.  Data sheet says <=10kOhm, but this 1kOhm still
 *   seems to high.  See http://forum.arduino.cc/index.php?topic=69675.0
 *
 * Status:
 *  
 *   Doesn't play well with microphone.cpp.  The joystick resistors seems to cause the microphone input
 *   not to work when joystick is in neutral position.  NOT USING THIS IN PROJECT.
 **/

#include <Arduino.h>
#include <stdint.h>
#include <limits.h>

#include "config.h"
#include "debug.h"
#include "adc_t.h"
#include "sample_t.h"
#include "joystick.h"


/******
* local
*******/

namespace {
	uint8_t _port;
	uint8_t _value;
	uint8_t _prescaler;
}

void
Joystick::begin( uint8_t const port )
{
	_port = port;

	// use same sample rate as for microphone input (ADCSRA_PRESCALER setting
	_prescaler = 0;
	for ( uint32_t d = 16e6 / 13; CONFIG_MIDIMIKE_SAMPLE_RATE < d; d /= 2 ) {
		_prescaler++;
	}
}


void
Joystick::update( void )
{
	ADCSRB =
		ADCSRB_MULTIPLEXER_ENABLE;

	ADMUX =
		ADMUX_REFERENCE_EXT |
		ADMUX_LEFT_ALIGN |
		(ADMUX_INPUT_MASK & _port);

	for ( uint_least8_t ii = 0; ii < 2; ii++ ) {
		ADCSRA =
			_prescaler |
			ADCSRA_AUTO_TRIGGER_DISABLE |
			ADCSRA_IRQ_DISABLE |
			ADCSRA_CONVERT_ENABLE |
			ADCSRA_CONVERT_START;

		while ( ADCSRA & ADCSRA_CONVERT_START ) {
			/* spin cpu */
		}
		_value = ADCH;
	}
}


JoystickState
Joystick::get( void )
{
	// voltage divider, see https://learn.adafruit.com/1-8-tft-display/reading-the-joystick
	uint8_t const left = UCHAR_MAX *  22e0 / (1e3 + 22e0);  //   5
	uint8_t const down = UCHAR_MAX * 220e0 / (1e3 + 220e0);  //  45
	uint8_t const select = UCHAR_MAX * 470e0 / (1e3 + 470e0);  //  81
	uint8_t const right = UCHAR_MAX *   1e3 / (1e3 + 1e3);  // 127
	uint8_t const up = UCHAR_MAX *  10e3 / (1e3 + 10e3);  // 232
	uint8_t const neutral = UCHAR_MAX;                          // 255

	return _value < (left / 2 + down / 2) ? JoystickState::LEFT :  //  24
		   _value < (down / 2 + select / 2) ? JoystickState::DOWN :  //  62
		   _value < (select / 2 + right / 2) ? JoystickState::SELECT :  // 103
		   _value < (right / 2 + up / 2) ? JoystickState::RIGHT :  // 178
		   _value < (up / 2 + neutral / 2) ? JoystickState::UP :  // 242
		   JoystickState::NEUTRAL;
}