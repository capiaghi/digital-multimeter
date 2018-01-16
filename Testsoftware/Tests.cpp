// ****************************************************************************
/// \file      Tests.h
///
/// \brief     Some tests for the DMM
///
/// \details   
///
/// \author    Christoph Capiaghi
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

// ****************************************************************************
// Includes *******************************************************************
#include "Tests.h"

// ----------------------------------------------------------------------------
/// \brief     Full Power Test
/// \detail    Switch on all LEDs (including RGBs) and switch display to white
/// \warning   
/// \return   
/// \todo      
///
void FullPower()
{
   // All LEDs on
   LEDFullPower();
   
   // White display
   displayFullPower();

   // Test for 20 s
   Serial.println("Remaining time");
   for(uint8_t i = 20; i > 0; i--)
   {
      Serial.print(i);
      Serial.println(F(" s"));
      delay(1000);
   }
  
   Serial.println(F("------------------"));
   Serial.println(F("All RGB LEDs off"));
   LEDOff();
   displayRefresh(); 
  
   Serial.println(F("FullPower Test finished"));
}
