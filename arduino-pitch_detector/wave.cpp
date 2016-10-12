/**
 * @brief Read WAV audio files
 * @file wave.cpp
 * $Id: wave.cpp 336 2015-03-18 20:11:03Z cvonk $
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
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
 **/

#include <Arduino.h>
#include <stdint.h>
#include <limits.h>
#include "config.h"
#include "sample_t.h"
#include "wave.h"

namespace {

	/************
	 * Local data
	 ************/

	// main chunk

	struct hdr_t {
		char      id[4];
		uint32_t  len;
	} PACK8;

	struct chunk_t {
		hdr_t     hdr;
		char      fmt[4];
	} PACK8;

	// sub chunk "fmt "

	struct fmtValue_t {
		uint16_t  audioFormat;
		uint16_t  numChannels;
		uint32_t  sampleRate;
		uint32_t  byteRate;
		uint16_t  blockAlign;
		uint16_t  bitsPerSample; // maybe followed by extra parameters
	} PACK8;

	struct fmt_t {
		hdr_t      hdr;
		fmtValue_t value;
	} PACK8;

	// sub chunk "data"

	typedef uint8_t dataValue_t;

	struct data_t {
		hdr_t       hdr;
		dataValue_t value[0];
	} PACK8;

	// identifiers

	enum idType_t {
		riff,
		wave,
		fmt,
		data,
		COUNT  // terminator
	};

	char const _ids[static_cast<int>(idType_t::COUNT)][4] = {
		{'R', 'I', 'F', 'F'},
		{'W', 'A', 'V', 'E'},
		{'f', 'm', 't', ' '},
		{'d', 'a', 't', 'a'}
	};


	/*****************
	 * Local functions
	 *****************/

	uint_least8_t const
	_readBytes( File &         f,       // in: file to read from
	 	        uint16_t const len,     // in: number of bytes to read
				int16_t const  offset,  // in: offset to add to each byte
				char * const   data )   // out: data read
	{
		char * buf = data;

		for ( uint16_t ii = 0; ii < len; ii++ ) {
			int const d = f.read();
			if ( d < 0 ) {
				return 1;
			}
			if ( buf ) {
				*(buf++) = d + offset;
			}
		}
		return 0;
	}

}  // name space


	/************************
	 * Read/parse wave header
	 ************************/

uint_least8_t const                                  // returns 0 if successful
Wave::readHeader( File &               f,            // file to read from [in]
				  sampleCnt_t * const  pSampleCnt )  // total number of samples in file [out]
{
		// main chunk
	{
		::chunk_t chunk;
		if (_readBytes(f, sizeof(chunk), 0, (char *)&chunk) != 0 ||
			memcmp(&chunk.hdr.id, _ids[ idType_t::riff ], sizeof(chunk.hdr.id)) != 0 ||
			memcmp(&chunk.fmt, _ids[ idType_t::wave ], sizeof(chunk.fmt)) != 0 ) {

			return 1;
		}
	}
	
		// sub chunk "fmt "
	{
		::hdr_t hdr;
		::fmtValue_t fmtValue;
		if (_readBytes(f, sizeof(hdr), 0, (char *)&hdr) ||
			memcmp(&hdr.id, _ids[idType_t::fmt], sizeof(hdr.id)) != 0) {

			return 2;
		}
		if (hdr.len < sizeof(fmtValue) ||
			_readBytes(f, sizeof(fmtValue), 0, (char *)&fmtValue) != 0 ||
			_readBytes(f, hdr.len - sizeof(fmtValue), 0, NULL) != 0) {

			return 3;
		}

		if (fmtValue.audioFormat != 1 ||                    // PCM
			fmtValue.numChannels != 1 ||                    // mono
			fmtValue.bitsPerSample != 8 ||                  // 8 bits/sample
			fmtValue.sampleRate != Config::SAMPLE_RATE ) {  // sample rate
			return 4;
		}
	}
	
		// sub chunk "data"
	{
		::hdr_t hdr;
		if (_readBytes(f, sizeof(hdr), 0, (char *)&hdr) != 0 ||
			memcmp(&hdr.id, _ids[idType_t::data], sizeof(hdr.id)) != 0) {

			return 5;
		}
		*pSampleCnt = hdr.len;
	}
		// leave the rest of the file to Wave::readSamples()
	return 0;
}


	/**************
	 * Read samples
	 **************/

uint_least8_t const                                 // returns 0 if successful
Wave::readSamples( File &             f,            // file to read from [in]
				   sampleCnt_t const  nrOfSamples,  // number of samples to [in]
				   samples_t          samples )     // samples read [out]
{
		// remove bias by changing values from [0..255] to [-128..127]

	if (_readBytes(f, nrOfSamples, SCHAR_MIN, samples) != 0) {
		return 1;
	}
	return 0;
}
