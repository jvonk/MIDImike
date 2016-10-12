/**
 * @brief Pitch Class, types
 * @file  pitch_t.h
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#pragma once

enum class noteNr_t {
    C = 0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B, COUNT
};

typedef uint_least8_t  octaveNr_t;

