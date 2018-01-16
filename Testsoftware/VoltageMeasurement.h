// ****************************************************************************
/// \file      Measurements.h
///
/// \brief     Measurements functions
///
/// \details   Measurements functions for the EUR Project
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.1
///
/// \date      20161202
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
#ifndef __VOLTAGE_MEASUREMENT_H__
#define __VOLTAGE_MEASUREMENT_H__

// Include ********************************************************************
#include "Arduino.h"
#include "Constants.h"
#include "Pinmapping.h"



// Exported types *************************************************************


// Exported constants *********************************************************

// Exported macros ************************************************************

// Exported functions *********************************************************
float getVoltageV(uint8_t range);
void setHighDampingVoltageMeasurement(float value);
void setLowDampingVoltageMeasurement(float value);
float getHighDampingVoltageMeasurement();
float getLowDampingVoltageMeasurement();
uint16_t measureVoltage();
void offsetCalibration(); // Make sure that nothing is connected on V and COM Port
uint16_t calcMeanValue(uint8_t pin);
float readOffset();
uint16_t readOffsetADC();


#endif