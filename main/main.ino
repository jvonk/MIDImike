
/**
 * @brief Pitch Detector for Monophonic Musical Instruments using Arduino
 *
 *                            /----------------------------\
 *                            |          Arduino           |
 *                            |      Pitch Detector        |
 *                            |            for             |
 *                            |     Music Instruments      |
 *                            \----------------------------/
 *
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: https://coertvonk.com/category/sw/arduino/pitch-detector
 * 
 * © Copyright 2015-2016,2022 Johan Vonk
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
 * SPDX-FileCopyrightText: Copyright 2015-2016,2022 Johan Vonk
 **/

// The Arduino build environment requires all compilation units to be listed as #include's
#include <Arduino.h>
#include <stdint.h>
#include <limits.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

#include "config.h"
#include "sample_t.h"
#include "src/debug/debug.h"
#include "src/pitch/pitch.h"
#include "src/sdcard/sddir.h"
#include "src/sdcard/wave.h"
#include "src/sdcard/calcnote.h"
#include "src/pitch/frequency.h"
#include "src/segment/segment.h"
#include "src/segment/segmentbuf.h"
#include "src/microphone/microphone.h"
#include "src/display/staff.h"
#include "src/display/pianoroll.h"
#include "src/midi/midiserial.h"

namespace {

    // Arduino Digital I/O that connect to the 1.8" TFT / SD Card
    //
    //  Arduino 5V -----------------wire to--- VCC *and* LITE on TFT/SD breakout
    //  Arduino GND ----------------wire to--- GND on TFT/SD breakout
    typedef enum digialIoPins_t {
        SHIFT_BCD1 = 2,       // ---wire-to--- SW2 BCD value 1 to GND
        SHIFT_BCD2 = 3,       // ---wire-to--- SW2 BCD value 2 to GND
        SPI_SD_CS = 4,        // ---wire-to--- CARD_CS on TFT/SD breakout  (SPI SD Card Chip Select)
        SHIFT_BCD4 = 5,       // ---wire-to--- SW2 BCD value 4 to GND
        SHIFT_BCD8 = 6,       // ---wire-to--- SW2 BCD value 8 to GND
        //REPLAY_BUTTON = 7,  // ---wire-to--- Pushbutton to GND
        CLIP_LED = 7,         // ---wire-to--- LED and 330 Ohm to GND
        SPI_TFT_DC = 8,       // ---wire-to--- TFT_DC on TFT/SD breakout   (SPI TFT Data/!Command)
        SPI_RST = 9,          // ---wire-to--- RESET on TFT/SD breakout    (Reset)
        SPI_TFT_CS = 10,      // ---wire-to--- TFT_CS on TFT/SD breakout   (SPI TFT Chip Select)
        SPI_MOSI = 11,        // ---wire-to--- MOSI on TFT/SD breakout     (SPI Master out, slave in)
        SPI_MISO = 12,        // ---wire-to--- MISO TFT/SD on breakout     (SPI Master in, slave out)
        SPI_CLK = 13          // ---wire-to--- SCK  TFT/SD on breakout     (SPI Clock)
    } digialIoPins_t;

    // Arduino Analog input connecting to Microphone Amp
    //
    //  Arduino 3.3V -----------------wire-to--- AREF on Arduino (don't forget this!)
    //  Arduino 5V -------------------wire-to--- Vdd on Microphone Amp breakout
    //  Arduino GND ------------------wire-to--- GND on Microphone Amp breakout
    typedef enum analogInPins_t { // --n.c.----- GAIN on Microphone Amp breakout (n.c.==not connected)
        MICROPHONE_IN = 0,        // -wire-to--- Out on Microphone Amp breakout
        JOYSTICK_IN = 3           // -wire-to--- on TFT/SD/joystick shield (NOT NEEDED, unused)
    } analogInPins_t;             // --n.c.----- AR on Microphone Amp breakout

    typedef struct file_scope_variables_t {
        Segment *     segment;
        SegmentBuf *  segmentBuf;
        bool          sdcard_ok;
    } file_scope_variables_t;

    static file_scope_variables_t _;
}

#if 0
static void
print_addr(void * p) 
{
    int ptr = (int) p;
    unsigned char tmp;
    char string[]="0123456789ABCDEF";

    tmp = *(1+ (unsigned char*) &ptr); // MSB
    putchar( string[tmp >> 4] );
    putchar( string[tmp & 0xF] );

    tmp = *(0+ (unsigned char*) &ptr); // LSB
    putchar( string[tmp >> 4] );
    putchar( string[tmp & 0xF] );    
}
#endif


    /************
     * Initialize
     ************/

void
setup()
{
    Serial.begin(CONFIG_MIDIMIKE_SERIAL_RATE);

    if (DST == DST_TEXT && USB == USB_SERIAL) {
        while (!Serial) {
            yield();  // wait for serial port to connect
        };
    }
    Serial.println("Welcome to MIDImike");


    if (SRC == SRC_FILE) {
        _.sdcard_ok = sddir_init(SPI_SD_CS) == 0;
        if (!_.sdcard_ok && USB == USB_SERIAL) {
            Serial.println("SD err");  // card inserted and formatted FAT/FAT32?
        }
    }

    pinMode(SHIFT_BCD1, INPUT_PULLUP);  // 
    pinMode(SHIFT_BCD2, INPUT_PULLUP);
    pinMode(SHIFT_BCD4, INPUT_PULLUP);
    pinMode(SHIFT_BCD8, INPUT_PULLUP);
    pinMode(CLIP_LED, OUTPUT);

    switch (DST) {
        case DST_STAFF:
            staff_init(SPI_TFT_CS, SPI_TFT_DC, SPI_RST);
            break;
        case DST_PIANOROLL:
            _.segment = new Segment();
            _.segmentBuf = new SegmentBuf();
            pianoroll_init(SPI_TFT_CS, SPI_TFT_DC, SPI_RST);
            //pinMode(REPLAY_BUTTON, INPUT_PULLUP);
            break;
        case DST_TEXT:
            if (SRC == SRC_FILE) {
                calcnote_write_serial_hdr();
                // for each file at sample rate, call `calc_note()`
                char dirname[13] = {}; 
                strcpy(dirname,"/notes/");
                utoa(CONFIG_MIDIMIKE_SAMPLE_RATE, dirname + strlen(dirname), 10);

                //Serial.print("main free="); Serial.println(debug_freeMemory());
                sddir_for_each_file_in_dir(dirname, calcnote_from_file);
            }
            break;
    }

    if (SRC == SRC_MICR) {
        microphone_begin(MICROPHONE_IN);
    }
}

    /***********
     * Main loop
     ***********/

void 
loop()
{
    uint8_t const shift = 1 * digitalRead(SHIFT_BCD1) + 2 * digitalRead(SHIFT_BCD2) +
                          4 * digitalRead(SHIFT_BCD4) + 8 * digitalRead(SHIFT_BCD8);
    (void)shift;  // 2BD use this!
 
    switch(SRC) {

        case SRC_MICR: {
            // ASSERT((debug_getMemFree() > CONFIG_MIDIMIKE_WINDOW_SIZE + 60));  // very rough estimate

            // get samples from microphone, samples will be dynamically allocated on first invocation
            amplitude_t amplitude;
            bool clipping;
            samples_t samples = microphone_get_samples(&amplitude, &clipping);
            digitalWrite(CLIP_LED, clipping);

            // find frequency from samples
            float freq = frequency_calculate(samples);

            // no longer need the samples => reuse it and start gathering samples for next time around
            microphone_start();  // async

            if (0) {  // ignore notes under audible threshold (2BD: already done in getSamples())
                if (amplitude < CONFIG_MIDIMIKE_AUDIBLE_THRESHOLD) {
                    freq = 0;
                }
            }

            // find corresponding note
            Pitch pitch_measured(freq);

            switch(DST) {
                case DST_STAFF:
                    staff_draw_note(pitch_measured);  // show note on TFT display
                    break;
                case DST_PIANOROLL:
                    _.segment->put(millis(), pitch_measured.get_segment(), amplitude, _.segmentBuf);
                    pianoroll_draw(_.segment->get_last_offset(), _.segmentBuf);
#if 0
                    if ((USB == USB_MIDI) && digitalRead(REPLAY_BUTTON) == 0) {
                        midiserial_send_notes(_.segmentBuf);
                        pianoroll_clear();
                    }
#endif
                    break;
                case DST_TEXT:
                    Pitch pitch_in(NOTENR_C, 0);
                    calcnote_write_serial("microphone", pitch_in, pitch_measured, freq);
                    break;

            } // switch(DST)
            break;
        }

        case SRC_FILE: {
            yield();
            break;

        }
    } // switch(SRC)
}
