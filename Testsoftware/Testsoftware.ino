// ****************************************************************************
/// \file      Testsoftware.ino
///
/// \brief     main code
///
/// \details   Testsoftware for the Student Project PASE. Feel free to add more functionality.
///            Actual: 100 Hz refresh rate
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   2.0
///
/// \date      20170522
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
/// \warning   - Complete redesign of V1.1. V2.0 is not compatible to V1.1 an earlier!
///
/// \todo      - NTC: Calculate correct resistance, or generate look-up table
///            - Programm memory: Optimize code!
///            - Warning, if calibration make no sense
///            
///           
///           
///
// ****************************************************************************
// Includes *******************************************************************
#include <EEPROM.h>                 // EEPROM for saving configurations
#include "VoltageMeasurement.h"     // For Voltage Measurements
#include "CurrentMeasurement.h"     // For Current Measurements
#include "TemperatureMeasurement.h" // For Temperature Measurements
#include "LEDs.h"
#include "Tests.h"                  // All test functions (RGB, LED, Power)
#include "Constants.h"              // Constants for global use
#include "PinMapping.h"             // All Pin Definitons
#include "ButtonHandler.h"          // Get button states
#include "Display.h"                // All display outputs
#include "DigitalPoti.h"

// Private types **************************************************************
/// \brief  Used States
/// \details List of all used states of the DMM. Feel free to add more functionality
typedef enum stm_state_e
{
   STM_STATE_STARTUP,               /// EEPROM restoring and UART Welcome Screen
   STM_STATE_CONFIGURATION,         /// Configuration of DMM
   STM_STATE_VOLTAGE_MEASUREMENT,   /// Starts Voltage Measurement and screens on display
   STM_STATE_VOLTAGE_OSCILLOSCOPE,  /// Starts Voltage Measurement and screens on a OSCILLOSCOPE
   STM_STATE_VOLTAGE_UART,          /// Starts Voltage Measurement and screens on a UART
   STM_STATE_CURRENT_MEASUREMENT,   /// Starts Current Measurement
   STM_STATE_LED_TEST,              /// Starts LED Test
   STM_STATE_POWER_TEST,            /// Starts Power test (switch on all LEDs, white screen)
   STM_STATE_NTC_TEST,              /// Starts Temperature Measurement and screens on display
   STM_STATE_DIY                    /// "Do it yourself" part of the project
} stm_state_t;

typedef unsigned char stm_bool_t; 

// Private constants **********************************************************

// Private macros *************************************************************

// Static variables ***********************************************************

static stm_state_t   stm_actState;    // Actual State variable
static stm_state_t   stm_newState;    // New State variable
static stm_bool_t    stm_entryFlag;   // Flag for handling the entry action
static stm_bool_t    stm_exitFlag;    // Flag for handling the exit action

static uint8_t       currentMode = DISPLAY_OUTPUT;
static uint8_t       voltageMode = HIGH_RANGE;
static uint16_t      counter = 0;

static float         measurement = 0.0;
static uint16_t      ADCvalue = 0;

// Two Resistor settings saved:
static uint8_t       dValuePotiHigh = 0; // R = D/256*100 kOhm
static uint8_t       dValuePotiLow = 0; 


// Private function prototypes ************************************************



// ISR **********************************************************
// ----------------------------------------------------------------------------
/// \brief     Timer interrupt 
/// \detail    For measurement: Every 10 ms an interrupt
/// \warning   
/// \return   
/// \todo      
///
uint8_t runMeasurement;
ISR(TIMER3_COMPA_vect)
{
   runMeasurement = 1;
   toggleGreenLED3(); // For perfomance measurement
   counter++;
}


// Initialization **********************************************************
// The setup function runs once when you press reset or power the board
void setup() {
   // Timer for ADC
   // Init timer 3, interrupts every second
   TCCR3A = 0;
   TCCR3B = 0xc;     // CTC mode, prescaler = 256+ (clk/256 (From prescaler)

   OCR3A = 312;      // 8 MHz / 256 = 31250 gives exactly one second (2 Output Compare Register)
                     // Speedup: 10 ms = 312.5 -> 100 Hz

   TIMSK3 |= 0x02;   // Enable output compare match ints
   sei();            // Enable interrupts

   //Set correct ADC Reference
   analogReference(EXTERNAL);

   // Initialize Buttons
   initButton();
   
   // Initialize Display
   initDisplay();
   
   // Initialize LEDs
   initLEDs();

   // Initialize state machine
   stm_entryFlag = TRUE;
   stm_exitFlag = FALSE;
   stm_newState = STM_STATE_STARTUP;
   stm_actState = STM_STATE_STARTUP;

   // Initialize Serial Port
   Serial.begin(UART_SPEED);
   
   pinMode(SPI_CS_SD_PIN, OUTPUT);
   digitalWrite(SPI_CS_SD_PIN, HIGH); // Very important! Without this command, the SPI-Bus is undefined.
   
   // SPI Poti
   digitalPotInit();

}


// Loop **********************************************************
// The loop function runs over and over aDamping forever
void loop() {

   updateButtonHandler(); // Polling
 
   switch (stm_actState)
   {
      //==============================================================================
      // STM_STATE_STARTUP
      //==============================================================================
      case STM_STATE_STARTUP:

      // Entry action
      if (stm_entryFlag == TRUE)
      {
         #ifdef DEBUG
            Serial.println(F("Entered STM_STATE_STARTUP"));
         #endif
         startup(); // Welcome screen: Display and serial port
         stm_exitFlag = TRUE;
         stm_newState = STM_STATE_CONFIGURATION;

         stm_entryFlag = FALSE;
      }

      if (stm_exitFlag == TRUE)
      {
         // do exit action
         clearButtonAllFlags();
         stm_exitFlag = FALSE;       
         stm_actState = stm_newState;
         stm_entryFlag = TRUE;
      }
   break;
    
      //==============================================================================
      // STM_STATE_CONFIGURATION
      //==============================================================================
      case STM_STATE_CONFIGURATION:         /// Configuration of DMM

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_CONFIGURATION"));
            #endif
            displayTitle("Config");
            displayCommand1("Config: Press Enter");
            displayCommand2("Next:   Press Down");

            stm_entryFlag = FALSE;
         }

         // Start application?
         if (getButtonStateEnter())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Enter"));
            #endif
            DMMconfig();
         }

         // State handler
         if(getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_DIY;
         }
         else if (getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_VOLTAGE_MEASUREMENT;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         }

      break;
      
      //==============================================================================
      // STM_STATE_VOLTAGE_MEASUREMENT
      //==============================================================================
      case STM_STATE_VOLTAGE_MEASUREMENT:   /// Starts Voltage Measurement

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_VOLTAGE_MEASUREMENT"));
            #endif
            displayTitle("Voltage");
            displayCommand1("Enter: Change Gain");
            displayCommand2("");
            
            stm_entryFlag = FALSE;
         }

         if (runMeasurement == 1) // Interrupt generated by timer
         {
            runMeasurement = 0;
            measurement = getVoltageV( voltageMode );
            displayValues(measurement  ,"V");
            LEDBar( measureVoltage() );
         }
         
         
         if(getButtonStateEnter())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Enter"));
            #endif
            if (voltageMode == LOW_RANGE)
            {
               displayCommand2("HIGH_RANGE");
               digitalPotWrite(COMMAND1, dValuePotiHigh); // TBD
               voltageMode = HIGH_RANGE;
               Serial.println(F("Set to HIGH_RANGE"));
            }
            else
            {
               displayCommand2("LOW_RANGE");
               digitalPotWrite(COMMAND1, dValuePotiLow); // TBD
               voltageMode = LOW_RANGE;
               Serial.println(F("Set to LOW_RANGE"));
            }

         }


         // State handler
         if (getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_CONFIGURATION;
         }
         else if (getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_VOLTAGE_OSCILLOSCOPE;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         }
         
      break;
      
      //==============================================================================
      // STM_STATE_VOLTAGE_OSCILLOSCOPE
      //==============================================================================
      case STM_STATE_VOLTAGE_OSCILLOSCOPE:   /// Starts Voltage Measurement

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_VOLTAGE_OSCILLOSCOPE"));
            #endif
            displayTitle("Voltage");
            displayCommand1("");
            displayCommand2("");
            
            stm_entryFlag = FALSE;
         }

         if (runMeasurement == 1) // Interrupt generated by timer
         {
            runMeasurement = 0;
            displayOscilloscope( measureVoltage() );
         }
         
         if(getButtonStateEnter())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Enter"));
            #endif
            if (voltageMode == LOW_RANGE)
            {
               displayCommand2("HIGH_RANGE");
               digitalPotWrite(COMMAND1, dValuePotiHigh); // TBD
               voltageMode = HIGH_RANGE;
               Serial.println(F("Set to HIGH_RANGE"));
            }
            else
            {
               displayCommand2("LOW_RANGE");
               digitalPotWrite(COMMAND1, dValuePotiLow); // TBD
               voltageMode = LOW_RANGE;
               Serial.println(F("Set to LOW_RANGE"));
            }

         }


         // State handler
         if (getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_VOLTAGE_MEASUREMENT;
         }
         else if (getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_VOLTAGE_UART;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         }
         
      break;
      
      //==============================================================================
      // STM_STATE_VOLTAGE_UART
      //==============================================================================
      case STM_STATE_VOLTAGE_UART:   /// Starts Voltage Measurement

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_VOLTAGE_UART"));
            #endif
            displayTitle("Voltage");
            displayCommand1("See Terminal for values");
            #ifdef CSV_ENABLE
               displayCommand2("CSV Output enabled");
            #else
               displayCommand2("Only Voltage values");
            #endif

            counter = 0;
            
            stm_entryFlag = FALSE;
         }

         if (runMeasurement == 1) // Interrupt generated by timer
         {
            ADCvalue = measureVoltage();
            runMeasurement = 0;
            LEDBar( ADCvalue );
            measurement = getVoltageV( voltageMode );

         #ifdef CSV_ENABLE
            Serial.print(counter);
            Serial.print(",");
            Serial.print(ADCvalue);
            Serial.print(",");
            Serial.println(measurement, DECIMAL_PLACES_UART);
         #else
            Serial.println(measurement, DECIMAL_PLACES_UART);
         #endif
            
         }
         
         if(getButtonStateEnter())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Enter"));
            #endif
            if (voltageMode == LOW_RANGE)
            {
               displayCommand2("HIGH_RANGE");
               digitalPotWrite(COMMAND1, dValuePotiHigh); // TBD
               voltageMode = HIGH_RANGE;
               Serial.println(F("Set to HIGH_RANGE"));
            }
            else
            {
               displayCommand2("LOW_RANGE");
               digitalPotWrite(COMMAND1, dValuePotiLow); // TBD
               voltageMode = LOW_RANGE;
               Serial.println(F("Set to LOW_RANGE"));
            }

         }


         // State handler
         if (getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_VOLTAGE_OSCILLOSCOPE;
         }
         else if (getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_CURRENT_MEASUREMENT;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         }
         
      break;
      
      
      
      
      //==============================================================================
      // STM_STATE_CURRENT_MEASUREMENT
      //==============================================================================
      case STM_STATE_CURRENT_MEASUREMENT:   /// Starts Current Measurement

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_CURRENT_MEASUREMENT"));
            #endif
            displayTitle("Current");
            displayCommand1("Change Output:");
            displayCommand2("Press Enter");
            stm_entryFlag = FALSE;
         }

         // Timer interrupt
         if (runMeasurement == 1)
         {
            runMeasurement = 0;
            measurement = getCurrentmA();
            ADCvalue = measureCurrent();
            
            if ( currentMode == DISPLAY_OUTPUT)
            {
               
               displayValues(measurement  ,"mA");
               LEDBar( ADCvalue );  
            }
            else
            {
               LEDBar( ADCvalue );
               Serial.print(counter);
               Serial.print(",");
               Serial.print( ADCvalue );
               Serial.print(",");
               Serial.println(measurement, DECIMAL_PLACES_UART);    
            }
         }

         if(getButtonStateEnter())
         {

            if (currentMode == DISPLAY_OUTPUT)
            {
               currentMode = CSV_OUTPUT;
               displayCommand2("CSV");
               Serial.println(F("Set Mode to CSV"));
            }
            else
            {
               currentMode = DISPLAY_OUTPUT; 
               displayCommand2("Display");
               Serial.println(F("Set Mode to Display"));               
            }            
         }


         // State handler
         if(getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_VOLTAGE_MEASUREMENT;
         }
         else if(getButtonStateDown())
         {
           #ifdef DEBUG
             Serial.println(F("Buttonflag Down"));
           #endif
           stm_exitFlag = TRUE;
           stm_newState = STM_STATE_LED_TEST;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         }
      break;
      
      //==============================================================================
      // STM_STATE_RGB_TEST
      //==============================================================================
      case STM_STATE_LED_TEST:              /// Starts RGB LED Test

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_RGB_TEST"));
            #endif
            displayTitle("LED Test");
            displayCommand1("Enter: Start Test");
            displayCommand2("Danger! Very Bright");

            stm_entryFlag = FALSE;
         }

         if(getButtonStateEnter())
         {
            RGBTest();
            LEDTest();
         }

         // State handler
         if(getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_CURRENT_MEASUREMENT;
         }
         else if(getButtonStateDown())
         {
           #ifdef DEBUG
             Serial.println(F("Buttonflag Down"));
           #endif
           stm_exitFlag = TRUE;
           stm_newState = STM_STATE_POWER_TEST;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         }      
      break;
      

      //==============================================================================
      // STM_STATE_POWER_TEST
      //==============================================================================
      case STM_STATE_POWER_TEST:                  /// Starts Power test (switch on all LEDs, white screen)

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_POWER_TEST"));
            #endif
            displayTitle("Power Test");
            displayCommand1("Enter: Start Test");
            displayCommand2("Danger! Very Bright");
            stm_entryFlag = FALSE;
         }

         if(getButtonStateEnter())
         {
            FullPower(); // Blocks main loop for 20 seconds
         }
         
         // State handler
         if(getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_LED_TEST;
         }
         else if(getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_NTC_TEST;
         }

        
         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         } 
        
      break;
      
      //==============================================================================
      // STM_STATE_NTC_TEST
      //==============================================================================
      case STM_STATE_NTC_TEST:   /// Do it yourself part

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_NTC_TEST"));
            #endif
            displayTitle("NTC Test");
            displayCommand1("Enter: Start Test");
            stm_entryFlag = FALSE;
         }

         if(getButtonStateEnter())
         {
            displayValues( measureTemperature(), "ADC" );
         }
         
         // State handler
         if(getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_POWER_TEST;
         }
         else if(getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_DIY;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         } 
        
      break;
      

      //==============================================================================
      // STM_STATE_DIY
      //==============================================================================
      case STM_STATE_DIY:   /// Do it yourself part

         // Entry action
         if (stm_entryFlag == TRUE)
         {
            #ifdef DEBUG
               Serial.println(F("Entered STM_STATE_DIY"));
            #endif
            displayTitle("DIY");
            displaySubTitle("Subtitle");
            displayCommand1("CMD1");
            displayCommand2("CMD2");
            stm_entryFlag = FALSE;
         }
         
         
         if(getButtonStateEnter())
         {
            // Enter pressed-> Action?
         }
         
         // State handler
         if(getButtonStateUp())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Up"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_NTC_TEST;
         }
         else if(getButtonStateDown())
         {
            #ifdef DEBUG
               Serial.println(F("Buttonflag Down"));
            #endif
            stm_exitFlag = TRUE;
            stm_newState = STM_STATE_CONFIGURATION;
         }

         if (stm_exitFlag == TRUE)
         {
            // do exit action
            clearButtonAllFlags();
            stm_exitFlag = FALSE;
            stm_actState = stm_newState;
            stm_entryFlag = TRUE;
         } 
        
      break;
        
      
      //==============================================================================
      // ERROR
      //==============================================================================
       default:
         //Error: State not defined
         stm_actState = STM_STATE_CONFIGURATION;
       break;
   }

   
}




// ################################
// ###### DMMconfig()        ######
// ################################
void DMMconfig()
{
   if (!Serial)
   {
      displayCommand1("no serial port detected");
      displayCommand2("Check USB cable");
      return;
   }
   displayCommand1("Serial port detected");
   displayCommand2("See terminal");
  
   Serial.println("Configuration");
   Serial.println(SEPARATOR);  
   Serial.println("Enter damping Du,high (float)");
   Serial.print(EEPROM_OLD_VAL_MSG);
   Serial.println(getHighDampingVoltageMeasurement(), 5); 
   // Serial okay?
   if( !CheckSerial() ) return;
    
   setHighDampingVoltageMeasurement(Serial.parseFloat()); // Set high Damping
   Serial.print(EEPROM_FEEDBACK_MSG);
   Serial.println(getHighDampingVoltageMeasurement(), 5);
   Serial.println(SEPARATOR);  

   Serial.println(F("Enter damping Du,low (float)"));
   Serial.print(EEPROM_OLD_VAL_MSG);
   Serial.println(getLowDampingVoltageMeasurement(), 5); 
   
   if( !CheckSerial() ) return;
   
   setLowDampingVoltageMeasurement(Serial.parseFloat());
   Serial.print(EEPROM_FEEDBACK_MSG);
   Serial.println(getLowDampingVoltageMeasurement(), 5);
   Serial.println(SEPARATOR);  
   
   Serial.println("Enter D Vaule Poti High (uint8_t)");
   Serial.print(EEPROM_OLD_VAL_MSG);
   Serial.println(dValuePotiHigh, 1);
   
   if( !CheckSerial() ) return;
   dValuePotiHigh = Serial.parseInt();
   Serial.print(EEPROM_FEEDBACK_MSG);
   Serial.println(dValuePotiHigh, 1);
   Serial.println(SEPARATOR); 
   
   Serial.println("Enter D Vaule Poti Low (uint8_t)");
   Serial.print(EEPROM_OLD_VAL_MSG);
   Serial.println(dValuePotiLow, 1);
   
   if( !CheckSerial() ) return;
   dValuePotiLow = Serial.parseInt();
   Serial.print(EEPROM_FEEDBACK_MSG);
   Serial.println(dValuePotiLow, 1);
   Serial.println(SEPARATOR);  
   
   
   Serial.println("Enter Gi (float)");
   Serial.print(EEPROM_OLD_VAL_MSG);
   Serial.println(getGainCurrentMeasurement(), 5);
   
   if( !CheckSerial() ) return;
   
   setGainCurrentMeasurement(Serial.parseFloat());
   Serial.print(EEPROM_FEEDBACK_MSG);
   Serial.println(getGainCurrentMeasurement(), 5);
   Serial.println(SEPARATOR);    

   Serial.println(F("Enter Shunt Value in Ohm (float)"));
   Serial.print(EEPROM_OLD_VAL_MSG);
   Serial.println(getShuntValue(), 5);
   
   if( !CheckSerial() ) return;
   
   setShuntValue(Serial.parseFloat());
   Serial.print(EEPROM_FEEDBACK_MSG);
   Serial.println(getShuntValue(), 5);
   Serial.println(SEPARATOR);  
   Serial.println(F("Configuration done"));
   Serial.println(SEPARATOR);   

   // Save in EEPROM
   EEPROM.put(EEPROM_ADDR_HIGH_VOLTAGE,      getHighDampingVoltageMeasurement());
   EEPROM.put(EEPROM_ADDR_LOW_VOLTAGE,       getLowDampingVoltageMeasurement());
   EEPROM.put(EEPROM_ADDR_HIGH_RESISTANCE,   dValuePotiHigh); // kOhm
   EEPROM.put(EEPROM_ADDR_LOW_RESISTANCE,    dValuePotiLow);  // kOhm
   EEPROM.put(EEPROM_ADDR_CURRENT,           getGainCurrentMeasurement());
   EEPROM.put(EEPROM_ADDR_SHUNT,             getShuntValue());
   //EEPROM.put(EEPROM_ADDR_CODE,              code);

   Serial.println(F("Configuration saved in EEPORM"));
  
  #ifdef DEBUG
      Serial.println(F("Saved EEPROM Data:"));
      for (int addr = 0; addr < EEPROM.length(); addr++)
      {
         int value = EEPROM.read(addr);
         Serial.print(addr);
         Serial.print("\t");
         Serial.print(value, DEC);
         Serial.println();
      }  
   #endif  
   delay(1000);
}

// ----------------------------------------------------------------------------
/// \brief     Startup Sequence
/// \detail    Shows wellcome screen
/// \warning   
/// \return    if finished: return 1
/// \todo
void startup()
{
   float uRangeHighVoltage;
   float uRangeLowVoltage;
   float iRangeCurrent;
   float shuntValue;
   
   Serial.println(F("...:::..."));
   Serial.print(F("PASE "));
   Serial.println(YEAR);
   Serial.println(F("EuR Rules!")); // Do NOT change this ;-)
   Serial.println(F("........."));
   Serial.println(F("Congratulations"));
   Serial.println(F("You Made It Work")); 
   Serial.println(SEPARATOR);   
   
   displayTitle("Testing");
   displaySubTitle(":-) PASE :-)");
   displayCommand1(SOFTWARE_VERSION);
   displayCommand2("NTB Buchs");
   
   delay(3000);
   
   Serial.println(F("Offset Calibration"));
   offsetCalibration();
   currentZeroCorretion();
   Serial.print(F("Offset: "));
   Serial.print(readOffset(), 5);
   Serial.println(F(" V"));
   Serial.print(F("Offset ADC: "));
   Serial.println(readOffsetADC());
   Serial.println(F("Offset Calibration done"));
   Serial.println(F("Restoring Configuration"));
   // Restore configuration
   EEPROM.get(EEPROM_ADDR_HIGH_VOLTAGE,      uRangeHighVoltage);
   EEPROM.get(EEPROM_ADDR_LOW_VOLTAGE,       uRangeLowVoltage);
   EEPROM.get(EEPROM_ADDR_HIGH_RESISTANCE,   dValuePotiHigh); // kOhm
   EEPROM.get(EEPROM_ADDR_LOW_RESISTANCE,    dValuePotiLow);  // kOhm
   EEPROM.get(EEPROM_ADDR_CURRENT,           iRangeCurrent);
   EEPROM.get(EEPROM_ADDR_SHUNT,             shuntValue);
   //EEPROM.get(EEPROM_ADDR_CODE,              code);

   // Save
   setHighDampingVoltageMeasurement(uRangeHighVoltage);
   setLowDampingVoltageMeasurement(uRangeLowVoltage);
   setGainCurrentMeasurement(iRangeCurrent);
   setShuntValue(shuntValue);
   
   digitalPotWrite(COMMAND1, dValuePotiHigh); // Set high value as default

   Serial.println(F("Restoring Configuration DONE"));
   Serial.println(SEPARATOR);   
}


// ----------------------------------------------------------------------------
/// \brief     CheckSerial
/// \detail    User has x seconds time to enter values
/// \warning   
/// \return    uint8_t 1: Okay, 0: error
/// \todo
static uint8_t CheckSerial()
{
   counter = 0;
   while(Serial.available() == 0) // Not available
   {
      if ( counter > SERIAL_TIMEOUT )
      {
         displayCommand1("Serial port TimeOut");
         displayCommand2("Please enter Values faster");
         Serial.println(F("Timeout Serial Port"));
         return 0; // Error, return
      }
      
      if( !Serial )
      {
         displayCommand1("Serial port Disconnected");
         displayCommand2("Check USB cable");
         return 0;
      } 
      
   }
   
   return 1;
}


// ################################
// ###### NTCTest()        ######
// ################################
  // A = - 17.6439
  // B = 6022.726
  // C = - 203157
  // D = - 7.183526E+06
  // A1 = 3.354016E-03
  // B1 = 2.264097E-04
