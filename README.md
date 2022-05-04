# arduino-pitch_detector  [![Build Status](https://travis-ci.org/johanvonk/Arduino_Pitch-Detector.svg?branch=master)](https://travis-ci.org/johanvonk/arduino-pitch_detector)
## Pitch Detection on Arduino using Autocorrelation

While playing my clarinet, I realized that it would be fun to hear other instruments playing alongside me. Instruments like guitar, piano or even a choir. It would also be nice if the melodies could be transcribed on paper. All existing solutions to these problems require a bulky computer or a cell phone. I realized that creating this compact device would combine my interest for music with my passion for engineering and math.

![Image](media/icon.jpg)

This project creates a small, affordable and accurate device that listens to a musical instrument and recognizes the notes played. These notes can then be sent to a synthesizer in the common MIDI format. This allows musician to hear other instruments playing alongside with them, and allows them store their compositions.
The implementation is in C++ and uses an Arduino UNO, breadboard, microphone and optional display.  It displays the music as a piano roll and sends it to an external synthesizer.

The implementation is in C++ and uses an Arduino, breadboard, microphone and display.  It changes the sound wave to an electrical signal; uses autocorrelation to find frequency played; display frequency as note on screen while sending to a MIDI synthesizer.

2018: Tested with: Arduino/Genuino UNO R3, Arduino AVR Boards 1.6.14, Arduino IDE 1.6.12
2022: Tested with: Arduino/Genuino UNO R3, Arduino AVR Boards 1.8.5, Adafruit BusIO 1.11.5, Adafruit ST7735 and ST7789 Library 1.9.3, Adafruit GFX Library 1.11.0, Arduino IDE 1.8.19, VS Code

Continue reading at [https://coertvonk.com/category/sw/arduino/pitch-detector](https://coertvonk.com/category/sw/arduino/pitch-detector)

(c) Copyright 2015-2018,2022, Johan Vonk
