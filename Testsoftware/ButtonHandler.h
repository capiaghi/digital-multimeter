// ****************************************************************************
/// \file      ButtonHandler.h
///
/// \brief     Sets and return Button flags. Debounced.
///
/// \details   Button Handler
///
/// \author    Christoph Capiaghi
///
/// \version   0.2
///
/// \date      20170509
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
#ifndef __BUTTONHANDLER_H__
#define __BUTTONHANDLER_H__

// Include ********************************************************************
#include "Arduino.h"
#include "PinMapping.h"

// Exported types *************************************************************


// Exported constants *********************************************************
//const long       DEBOUNCE_DELAY = 50;    // the debounce time; increase if the output flickers


// Exported macros ************************************************************
#define POLARITY  ( HIGH ) // LOW: low active, HIGH: high active


#define REVERSE_POLARITY ( !POLARITY )

// Exported functions *********************************************************
void     initButton();           // Call this first (Initialization)
void     updateButtonHandler();  // Read actual button states -> Polling required
void     clearButtonAllFlags();  // Deletes all button flags
uint8_t  getButtonStateUp();     // Returns Button Flag and resets flag
uint8_t 	getButtonStateEnter();
uint8_t 	getButtonStateDown();

#endif
