/**
 * @brief Converts between Host byte order and MIDI byte order (big endian)
 * @file  endian.h
 * Platform: Arduino UNO R3 using Arduino IDE
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015, Coert Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

#pragma once

#include <Arduino.h>
#include <stdint.h>


#if BYTE_ORDER == BIG_ENDIAN
# define htom16(x) (x)
# define htom32(x) (x)
# define mtoh16(x) (x)
# define mtoh32(x) (x)
#elif BYTE_ORDER == LITTLE_ENDIAN
# define htom16(x) __bswap_16( x );
# define htom32(x) __bswap_32( x );
# define mtoh16(x) __bswap_16( x );
# define mtoh32(x) __bswap_32( x );
#else
# error "BYTE_ORDER not supported"
#endif

