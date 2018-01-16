// ****************************************************************************
/// \file      VoltageMeasurement.cpp
///
/// \brief     Measurements functions
///
/// \details   Measurements functions for the EUR Project
///            Support for Digital Potentiometer AD5271
///            Added Offset calibration
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.3
///
/// \date      2017112017
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
#include "VoltageMeasurement.h"

// Private constants **********************************************************

static float highDampingVoltageMeasurement   = 14.3824; 			// Default value (50 k Poti)
static float lowDampingVoltageMeasurement    = 14.3824;			// Default value (50 k Poti)
static float uOffset                      = U_OFFSET;          // Offset
static uint16_t uOffsetADC                = 0;
static uint16_t uOffsetADCsum             = 0;
static uint16_t ADCminValue               = ADC_MAX_VALUE;
static uint16_t ADCmaxValue               = ADC_MIN_VALUE;


// ----------------------------------------------------------------------------
/// \brief     Voltage Measurement
/// \detail    Reads ADC value and calculates the voltage.
/// \warning   
/// \return    float voltage in Volt
/// \todo      
///
float getVoltageV(uint8_t range)
{
   uint16_t voltageADC = measureVoltage();
   float voltageV = 0.0;

   if (range == HIGH_RANGE) // Select correct Damping and calculated voltage
   {
      voltageV = (voltageADC*ADCCONST - uOffset)*(highDampingVoltageMeasurement) ; // TBD: Efficiency
   }
   else if (range == LOW_RANGE)
   {
      voltageV = (voltageADC*ADCCONST - uOffset)*(lowDampingVoltageMeasurement); // TBD: Efficiency
   }
   else 
   {
      voltageV = -1;
   }
   
   return voltageV;
   
}


// ----------------------------------------------------------------------------
/// \brief     Set high Damping of voltage measurement
/// \detail    
/// \warning   
/// \return  
/// \todo      
///
void setHighDampingVoltageMeasurement(float value)
{
   highDampingVoltageMeasurement = value;
}

// ----------------------------------------------------------------------------
/// \brief     Set low Damping of voltage measurement
/// \detail    
/// \warning   
/// \return  
/// \todo      
///
void setLowDampingVoltageMeasurement(float value)
{
   lowDampingVoltageMeasurement = value;
}

// ----------------------------------------------------------------------------
/// \brief     Get high Damping of voltage measurement
/// \detail    
/// \warning   
/// \return    float high Damping of voltage measurement
/// \todo      
///
float getHighDampingVoltageMeasurement()
{
   return highDampingVoltageMeasurement;
}

// ----------------------------------------------------------------------------
/// \brief     Get low Damping of voltage measurement
/// \detail    
/// \warning   
/// \return    float low Damping of voltage measurement
/// \todo      
///
float getLowDampingVoltageMeasurement()
{
   return lowDampingVoltageMeasurement;
}

// ----------------------------------------------------------------------------
/// \brief     Measure ADC value 
/// \detail    
/// \warning   
/// \return    uint16_t ADC value
/// \todo      
///
uint16_t measureVoltage()
{
	return analogRead(VOLTAGE_MANAGEMENT_ADC_CHANNEL); // Read ADC value
}

// ----------------------------------------------------------------------------
/// \brief     Calibrates internal offset calculation
/// \detail    
/// \warning   Make sure that nothing is connected on V and COM Port
/// \return    
/// \todo      
///
void offsetCalibration()
{
   uOffsetADC = calcMeanValue(VOLTAGE_MANAGEMENT_ADC_CHANNEL);  
   uOffset = uOffsetADC*ADCCONST;  
}



// ----------------------------------------------------------------------------
/// \brief     Calculates mean value (ADC value)
/// \detail    Takes NUM_OF_OFFSET_SAMPLES samples, removes highest and lowest
///            value and calculates mean value
/// \warning   
/// \return    uint16_t mean value
/// \todo      
///
uint16_t calcMeanValue(uint8_t pin)
{
   uint16_t actADCval   = 0;
   uint16_t sumADCval   = 0;
   ADCminValue          = ADC_MAX_VALUE;
   ADCmaxValue          = ADC_MIN_VALUE;
   
   for(int i = 0; i < NUM_OF_OFFSET_SAMPLES; i++)
   {
      actADCval = analogRead(pin); // Read ADC value
      sumADCval = sumADCval + actADCval;
     
     
      // Save min and max values
      if( actADCval < ADCminValue )
      {
         ADCminValue = actADCval;
      }
      
      if( actADCval > ADCmaxValue )
      {
         ADCmaxValue = actADCval;
      }      
   }
   
   // 
   
   actADCval = (sumADCval - ADCminValue - ADCmaxValue);
   #ifdef DEBUG
      Serial.println("Without max und min");
      Serial.println(actADCval);
   #endif
   
   // Division
   actADCval = actADCval >> NUM_OF_SHIFTS;
   
   #ifdef DEBUG
      Serial.println("Finished calcMeanValue");
      Serial.println(actADCval);
   #endif   
   
   return actADCval;
}

// ----------------------------------------------------------------------------
/// \brief     Read offset voltage
/// \detail    
/// \warning   
/// \return    float offset
/// \todo      
///
float readOffset()
{
   return uOffset;
}

// ----------------------------------------------------------------------------
/// \brief     Read offset voltage in ADC values (0 - 1023)
/// \detail    
/// \warning   
/// \return    uint16_t offset (ADC value)
/// \todo      
///
uint16_t readOffsetADC()
{
   return uOffsetADC;
}
