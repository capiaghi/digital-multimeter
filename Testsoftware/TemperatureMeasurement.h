// ****************************************************************************
/// \file      TemperatureMeasurement.h
///
/// \brief     Measures the temperature
///
/// \details   Functions for the EUR Project
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
#ifndef __TEMPERATURE_MEASUREMENT_H__
#define __TEMPERATURE_MEASUREMENT_H__

// Include ********************************************************************
#include "Arduino.h"
#include "Pinmapping.h"

// Exported types *************************************************************


// Exported constants *********************************************************

// Exported macros ************************************************************

// Exported functions *********************************************************
float getTemperatureC();
uint16_t measureTemperature();

#endif