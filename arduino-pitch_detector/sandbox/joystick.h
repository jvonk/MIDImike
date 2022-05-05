/**
 * @brief Analog input driver for joystick on Adafruit 1.8" TFT shield
 * @file  joystick.h
 * $Id$
 * see https://coertvonk.com/category/sw/arduino/pitch-detector
 *
 * (c) Copyright 2015 by Coert Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 **/

#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "config.h"

enum class JoystickState {
    NEUTRAL = 0,
    LEFT,
    DOWN,
    SELECT,
    RIGHT,
    UP
};

class Joystick {

public:

    static void
        begin( uint8_t const port );

    static void
        update( void );

    static JoystickState
        get( void );

};
