// ****************************************************************************
/// \file      CurrentMeasurement.cpp
///
/// \brief     Measurements functions
///
/// \details   Measurements functions for the EUR Project
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
/// \warning   Not compatible with PASE2016
///
/// \todo     
///
// ****************************************************************************
// Includes *******************************************************************
#include "CurrentMeasurement.h"
#include "VoltageMeasurement.h"

// Private constants **********************************************************

static float gainCurrentMeasurement 		= 11.0;
static float shuntValue                   = 0.050;
static float offsetCorrection             = 0.0;


// ----------------------------------------------------------------------------
/// \brief     Current Measurement
/// \detail    Reads ADC value and calculates the Current.
/// \warning   
/// \return    Current in mili Ampere (float)
/// \todo      
///
float getCurrentmA()
{
   uint16_t currentADC = measureCurrent();
   float uOffset = readOffset();
   float currentmA = 0.0;
      
	currentmA = -(currentADC*ADCCONST - uOffset) / (gainCurrentMeasurement * shuntValue) * 1000.0 - offsetCorrection; // TBD: Efficiency

   return currentmA;
}

// ----------------------------------------------------------------------------
/// \brief     Measure ADC value 
/// \detail    
/// \warning   
/// \return    uint16_t ADC value
/// \todo      
///
uint16_t measureCurrent()
{
	return analogRead( CURRENT_MANAGEMENT_ADC_CHANNEL ); // Read ADC value
}

// ----------------------------------------------------------------------------
/// \brief     Get shunt value
/// \detail    
/// \warning   
/// \return    float shunt value in Ohm
/// \todo      
///
float getShuntValue()
{
   return shuntValue;
}

// ----------------------------------------------------------------------------
/// \brief     Set shunt value
/// \detail    Shunt value in Ohm
/// \warning   
/// \return    float shunt vaule in Ohm
/// \todo      
///
void setShuntValue(float value)
{
   shuntValue = value;
}

// ----------------------------------------------------------------------------
/// \brief     Get gain of current measurement
/// \detail    
/// \warning   
/// \return    float gain of current measurement
/// \todo      
///
float getGainCurrentMeasurement()
{
   return gainCurrentMeasurement;
}

// ----------------------------------------------------------------------------
/// \brief     Get gain of current measurement
/// \detail    
/// \warning   
/// \return    float gain of current measurement
/// \todo      
///
void setGainCurrentMeasurement(float value)
{
   gainCurrentMeasurement = value;
}

void currentZeroCorretion()
{
   offsetCorrection = getCurrentmA();
}
   
