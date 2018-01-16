// ****************************************************************************
/// \file      CurrentMeasurement.h
///
/// \brief     Measurements functions Current
///
/// \details   Measurements functions Current for the EUR Project
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.3
///
/// \date      20171120
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
#ifndef __CURRENT_MEASUREMENT_H__
#define __CURRENT_MEASUREMENT_H__

// Include ********************************************************************
#include "Arduino.h"
#include "Constants.h"
#include "Pinmapping.h"

// Exported types *************************************************************


// Exported constants *********************************************************

// Exported macros ************************************************************

// Exported functions *********************************************************
float getCurrentmA();
uint16_t measureCurrent();
float getShuntValue();
void setShuntValue(float value);
void setGainCurrentMeasurement(float value);
float getGainCurrentMeasurement();
void currentZeroCorretion();


#endif
