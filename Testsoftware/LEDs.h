// ****************************************************************************
/// \file      LEDs.h
///
/// \brief     Controll for all LEDs (RGB and normal LEDs)
///
/// \details   
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.1
///
/// \date      20170523
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
/// \todo     
///

// Define to prevent recursive inclusion
#ifndef __LEDS__
#define __LEDS__

// Include ********************************************************************
#include <Adafruit_NeoPixel.h>  // RGB LEDs
#include "Arduino.h"
#include "Pinmapping.h"
#include "VoltageMeasurement.h"


// Exported types *************************************************************


// Exported constants *********************************************************
const uint8_t  NUM_OF_RGB_LED       = 4;
const uint8_t  BRIGHTNESS           = 64; // 0 ... 255

const uint32_t RGB_BLACK   = 0;  // (0, 0, 0)       
const uint32_t RGB_WHITE  = 0xFFFFFF;
const uint32_t RGB_RED    = 0xFF0000;        
const uint32_t RGB_GREEN  = 0x00FF00;  
const uint32_t RGB_BLUE   = 0x0000FF;

const int8_t 	RGB_STEPSIZE = 85;  // 4 LEDs, 2 colors (Red, green, blue)
                                   //-> 12 states: 1024/12 = 85.33 -> 85 steps
              
// Order of the RGB LEDs              
#define LED4   ( 3 )
#define LED3   ( 2 )
#define LED2   ( 1 )
#define LED1   ( 0 )


// Exported macros ************************************************************

// Exported functions *********************************************************
void initLEDs();
void RGBTest();
void LEDTest();
void LEDFullPower();
void LEDOff();

void setGreenLED3();
void resetGreenLED3();
void toggleGreenLED3();

void setRedLED();
void resetRedLED();
void LEDBar(uint16_t ADCvalue);



static uint32_t Wheel(byte WheelPos);
static void rainbowCycle(uint8_t wait);

#endif