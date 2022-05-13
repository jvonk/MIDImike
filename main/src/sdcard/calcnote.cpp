#include <Arduino.h>
#include <stdint.h>
#include "../../config.h"
#include "../../sample_t.h"
#include "../../mapping.h"
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
        Serial.println(F(""));
        Serial.print(F("instrument,samplefreq,buffsize,noteoctave,freq,=>,"));
        Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE);
        Serial.print(F(","));
        Serial.println(CONFIG_MIDIMIKE_WINDOW_SIZE);
    }
}

    /***********************
     * calcnote_write_serial
     ***********************/

void
calcnote_write_serial(char const * const instrument,  // instrument name
                      Pitch & pitch_in,               // pitch read from file
                      Pitch & pitch_measured,         // measured pitch
                      frequency_t freq)               // measured frequency
{
    if (USB == USB_SERIAL) {
        Serial.print(instrument); Serial.print(",");
        Serial.print(CONFIG_MIDIMIKE_SAMPLE_RATE); Serial.print(F(","));
        Serial.print(CONFIG_MIDIMIKE_WINDOW_SIZE); Serial.print(F(","));

        // the value it shoud be (do not show for microphone input)
        if (pitch_in.get_frequency()) {
            Serial.print(pitch_in.get_shortname());
            Serial.print(pitch_in.get_octavenr());
            Serial.print(F(","));
            Serial.print(pitch_in.get_frequency());
        }

        // value measured
        if (pitch_measured.get_segment() > 0) {
            Serial.print(F(",=>,"));
            Serial.print(freq);
            Serial.print(F(","));
            Serial.print(pitch_measured.get_shortname());
            Serial.print(pitch_measured.get_octavenr());
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
    if (USB == USB_SERIAL && DST == DST_TEXT) {

        amplitude_t amplitude;
        sample_t samples[CONFIG_MIDIMIKE_WINDOW_SIZE];

        char note_name[8 + 1 + 3 + 1];
        if (wave_read_samples(f, note_name, ARRAY_SIZE(note_name), samples, &amplitude) == 0) {

            // find frequency from samples
            float freq = frequency_calculate(samples);

            // find note from frequency
            Pitch pitch_measured(freq);

            // calculate pitch of note from file (based on file name)
            Pitch pitch_in(note_name);

            calcnote_write_serial(instrument, pitch_in, pitch_measured, freq);
        } else {
            Serial.println(F("wave_read_samples() err"));
        }
        return 0;
    }
    return 1;
}
