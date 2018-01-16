// ****************************************************************************
/// \file      PinMapping.h
///
/// \brief     Defines Pins of the Board
///
/// \details    
///
/// \author    Christoph Capiaghi
///
/// \version   0.2
///
/// \date      20171123
/// 
/// \copyright Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// http://www.apache.org/licenses/LICENSE-2.0
///
/// \pre       
///
/// \bug       
///
/// \warning   
///
/// \todo     Testing new pin configuration
///

// Define to prevent recursive inclusion
#ifndef __PINMAPPING_H__
#define __PINMAPPING_H__

// Include ********************************************************************
#include "Arduino.h"
// Exported types *************************************************************
/// \brief     Optional description
/// \details   Optional description (more detailed)


// Exported constants *********************************************************

// Exported macros ************************************************************
// Mapping according "pins_arduino.h"
// ATMEL ATMEGA32U4 / ARDUINO LEONARDO

// Digital Poti
// D5#              PC6     ???         OC3A/#OC4A
#define SPI_CS_POT_PIN                    ( 5 )   // Digital Potentiometer \CS, Pin 31, PC6

// RGB LED Data Pin
// D10#     A10     PB6     PWM16       OC1B/0c4B/ADC13/PCINT6
#define RGB_MANAGEMENT_PIN              ( 10 )  // RGB Data Pin, Pin 30, PB6

// LCD Pins
// SS       D17     PB0                 RXLED,SS/PCINT0
#define SPI_CS_LCD_PIN                  ( 17 )  // SPI \CS Display, SPI_CS_LCD, D17
// D7               PE6                 INT6/AIN0
#define RESET_LCD_PIN                   ( 7 )   // RESET_LCD, Pin 1, PE6
// D9#      A9      PB5     PWM16       OC1A/#OC4B/ADC12/PCINT5
#define DC_LCD_PIN                      ( 9 )    // DC_LCD, Pin 29, PB5

// Stud Pin
// D11#             PB7     PWM8/16     0C0A/OC1C/#RTS/PCINT7
#define STUD_PIN                        ( 11 )   // Stud1, Pin 12, PB7

/*
#ifdef TEAM3
   #define DC_LCD_PIN                      ( 11 )   // DC_LCD, Pin 12, PB7 -> Not yet tested  TBD
   #define STUD_PIN                        ( 9 )    // Stud 1, Pin 29, PB5
#else  
   #define DC_LCD_PIN                      ( 9 )    // DC_LCD, Pin 29, PB5
   #define STUD_PIN                        ( 11 )   // Stud1, Pin 12, PB7
#endif
*/

//LEDs
// D3#              PD0     PWM8/SCL    OC0B/SCL/INT0
#define LED1_PIN                        ( 3 )   // Pin 18, PD0 
// D2               PD1     SDA         SDA/INT1
#define LED2_PIN                        ( 2 )   // Pin 19, PD1
// D0               PD2                 RXD1/INT2
#define LED3_PIN                        ( 0 )   // Pin 20, PD2

// Buttons
//#define BUTTON_UP_PIN                   ( 4 )   // Pin 25, PD4
// TXLED    D30     PD5                 XCK1
#define BUTTON_UP_PIN                  ( 30 )  // Pin 22, PD5
// D12      A11     PD6                 T1/#OC4D/ADC9
#define BUTTON_ENTER_PIN               ( 12 )  // Pin 26, PD6
// D6#      A7      PD7     FastPWM     #OC4D/ADC10
#define BUTTON_DOWN_PIN                ( 6 )   // Pin 27, PD7

// ADC Pins
// A5       D23     PF0                 ADC0
#define TEMP_MEASUREMENT_ADC_CHANNEL    ( A5 )     // ADC Channel Temperature (NTC)
// A4       D22     PF1                 ADC1
#define CURRENT_MANAGEMENT_ADC_CHANNEL  ( A4 )     // ADC Channel Current
// D4       A6      PD4                 ADC8
#define EXTERNAL_ADC_CHANNEL            ( A6 )     // ADC Channel External (Audio Connector)
// D8       A8      PB4                 ADC11/PCINT4
#define VOLTAGE_MANAGEMENT_ADC_CHANNEL  ( A8 )     // ADC Channel Voltage


#define SPI_CS_SD_PIN                    ( 13 )  // SPI_CS_SD, Pin 32, PC7, SD Card not used

// Exported functions *********************************************************

#endif
