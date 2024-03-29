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
#include "../../mapping.h"
#include "../../sample_t.h"
#include "../debug/debug.h"
#include "wave.h"

namespace {
	typedef struct wave_hdr_t {
		char     id[4];
		uint32_t len;
	} PACK8 wave_hdr_t;

	typedef struct wave_chunk_t {
		wave_hdr_t hdr;
		char       fmt[4];
	} PACK8 wave_chunk_t;

	typedef struct wave_fmtvalue_t {
		uint16_t audio_format;
		uint16_t num_of_channels;
		uint32_t sample_rate;
		uint32_t byte_rate;
		uint16_t block_align;
		uint16_t bits_per_sample; // maybe followed by extra parameters
	} PACK8 wave_fmtvalue_t;

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
}

    /********************************************
     * Read a specified number of bytes from file
     ********************************************/

static uint_least8_t               // returns the number of bytes read
_read_bytes(File & f,              // file to read from 
            uint16_t const len,    // number of bytes to read
            int16_t const offset,  // offset to add to each byte read
            char * const data)     // data read buffer
{
    //Serial.print("n="); Serial.println(len);
	char * buf = data;

	for (uint16_t ii = 0; ii < len; ii++) {
		int const d = f.read();
		if (d < 0) {
			return 1;
		}
		if (buf) {
			*(buf++) = d + offset;
            // uint8_t const u8 = d & 0xFF; 
            // debug_hex_dump(&u8, 0, 1); Serial.print(" u8=");
            // Serial.print(u8); Serial.print(" *buf="); Serial.println((int)*(buf-1)); 
		}
	}
    //Serial.println();

	return 0;
}

    /*****************
     * Read WAV header
     *****************/

static uint_least8_t                          // returns 0 if successful
_read_hdr(File & f,                           // file to read from
          sample_cnt_t * const sample_cnt_p)  // total number of samples in file
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

	*sample_cnt_p = hdr.len;  // leave the rest of the file to _read_samples()		
	return 0;
}

    /*************
     * Remove bias by changing values from [0..255] to [-128..127]
     *************/ 

static uint_least8_t                          // returns 0 if successful
_read_samples(File & f,                       // file to read from
              sample_cnt_t const sample_cnt,  // number samples to read
              samples_t samples)              // buffer to write samples to
{
	if (_read_bytes(f, sample_cnt, SCHAR_MIN, (char *)samples) != 0) {
		return 1;
	}
	return 0;
}

    /************************
     * Read samples from file
     ************************/

uint_least8_t                                      // returns 0 if successful
wave_read_samples(File &            f,             // file to read samples from [in]
				  char * const      note_name,     // note name derived from file name [out]
                  size_t            note_name_len, // note name max length (including terminating '\0')
				  sample_t * const  samples,       // samples read from file [out]
				  amplitude_t *     amplitude)     // signal amplitude [out]
{
    f.getName8(note_name, note_name_len);  // returns uppercase, except extension that is lowercase

	// remove file name extension
	char * const ext = strrchr(note_name, '.');
	if (!ext || strncmp(ext, ".wav", 4) != 0) {  // 2BD should be case insensitive
		return 1;
	}
	*ext = '\0';
	if (note_name[1] == 'B') {
		note_name[1] = 'b';
	}
    //Serial.println(note_name);

	sample_cnt_t nrOfSamplesInFile;

	if (_read_hdr(f, &nrOfSamplesInFile) != 0 ||
		_read_samples(f, CONFIG_MIDIMIKE_SAMPLE_RATE * CONFIG_MIDIMIKE_FILE_SEC2SKIP, NULL) != 0 ||
		_read_samples(f, CONFIG_MIDIMIKE_WINDOW_SIZE, samples) != 0) {

		return 2;
	}

	// determine peak-to-peak value
	sample_t min = SCHAR_MAX;
	sample_t max = SCHAR_MIN;
	for (sample_cnt_t ii = 0; ii < CONFIG_MIDIMIKE_WINDOW_SIZE; ii++) {
		sample_t const s = samples[ii];
		if (s < min) {
			min = s;
		}
		if (s > max) {
			max = s;
		}
	}

	*amplitude = (int16_t)max - min; // top-top
	return 0;
}
