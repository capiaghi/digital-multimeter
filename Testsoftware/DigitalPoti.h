// ****************************************************************************
/// \file      DigitalPoti.h
///
/// \brief     Driver for AD5271
///
/// \details   
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.1
///
/// \date      20171122
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
#ifndef __DIGITAL_POTI_H__
#define __DIGITAL_POTI_H__

// Include ********************************************************************
#include "Arduino.h"
#include "Constants.h"
#include "Pinmapping.h"
#include "SPI.h"

// Exported types *************************************************************


// Exported constants *********************************************************

// Exported macros ************************************************************

// Exported functions *********************************************************
void digitalPotInit();
uint16_t digitalPotWrite(uint16_t ctrl, uint16_t data);
uint16_t getCtrlRegister();
void printHex(int num, int precision);

#endif
