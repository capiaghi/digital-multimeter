// ****************************************************************************
/// \file      TemperatureMeasurement.cpp
///
/// \brief     Measurement functions
///
/// \details   Measurement functions for the EUR Project
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
// ****************************************************************************
// Includes *******************************************************************
#include "TemperatureMeasurement.h"

// Private constants **********************************************************


// ----------------------------------------------------------------------------
/// \brief     Temperature Measurement
/// \detail    Reads ADC value and calculates the temperature.
/// \warning   Not yet implemented
/// \return    float Temperature in Celsius
/// \todo      
///
float getTemperatureC()
{
   return -1.0; 
}


// ----------------------------------------------------------------------------
/// \brief     Measure ADC value 
/// \detail    
/// \warning   
/// \return    uint16_t ADC value
/// \todo      
///
uint16_t measureTemperature()
{
	return analogRead(TEMP_MEASUREMENT_ADC_CHANNEL); // Read ADC value
}
