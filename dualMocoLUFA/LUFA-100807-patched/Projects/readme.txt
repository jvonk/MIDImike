
     dualMocoLUFA Project
     Copyright (C) 2013 by morecat_lab

     2013/09/22
              
     http://morecatlab.akiba.coocan.jp/

     based on LUFA-100807

This is dual mode firmware for Arduino Uno.
There are two mode on this firmware, USB-MIDI(MocoLUFA) and Arduino-Serial.

INSTRUCTIONS
1. Burn 8u2 (or 16u2) on Arduino Uno.
   check original document below.
2. USB-MIDI formware work as default.
3. To enable Arduino-Serial, ass jumper to PIN 4(MOSI PB2) and PIN6 (grand) on ICSP connector for 8U2.
   Reset is required to change the firmware mode.

-Yoshi

-------------------------------------
original readme.txt from Arduino-Serial

To setup the project and upload the Arduino usbserial application firmware to an ATMEGA8U2 using the Arduino USB DFU bootloader:
1. unpack the source into LUFA's Projects directory
2. set ARDUINO_MODEL_PID in the makefile as appropriate
3. do "make clean; make"
4. put the 8U2 into USB DFU mode:
4.a. assert and hold the 8U2's RESET line
4.b. assert and hold the 8U2's HWB line
4.c. release the 8U2's RESET line
4.d. release the 8U2's HWB line
5. confirm that the board enumerates as either "Arduino Uno DFU" or "Arduino Mega 2560 DFU"
6. do "make dfu" (OS X or Linux - dfu-programmer must be installed first) or "make flip" (Windows - Flip must be installed first)

Check that the board enumerates as either "Arduino Uno" or "Arduino Mega 2560".  Test by uploading a new Arduino sketch from the Arduino IDE.
