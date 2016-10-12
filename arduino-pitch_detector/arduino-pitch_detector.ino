/**
 * @brief Pitch Detector for Monophonic Musical Instruments using Arduino
 * @file  arduino-pitch_detector.ino
 *
 *                            /----------------------------\
 *                            |          Arduino           |
 *                            |      Pitch Detector        |
 *                            |            for             |
 *                            |     Music Instruments      |
 *                            \----------------------------/
 *
 * Platform: Arduino UNO R3 using Arduino IDE
 * Documentation: http://www.coertvonk.com/technology/embedded/arduino-pitch-detector-13252
 * Tested with: Arduino IDE 1.6.12, board package arduino avr 1.6.13, Arduino/Genuino UNO R3
 *
 * GNU GENERAL PUBLIC LICENSE Version 3, check the file LICENSE for more information
 * (c) Copyright 2015-2016, Johan Vonk
 * All rights reserved.  Use of copyright notice does not imply publication.
 * All text above must be included in any redistribution
 **/

// The Arduino build environment requires all compilation units to be listed as #include's
#include <stdint.h>
#include <limits.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_ST7735.h>  // if error, read "Toolchain" at above mentioned URL
#include <Adafruit_GFX.h>     // if error, read "Toolchain" at above mentioned URL

#include "config.h"
#include "debug.h"
#include "sample_t.h"
#include "pitch.h"
#include "sddir.h"
#include "wave.h"
#include "frequency.h"
#include "staff.h"
#include "segment.h"
#include "segmentbuf.h"
#include "pianoroll.h"
#include "microphone.h"
#include "midiserial.h"
#include "midifile.h"

namespace {

    /*****************
     * I/O assignments
     *****************/

    // Arduino Digital I/O that connect to the 1.8" TFT / SD Card
    //
    //  Arduino 5V -----------------wire to--- VCC *and* LITE on TFT/SD breakout
    //  Arduino GND ----------------wire to--- GND on TFT/SD breakout
    enum digialIoPins {       //
        SPI_RST = 9,          // ---wire-to--- RESET on TFT/SD breakout    (Reset)
        SPI_DC = 8,           // ---wire-to--- D/C on TFT/SD breakout      (SPI Data/Command)
        SPI_SD_CS = 4,        // ---wire-to--- CARD_CS on TFT/SD breakout  (SPI SD Card Chip Select)
        SPI_TFT_CS = 10,      // ---wire-to--- TFT_CS on TFT/SD breakout   (SPI TFT Chip Select)
        SPI_MOSI = 11,        // ---wire-to--- MOSI on TFT/SD breakout     (SPI Master out, slave in)
        SPI_CLK = 13,         // ---wire-to--- SCK  TFT/SD on breakout     (SPI Clock)
        SPI_MISO = 12,        // ---wire-to--- MISO TFT/SD on breakout     (SPI Master in, slave out)
        BUTTON_IN = 5         // ---wire-to--- Pushbutton to Vcc, and with 1 MOhm to GND
    };

    // Arduino Analog input connecting to Microphone Amp
    //
    //  Arduino 3.3V ---------------wire-to--- AREF on Arduino (don't forget this!)
    //  Arduino 5V -----------------wire-to--- Vdd on Microphone Amp breakout
    //  Arduino GND ----------------wire-to--- GND on Microphone Amp breakout
    enum analogInPins {       // ----n.c.----- GAIN on Microphone Amp breakout (n.c.==not connected)
        MICROPHONE_IN = 0,    // ---wire-to--- Out on Microphone Amp breakout
        JOYSTICK_IN = 3       // ---wire-to--- on TFT/SD/joystick shield (NOT NEEDED, unused)
    };                        // ----n.c.----- AR on Microphone Amp breakout


#if DST == DST_PIANOROLL
    struct mainvariables_t {
        Segment *     segment;
        SegmentBuf *  segmentBuf;
    };  // file scope variables
    static mainvariables_t mv;
#endif


    /************************
     * Read samples from file
     ************************/

#if SRC == SRC_FILE

    INLINE uint_least8_t const                       // return 0 if successful
    _readSamplesFromFile( File &        f,           // file to read samples from [in]
                          char * const  noteName,    // note name derived from file name [out]
                          char * const  samples,     // samples read from file [out]
                          amplitude_t * amplitude )  // signal amplitude [out]
    {
        strcpy(noteName, f.name());

        // remove file name extension
        char * const ext = strrchr( noteName, '.' );
        if ( !ext || strncmp( ext, ".WAV", 4 ) != 0 ) {
            return 1;
        }
        *ext = '\0';

        if (noteName[1] == 'B') {
            noteName[1] = 'b';
        }

        sampleCnt_t nrOfSamplesInFile;

        if ( Wave::readHeader( f, &nrOfSamplesInFile ) != 0 ||
            Wave::readSamples( f, Config::SAMPLE_RATE * Config::FILE_SEC2SKIP, NULL ) != 0 ||
            Wave::readSamples( f, Config::WINDOW_SIZE, samples ) != 0 ) {

            return 2;
        }

        // determine peak-to-peak value
        sample_t min = SCHAR_MAX;
        sample_t max = SCHAR_MIN;
        for ( sampleCnt_t ii = 0; ii < Config::WINDOW_SIZE; ii++ ) {
            sample_t const s = samples[ii];
            if ( s < min ) {
                min = s;
            }
            if ( s > max ) {
                max = s;
            }
        }
        *amplitude = (int16_t)max - min; // top-top

        SHOW_MEMORY_USAGE_ONLY(( Debug::showMemUsage() ));
        return 0;
    }


    /**********************************************
     * Calculate frequency and note pitch from file
     **********************************************
     * 1. read sample from uSD card
     * 2. calculate the frequency
     * 3. match the frequency to a note
     */

    uint_least8_t const                   // returns 0 when successful
    _calcNoteFromFile(File & f,           // file to read samples from
                      char * instrument ) // name of instrument (for CSV monitor only)
    {
        ASSERT(( Debug::getMemFree() > Config::WINDOW_SIZE + 65 ));  // very rough estimate
        char samples[Config::WINDOW_SIZE];

        // read samples from file

        amplitude_t amplitude;

        char noteName[8 + 1 + 3 + 1];
        if ( _readSamplesFromFile( f, noteName, samples, &amplitude ) == 0 ) {

            // find frequency from samples
            float freq = Frequency::calculate( samples );

            // find note from frequency
            Pitch pitch( freq );

# if DST == DST_STAFF

            // show note on TFT display
            Staff::showNote( pitch, amplitude );

# elif DST == DST_PIANOROLL

            // need it twice, otherwise it doesn't meet the minimum note duration
#if 0
			mv.segmentBuf->put( note.getPitch(), amplitude );
            mv.segmentBuf->put( note.getPitch(), amplitude );
            PianoRoll::show( mv.segment->getLastOffset(), mv.segmentBuf );
#endif
			mv.segment->put(millis(), pitch.getPitch(), amplitude, mv.segmentBuf);
			mv.segment->put(millis(), pitch.getPitch(), amplitude, mv.segmentBuf);
			PianoRoll::show(mv.segment->getLastOffset(), mv.segmentBuf);

# elif DST == DST_SERIAL

            // show note on Serial monitor
            Pitch pitchIn(noteName);
            pitch.serialOut( instrument, pitchIn, freq, amplitude );
# endif
        }
        SHOW_MEMORY_USAGE_ONLY( (Debug::showMemUsage()) );
        return 0;
    }
#endif

} // name space


    /************
     * Initialize
     ************/

void
setup()
{
    Serial.begin( Config::SERIAL_RATE );
    while ( !Serial ) {
        ; // wait until the serial port connects
    }
    //Serial.println( "setup()" );
#if SRC == SRC_FILE
    if (SdDir::begin(SPI_SD_CS) != 0) {
        Serial.println("No SD Card");  // uSD card inserted/formatted  ??
    }
#endif

#if DST == DST_STAFF

    Staff::begin( SPI_TFT_CS, SPI_DC, SPI_RST );
    //Midi::begin();

#elif DST == DST_PIANOROLL

    mv.segment = new Segment();
    mv.segmentBuf = new SegmentBuf();
    PianoRoll::begin( SPI_TFT_CS, SPI_DC, SPI_RST );

#if 0
    if ( MidiFile::begin( SPI_SD_CS ) != 0 ) {
        Serial.println( "No SD Card" );  // uSD card inserted/formatted  ??
    }
#endif

    pinMode( BUTTON_IN, INPUT_PULLUP );

#endif

#if SRC == SRC_MICR
    Microphone::begin( MICROPHONE_IN );
#endif
    // loop() never stops, so there is no need for corresponding end() methods
}


    /***********
     * Main loop
     ***********/

void 
loop()
{
#if SRC == SRC_MICR

    // 2BD show % error compared to note recognized, so it can be used as a tuner
    // 2BD apply note level segmentation.  See segment.cpp for suggestions

    ASSERT( (Debug::getMemFree() > Config::WINDOW_SIZE + 60) );  // rough estimate

    // get samples from microphone, samples will be dynamically allocated on first invocation

    amplitude_t amplitude;
    samples_t samples = Microphone::getSamples( &amplitude );

    // find frequency from samples
    float freq = Frequency::calculate( samples );

    // no longer need the samples, so reuse it and start gathering samples for next time around
    (void)Microphone::update();  // async

    // ignore notes under audible threshold (2BD: already done in getSamples())
    if ( amplitude < Config::AUDIBLE_THRESHOLD ) {
        freq = 0;
    }

    // find corresponding note
    Pitch pitch( freq );

# if DST == DST_STAFF

    // show note on TFT display
    Staff::showNote( pitch, amplitude );

# elif DST == DST_PIANOROLL

    mv.segment->put( millis(), pitch.getPitch(), amplitude, mv.segmentBuf );
    PianoRoll::show( mv.segment->getLastOffset(), mv.segmentBuf );

    // 2BD should clear the buffer if 64 seconds of silence,
    // or maybe just start playing the buffer over MIDI ..

    if ( USB_MIDI && digitalRead( BUTTON_IN ) == 0 ) {
        MidiSerial::send(mv.segmentBuf);
        PianoRoll::clear();
    }

#if 0
    if ( MidiFile::write( mv.segmentBuf, "arduino.mid") != 0 ) {
        Serial.println("MidiFile::write is mad");
    }
#endif

# elif DST == DST_SERIAL

    Pitch pitchIn( noteNr_t::C,0 );
    note.serialOut( "microphone", pitchIn, freq, amplitude );

# endif

    SHOW_MEMORY_USAGE_ONLY(( Debug::showMemUsage() ));
#endif

#if SRC == SRC_FILE
# if DST == DST_SERIAL
    Pitch::serialOutHeader();
# endif
    // for each file at sample rate, call _calcNoteFromFile()
    char dir[13] = "/notes/\012345";
    utoa( Config::SAMPLE_RATE, &dir[7], 10);
    //Serial.println( dir );
    SdDir::forEachFile( dir, _calcNoteFromFile );
#endif
}
