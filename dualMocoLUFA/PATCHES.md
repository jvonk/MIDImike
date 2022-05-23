# Patch

A precompiled `.hex` can be found in `LUFA-100807-patched/Projects/`. If you want to use that, you can skip this writeup.

## Download and patch

This section is for the die-hard folks that want to start from vanilla downloads. If you're happy using the sources in `LUFA-100807-patched`, you can jump to the Build section.

Download the sources

- [LUFA-100807](http://www.fourwalledcubicle.com/files/dualMocoLUFA/LUFA-100807.zip), unzip and remove the contents of the Projects directory.
- [dualMocoLUFA](http://morecatlab.akiba.coocan.jp/lab/wp-content/uploads/2013/09/dualMocoLUFA.tgz), unzip and move the files to the LUFA Projects directory.

Patch to specify the IDs, microcontroller and reverse the pin logic.

- The main LUFA `makefile`
    - change it so that it only builds the `Projects` directory

- `Projects\makefile` (specify target)
    - line 65: `MCU = atmega16u2`
    - line 72: `ARDUINO_MODEL_PID = 0x0043`

- `Projects\Descriptors.c` (fix compile error and specify identifiers)
    - search and replace `PROGMEM` with `PROGMEM const`
    - line 80: `.VendorID = 0x2341`
    - line 82: `.ProductID = ARDUINO_MODEL_PID`

- `Projects\Descriptors.c` (change the USB device name)
    - line 452: `.Header = {.Size = USB_STRING_LEN(14), .Type = DTYPE_String}`    
    - line 454: `.UnicodeString = L"Pitch Detector"`

- `Projects\Descriptors.h` (specify ID)
    - line 57: `ARDUINO_UNO_PID 0x0043`

- `Projects\dualMoco.c` (reverse the logic)
    - line 48: mocoMode = 0
    - line 340: mocoMode = 1

## Build

From Linux (e.g. Window Subsystem for Linux)

```
sudo apt-get install binutils make gcc-avr avr-libc uisp avrdude flex byacc bison
cd Projects
make clean
make -s
```

Move the resulting `Projects/dualMoco.hex` over to your regular environment.[^1]

[^1]: For your piece of mind, the original firmware can be found in the Arduino directory as `hardware\arduino\avr\firmwares\atmegaxxu2\arduino-usbserial\Arduino-usbserial-atmega16u2-Uno-Rev3.hex`.

