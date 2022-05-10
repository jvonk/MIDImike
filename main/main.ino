
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
#include <SD.h>
#include <SPI.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

#include "config.h"
#include "sample_t.h"
#include "src/pitch/pitch.h"
#include "src/sdcard/sddir.h"
#include "src/sdcard/wave.h"
#include "src/pitch/frequency.h"
#include "src/segment/segment.h"
#include "src/segment/segmentbuf.h"
#include "src/microphone/microphone.h"
#include "src/display/staff.h"
#include "src/display/pianoroll.h"
#include "src/midi/midiserial.h"
#include "src/midi/midifile.h"

namespace {

    // Arduino Digital I/O that connect to the 1.8" TFT / SD Card
    //
    //  Arduino 5V -----------------wire to--- VCC *and* LITE on TFT/SD breakout
    //  Arduino GND ----------------wire to--- GND on TFT/SD breakout
    typedef enum digialIoPins_t {
        SPI_RST = 9,          // ---wire-to--- RESET on TFT/SD breakout    (Reset)
        SPI_DC = 8,           // ---wire-to--- D/C on TFT/SD breakout      (SPI Data/Command)
        SPI_SD_CS = 4,        // ---wire-to--- CARD_CS on TFT/SD breakout  (SPI SD Card Chip Select)
        SPI_TFT_CS = 10,      // ---wire-to--- TFT_CS on TFT/SD breakout   (SPI TFT Chip Select)
        SPI_MOSI = 11,        // ---wire-to--- MOSI on TFT/SD breakout     (SPI Master out, slave in)
        SPI_CLK = 13,         // ---wire-to--- SCK  TFT/SD on breakout     (SPI Clock)
        SPI_MISO = 12,        // ---wire-to--- MISO TFT/SD on breakout     (SPI Master in, slave out)
        BUTTON_IN = 5         // ---wire-to--- Pushbutton to Vcc, and with 1 MOhm to GND
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
    } file_scope_variables_t;

    static file_scope_variables_t _;
} // name space


    /**********************************************
     * Calculate frequency and note pitch from file
     **********************************************
     * 1. read sample from uSD card
     * 2. calculate the frequency
     * 3. match the frequency to a note
     */

uint_least8_t                 // always returns 0
calc_note(File & f,           // file to read samples from
          char * instrument)  // name of instrument (for CSV monitor only)
{
    //ASSERT((Debug::getMemFree() > CONFIG_MIDIMIKE_WINDOW_SIZE + 65));  // very rough estimate
    sample_t samples[CONFIG_MIDIMIKE_WINDOW_SIZE];

    amplitude_t amplitude;

    char noteName[8 + 1 + 3 + 1];
    if (wavewave_read_samples(f, noteName, samples, &amplitude) == 0) {

        // find frequency from samples
        float freq = frequency_calculate(samples);

        // find note from frequency
        Pitch pitch(freq);

        switch(DST) {
            case DST_STAFF:
                staff_draw_note(pitch);
                break;

            case DST_PIANOROLL:
                // call twice to meet meet the minimum note duration
                _.segment->put(millis(), pitch.get_segment(), amplitude, _.segmentBuf);
                _.segment->put(millis(), pitch.get_segment(), amplitude, _.segmentBuf);
                pianoroll_draw(_.segment->get_last_offset(), _.segmentBuf);
                break;

            case DST_SERIAL:
                Pitch pitch_in(noteName);
                pitch.write_serial(instrument, pitch_in, freq);
                break;
        }
    }
    return 0;
}


    /************
     * Initialize
     ************/

void
setup()
{
    Serial.begin(CONFIG_MIDIMIKE_SERIAL_RATE);

    if (SRC == SRC_FILE) {
        if (sddir_init(SPI_SD_CS) != 0) {
            Serial.println("No SD Card");  // is the SD card inserted and formatted?
        }
    }

    switch(DST) {

        case DST_STAFF:
            staff_init(SPI_TFT_CS, SPI_DC, SPI_RST);
            break;

        case DST_PIANOROLL:
            _.segment = new Segment();
            _.segmentBuf = new SegmentBuf();
            pianoroll_init(SPI_TFT_CS, SPI_DC, SPI_RST);
            if (0) {
                if (midifile_init(SPI_SD_CS) != 0) {
                    Serial.println("No SD Card");  // is the SD card inserted and formatted?
                }
            }
            pinMode(BUTTON_IN, INPUT_PULLUP);
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
    switch(SRC) {

        case SRC_MICR: {

            // ASSERT((Debug::getMemFree() > CONFIG_MIDIMIKE_WINDOW_SIZE + 60));  // very rough estimate

            // get samples from microphone, samples will be dynamically allocated on first invocation
            amplitude_t amplitude;
            samples_t samples = microphone_get_samples(&amplitude);

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
            Pitch pitch(freq);

            switch(DST) {
                case DST_STAFF:
                    staff_draw_note(pitch);  // show note on TFT display
                    break;
                case DST_PIANOROLL:
                    _.segment->put(millis(), pitch.get_segment(), amplitude, _.segmentBuf);
                    pianoroll_draw(_.segment->get_last_offset(), _.segmentBuf);

                    if (USB_MIDI && digitalRead(BUTTON_IN) == 0) {
                        midiserial_send_notes(_.segmentBuf);
                        pianoroll_clear();
                    }
                    if (0) {
                        if (midifile_write(_.segmentBuf, "arduino.mid") != 0) {
                            Serial.println("midifile_write is mad");
                        }
                    }
                    break;
                case DST_SERIAL:
                    Pitch pitch_in(NOTENR_C, 0);
                    pitch.write_serial("microphone", pitch_in, freq);
                    break;

            } // switch(DST)
            break;
        }

        case SRC_FILE: {

            if (DST == DST_SERIAL) {
                Pitch::write_serial_hdr();
            }

            // for each file at sample rate, call `calc_note()`
            char dir[13] = "/notes/\012345"; 
            utoa(CONFIG_MIDIMIKE_SAMPLE_RATE, &dir[7], 10);
            sddir_for_each_file(dir, calc_note);
            break;
        }
    } // switch(SRC)
}
