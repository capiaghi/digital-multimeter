// ****************************************************************************
/// \file      ButtonHandler.cpp
///
/// \brief     Sets and returns Button flags
///
/// \details   Button Handler for button up, enter and down. Debounced.
///            Adapted from http://www.arduino.cc/en/Tutorial/Debounce
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
/// \warning   Not debounced
///
/// \todo     
///
// ****************************************************************************
// Includes *******************************************************************
#include "ButtonHandler.h"

// Private constants **********************************************************
static uint8_t 	buttonStateUp        = REVERSE_POLARITY;
static uint8_t 	buttonStateEnter     = REVERSE_POLARITY;
static uint8_t 	buttonStateDown      = REVERSE_POLARITY;

// Button pressed flag
static uint8_t 	buttonUpFlag      = LOW;
static uint8_t 	buttonEnterFlag   = LOW;
static uint8_t 	buttonDownFlag    = LOW;
 
// ----------------------------------------------------------------------------
/// \brief     Initialize buttosn
/// \detail    Turn on Pull-ups, define as input
/// \warning   
/// \return    void
/// \todo      
///
void initButton()
{
   // Initialize digital pins as an input
   pinMode(BUTTON_UP_PIN, INPUT);
   pinMode(BUTTON_ENTER_PIN, INPUT);
   pinMode(BUTTON_DOWN_PIN, INPUT);

   //pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
   //pinMode(BUTTON_ENTER_PIN, INPUT_PULLUP);
   //pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
}

// ----------------------------------------------------------------------------
/// \brief     Get state of Button Up
/// \detail    Gets the state of the button and resets the flag
/// \warning   
/// \return    state: 1 pressed, 0 not pressed
/// \todo      
///
uint8_t getButtonStateUp()
{
	if(buttonUpFlag == HIGH)
	{
		buttonUpFlag = LOW;
		return 1;
	}
	else
	{
		buttonUpFlag = LOW;
		return 0;
	}
}

// ----------------------------------------------------------------------------
/// \brief     Get state of Button Enter
/// \detail    Gets the state of the button and resets the flag
/// \warning   
/// \return    state: 1 pressed, 0 not pressed
/// \todo      
///
uint8_t getButtonStateEnter()
{
	if(buttonEnterFlag == HIGH)
	{
		buttonEnterFlag = LOW;
		return 1;
	}
	else
	{
		buttonEnterFlag = LOW;
		return 0;
	}
}

// ----------------------------------------------------------------------------
/// \brief     Get state of Button Down
/// \detail    Gets the state of the button and resets the flag
/// \warning   
/// \return    state: 1 pressed, 0 not pressed
/// \todo      
///
uint8_t getButtonStateDown()
{
	if(buttonDownFlag == HIGH)
	{
		buttonDownFlag = LOW;
		return 1;
	}
	else
	{
		buttonDownFlag = LOW;
		return 0;
	}
}

void clearButtonAllFlags()
{
   buttonUpFlag    = LOW;
   buttonEnterFlag = LOW;
   buttonDownFlag  = LOW;
}



// ----------------------------------------------------------------------------
/// \brief     Updates the flags of the buttons
/// \detail    Sets the flags of the 3 buttons, NOT debounced
/// \warning   
/// \return    state: 1 pressed, 0 not pressed
/// \todo      
///
void updateButtonHandler()
{
   // Read out buttons
   uint8_t readingUp      = digitalRead(BUTTON_UP_PIN);
   uint8_t readingEnter   = digitalRead(BUTTON_ENTER_PIN);
   uint8_t readingDown    = digitalRead(BUTTON_DOWN_PIN);

   // UP
   // if the button state has changed:
   if (readingUp != buttonStateUp)
   {
      buttonStateUp = readingUp;

      if (buttonStateUp == POLARITY)
      {
         buttonUpFlag = HIGH;
      }
   }

   // ENTER
   // if the button state has changed:
   if (readingEnter != buttonStateEnter)
   {
      buttonStateEnter = readingEnter;

      if (buttonStateEnter == POLARITY)
      {
         buttonEnterFlag = HIGH;
      }
   }


   // DOWN
   // if the button state has changed:
   if (readingDown != buttonStateDown)
   {
      buttonStateDown = readingDown;

      if (buttonStateDown == POLARITY)
      {
         buttonDownFlag = HIGH;
      }
   }
   
}