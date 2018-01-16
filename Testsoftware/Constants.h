// ****************************************************************************
/// \file      Constants.h
///
/// \brief     Constants
///
/// \details   All Constants for the EUR Project
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.2
///
/// \date      20161222
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
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Include ********************************************************************

// Exported types *************************************************************
/// \brief     Optional description
/// \details   Optional description (more detailed)

// Exported constants *********************************************************

const uint16_t   ADC_MAX_VALUE         = 1023;
const uint8_t    ADC_MIN_VALUE         = 0;
const float      ADC_REF_VOLTAGE       = 3.3;
const float      ADCCONST              = (ADC_REF_VOLTAGE / ADC_MAX_VALUE);
const float      U_OFFSET              = (ADC_REF_VOLTAGE / 2.0);
const uint16_t   NUM_OF_OFFSET_SAMPLES = 66; // 2^6 = 64, + min und max
                                             // Maximum value: uint16_t -> 16 bit.
                                             // ADC: 2^10 -> 2^6, if full range
const uint8_t    NUM_OF_SHIFTS         = 6; // division 64
 

const char       SOFTWARE_VERSION[5]  = "V2.0";
const char       YEAR[5]               = "2017";
const uint32_t   UART_SPEED            = 115200;

// EEPROM Addresses with enough space
const uint8_t  EEPROM_ADDR_HIGH_VOLTAGE      = 10; 
const uint8_t  EEPROM_ADDR_LOW_VOLTAGE       = 20;
const uint8_t  EEPROM_ADDR_HIGH_RESISTANCE   = 30;
const uint8_t  EEPROM_ADDR_LOW_RESISTANCE    = 40;
const uint8_t  EEPROM_ADDR_CURRENT           = 50;
const uint8_t  EEPROM_ADDR_SHUNT             = 60;
const uint8_t  EEPROM_ADDR_CODE              = 70;

// Constants to save memory
const char     SEPARATOR[] = "------";
const char     EEPROM_FEEDBACK_MSG[] = "I received: ";
const char     EEPROM_OLD_VAL_MSG[] = "Old Vaule: ";




// Exported macros ************************************************************

//#define DEBUG                 ( 1 ) // Serial Debug enable
#define CSV_ENABLE            ( 1 ) // CSV Output

#define DECIMAL_PLACES_UART   ( 3 )


#define HIGH_RANGE            ( 1 )
#define LOW_RANGE             ( 0 )

#define DISPLAY_OUTPUT        ( 0 )
#define CSV_OUTPUT            ( 1 )    


// Define Boolean Variable
#ifndef TRUE
   #define TRUE               ( 1 )
#endif
#ifndef FALSE
   #define FALSE              ( !TRUE )
#endif


#define SPI_FREQ_POTI		   1000000UL // Maximum SCLK frequency is 50 MHz

// POTI
#define COMMAND0              ( 0 )    // NOP: do nothing.
#define COMMAND1              ( 1 )    // Write contents of serial register
                                       // data to RDAC. 
#define COMMAND7              ( 7 )    // Write contents of serial register
                                       // data to control register.
#define COMMAND8              ( 8 )    // Read contents of control register.
#define C1                    ( 2 )    // C3 C2 C1 C0 -> 0010

#define SERIAL_TIMEOUT        ( 2000 )


// Exported functions *********************************************************


#endif
