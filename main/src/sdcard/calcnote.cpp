#include <Arduino.h>
#include <stdint.h>
#include "../../config.h"
#include "../../sample_t.h"
#include "../pitch/pitch.h"
#include "../sdcard/sddir.h"
#include "../sdcard/wave.h"
#include "../pitch/frequency.h"
#include "../segment/segment.h"
#include "../segment/segmentbuf.h"
#include "../display/staff.h"
#include "../display/pianoroll.h"
#include "../debug/debug.h"

void
calcnote_write_serial_hdr(void)
{
    if (USB == USB_SERIAL) {
        Serial.println("");
        Serial.print("instrument samplefreq buffsize noteoctave freq => ");
        Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE);
        Serial.print(" ");
        Serial.println(CONFIG_MIDIMIKE_WINDOW_SIZE);
    }
}

    /***********************
     * calcnote_write_serial
     ***********************/

void
calcnote_write_serial(char const * const instrument,  // instrument name
                      Pitch & in_pitch,               // pitch read from file
                      Pitch & measured_pitch,         // measured pitch
                      frequency_t freq)               // measured frequency
{
    if (USB == USB_SERIAL) {
        Serial.print(instrument); Serial.print(" ");
        Serial.print(CONFIG_MIDIMIKE_SAMPLE_RATE); Serial.print(" ");
        Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE); Serial.print(" ");

        // the value it shoud be (do not show for microphone input)
        if (in_pitch.get_frequency()) {
            Serial.print(in_pitch.get_shortname());
            Serial.print(in_pitch.get_octavenr());
            if (strlen(in_pitch.get_shortname()) < 2) {
                Serial.print(" ");
            }
            Serial.print(" ");
            Serial.print(measured_pitch.get_frequency());
        }

        // value measured
        if (measured_pitch.get_segment() > 0) {
            Serial.print(" => ");
            Serial.print(freq);
            Serial.print(" ");
            Serial.print(measured_pitch.get_shortname());
            Serial.print(measured_pitch.get_octavenr());
            if (strlen(measured_pitch.get_shortname()) < 2) {
                Serial.print(" ");
            }
        }
        Serial.println();
    }
}

    /**********************************************
     * Calculate frequency and note pitch from file
     **********************************************
     * 1. read sample from uSD card
     * 2. calculate the frequency
     * 3. match the frequency to a note
     */

uint_least8_t                          // returns 0 if successful, otherwise returns 1
calcnote_from_file(File & f,           // file to read samples from
                   char * instrument)  // name of instrument (for CSV monitor only)
{
    //Serial.println(f.name());

    if (USB == USB_SERIAL && DST == DST_TEXT) {

        //
        // sorry doesn't work .. we run out of mem
        //

        //ASSERT((Debug::getMemFree() > CONFIG_MIDIMIKE_WINDOW_SIZE + 65));  // very rough estimate

        amplitude_t amplitude;
        sample_t samples[CONFIG_MIDIMIKE_WINDOW_SIZE];

        // Serial.print("calcnote_from_file() "); Serial.println(f.name());

        char noteName[8 + 1 + 3 + 1];
        if (wave_read_samples(f, noteName, samples, &amplitude) == 0) {

            // find frequency from samples
            float freq = frequency_calculate(samples);

            // find note from frequency
            Pitch pitch(freq);

            Pitch pitch_in(noteName);
            calcnote_write_serial(instrument, pitch_in, pitch, freq);
        } else {
            Serial.println("wave_read_samples() err");
        }
        return 0;
    }
    return 1;
}
