#pragma once

#include <Arduino.h>

/**********************
* Atmel ATMega328P ADC
**********************
* see the data sheet
*   http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf
*/

// 24.9.1 ADMUX ~ ADC Multiplexer Selection Register

enum ADMUX_REFS_t {
    ADMUX_REFERENCE_EXT = 0,
    ADMUX_REFERENCE_VCC = bit(6),  // 5V on Arduino Uno
    ADMUX_REFERENCE_1V1 = bit(6) | bit(7)
};
enum ADMUX_ADLAR_t {
    ADMUX_RIGHT_ALIGN = 0,
    ADMUX_LEFT_ALIGN = bit(5)
};
enum ADMUX_MUX_t {
    ADMUX_INPUT_A0 = 0,
    ADMUX_INPUT_A1 = 1,
    ADMUX_INPUT_A2 = 2,
    ADMUX_INPUT_A3 = 3,
    ADMUX_INPUT_A4 = 4,
    ADMUX_INPUT_A5 = 5
};
uint8_t const ADMUX_INPUT_MASK = 0x0F;

// 24.9.2 ADCSRA ~ ADC Control and Status Register A

enum ADCSRA_ADEN_t {
    ADCSRA_CONVERT_DISABLE = 0,
    ADCSRA_CONVERT_ENABLE = bit(7),
};
enum ADCSRA_ADSC_t {
    ADCSRA_CONVERT_FINISHED = 0,
    ADCSRA_CONVERT_START = bit(6),
};
enum ADCSRA_ADATE_t {
    ADCSRA_AUTO_TRIGGER_DISABLE = 0,
    ADCSRA_AUTO_TRIGGER_ENABLE = bit(5)
};
enum ADCSRA_ADIF_t {
    ADCSRA_IRQ_NOTYET = 0,
    ADCSRA_IRQ_ACTIVE = bit(4)
};
enum ADCSRA_ADIE_t {
    ADCSRA_IRQ_DISABLE = 0,
    ADCSRA_IRQ_ENABLE = bit(3)
};
enum ADCSRA_ADPS_t {
    ADCSRA_PRESCALER_DIV1 = 0,
    ADCSRA_PRESCALER_DIV2 = 1,
    ADCSRA_PRESCALER_DIV4 = 2,
    ADCSRA_PRESCALER_DIV8 = 3,
    ADCSRA_PRESCALER_DIV16 = 4,
    ADCSRA_PRESCALER_DIV32 = 5,
    ADCSRA_PRESCALER_DIV64 = 6,
    ADCSRA_PRESCALER_DIV128 = 7
};

// 24.9.3 ADCL and ADCH ~ The ADC Data Register
// with ADMUX_RESULT_RIGHT_ALIGN .. ADCH[1:0] = b9..b8, ADCL[7:0] = b7..b0
// with ADMUX_RESULT_LEFT_ALIGN ... ADCH[7:0] = b9..b2, ADCL[7:6] = b1..b0

// 24.9.4 ADCSRB ~ ADC Control and Status Register B

enum ADCSRB_ACME_t {  // see 23.3.1
    ADCSRB_MULTIPLEXER_DISABLE = 0,
    ADCSRB_MULTIPLEXER_ENABLE = bit(6)
};
enum ADCSRB_ADTS_t {
    ADCSRB_TRIGGERSRC_FREERUNNING = 0,
    ADCSRB_TRIGGERSRC_ANALOGCOMP = 1,
    ADCSRB_TRIGGERSRC_EXTERNAL_IRQ = 2,
    ADCSRB_TRIGGERSRC_TC0_MATCH_A = 3,
    ADCSRB_TRIGGERSRC_TC0_OVERFLOW = 4,
    ADCSRB_TRIGGERSRC_TC1_MATCH_B = 5,
    ADCSRB_TRIGGERSRC_TC1_OVERFLOW = 6,
    ADCSRB_TRIGGERSRC_TC1_CAPTURE = 7
};

// 24.9.5 DIDR0 ~ Digital Input Disable Register 0

enum DIDR0_ADCxD_t {
    DIDR0_DISABLE_DIGBUF_0 = bit(0),
    DIDR0_DISABLE_DIGBUF_1 = bit(1),
    DIDR0_DISABLE_DIGBUF_2 = bit(2),
    DIDR0_DISABLE_DIGBUF_3 = bit(3),
    DIDR0_DISABLE_DIGBUF_4 = bit(4),
    DIDR0_DISABLE_DIGBUF_5 = bit(5)
};
