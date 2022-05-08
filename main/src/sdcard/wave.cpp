/**
 * @brief Read WAV audio files
 * 
 * Supports WAV files in 8-bit mono PCM.  Use SoX to transcode sound files to this format.
 *
 * Implementation details:
 *   Wave is a two level Type-Length-Value format.  Details can be found at
 *     http://soundfile.sapp.org/doc/WaveFormat/
 *   Hex file views
 *     http://frhed.sourceforge.net/en/
 *   Samples can be downloaded from the Univ of Iowa Electronic Music Studios
 *     http://theremin.music.uiowa.edu/index.html
 * 
 * © Copyright 2014, 2019, 2022, Coert Vonk
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
 * SPDX-FileCopyrightText: Copyright 2014,2019,2022 Coert Vonk
 **/

#include <Arduino.h>
#include <stdint.h>
#include <limits.h>

#include "../../config.h"
#include "../../sample_t.h"
#include "wave.h"

struct wave_hdr_t {
	char     id[4];
	uint32_t len;
} PACK8;

struct wave_chunk_t {
	wave_hdr_t hdr;
	char       fmt[4];
} PACK8;

struct wave_fmtvalue_t {
	uint16_t audio_format;
	uint16_t num_of_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample; // maybe followed by extra parameters
} PACK8;

typedef uint8_t dataValue_t;

typedef enum idType_t {
	IDTYPE_TIFF,
	IDTYPE_WAVE,
	IDTYPE_FMT,
	IDTYPE_DATA,
	IDTYPE_COUNT
} idType_t;

static char const _ids[IDTYPE_COUNT][4] = {
	{'R', 'I', 'F', 'F'},
	{'W', 'A', 'V', 'E'},
	{'f', 'm', 't', ' '},
	{'d', 'a', 't', 'a'}
};

/**
 * @brief Read a specified number of bytes from file.
 * 
 * @param f              File to read from [in]
 * @param len            Number of bytes to read [in]
 * @param offset         Offset to add to each byte [in]
 * @param data           Data read [out]
 * @return uint_least8_t Returns number of of bytes read
 */
static uint_least8_t
_read_bytes(File &f, uint16_t const len, int16_t const offset, char * const data)
{
	char * buf = data;

	for (uint16_t ii = 0; ii < len; ii++) {
		int const d = f.read();
		if (d < 0) {
			return 1;
		}
		if (buf) {
			*(buf++) = d + offset;
		}
	}
	return 0;
}

/**
 * @brief Read WAV header.
 * 
 * @param f              file to read from [in]
 * @param sample_cnt_p   total number of samples in file [out]
 * @return uint_least8_t returns 0 if successful
 */
uint_least8_t
wave_read_hdr(File &f, sample_cnt_t * const sample_cnt_p)
{
	// main chunk
	wave_chunk_t chunk;
	if (_read_bytes(f, sizeof(chunk), 0, (char *) &chunk) != 0 ||
		memcmp(&chunk.hdr.id, _ids[ IDTYPE_TIFF ], sizeof(chunk.hdr.id)) != 0 ||
		memcmp(&chunk.fmt, _ids[ IDTYPE_WAVE ], sizeof(chunk.fmt)) != 0) {

		return 1;
	}
	
	// sub chunk "fmt "
	wave_hdr_t hdr;
	wave_fmtvalue_t fmtValue;
	if (_read_bytes(f, sizeof(hdr), 0, (char *)&hdr) ||
		memcmp(&hdr.id, _ids[IDTYPE_FMT], sizeof(hdr.id)) != 0) {
		return 2;
	}
	if (hdr.len < sizeof(fmtValue) ||
		_read_bytes(f, sizeof(fmtValue), 0, (char *)&fmtValue) != 0 ||
		_read_bytes(f, hdr.len - sizeof(fmtValue), 0, NULL) != 0) {
		return 3;
	}
	if (fmtValue.audio_format != 1 ||     // PCM
		fmtValue.num_of_channels != 1 ||  // mono
		fmtValue.bits_per_sample != 8 ||  // 8 bits/sample
		fmtValue.sample_rate != CONFIG_MIDIMIKE_SAMPLE_RATE) {
		return 4;
	}
	
	// sub chunk "data"
	if (_read_bytes(f, sizeof(hdr), 0, (char *) &hdr) != 0 ||
		memcmp(&hdr.id, _ids[IDTYPE_DATA], sizeof(hdr.id)) != 0) {

		return 5;
	}

	*sample_cnt_p = hdr.len;  // leave the rest of the file to wave_read_samples()		
	return 0;
}

/**
 * @brief remove bias by changing values from [0..255] to [-128..127]
 * 
 * @param f              returns 0 if successful
 * @param sample_cnt     number of samples to [in]
 * @param samples        samples read [out]
 * @return uint_least8_t returns 0 if successful
 */
uint_least8_t
wave_read_samples(File &f, sample_cnt_t const sample_cnt, samples_t samples)
{
	if (_read_bytes(f, sample_cnt, SCHAR_MIN, (char *)samples) != 0) {
		return 1;
	}
	return 0;
}
