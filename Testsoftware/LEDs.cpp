#include "LEDs.h"



// Create RGB strip object
static Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_RGB_LED, RGB_MANAGEMENT_PIN, NEO_GRB + NEO_KHZ800);

// ----------------------------------------------------------------------------
/// \brief     Initialize all LEDs (incl. RGBs)
/// \detail    
/// \warning   
/// \return   
/// \todo      
///
void initLEDs()
{
   // LEDs
   pinMode(LED1_PIN, OUTPUT);
   pinMode(LED2_PIN, OUTPUT);
   pinMode(LED3_PIN, OUTPUT);
   
   // RBG LEDs
   strip.begin();
   Serial.println(F("Init RGB LEDs: All RGB LEDs off"));
   strip.setBrightness(BRIGHTNESS);  // 0 ...255
   
   LEDOff();
}



// ----------------------------------------------------------------------------
/// \brief     Set Green LED
/// \detail    Switch on green LED
/// \warning   
/// \return   
/// \todo      
///
void setGreenLED3()
{
   digitalWrite(LED3_PIN, HIGH);
   
}

// ----------------------------------------------------------------------------
/// \brief     Reset Green LED
/// \detail    Switch off green LED
/// \warning   
/// \return   
/// \todo      
///
void resetGreenLED3()
{
   digitalWrite(LED3_PIN, LOW);
   
}

// ----------------------------------------------------------------------------
/// \brief     Toggle Green LED
/// \detail       
/// \warning   
/// \return   
/// \todo      
///
void toggleGreenLED3() // TBD: LED1_PIN?
{
   if( digitalRead(LED3_PIN) == HIGH)
   {
      digitalWrite(LED3_PIN, LOW);
   }
   else
   {
      digitalWrite(LED3_PIN, HIGH);
   }
      
}


// ----------------------------------------------------------------------------
/// \brief     Set Red LED
/// \detail    Switch on green LED
/// \warning   
/// \return   
/// \todo      
///
void setRedLED()
{
   digitalWrite(LED1_PIN, HIGH);

}

// ----------------------------------------------------------------------------
/// \brief     Reset Red LED
/// \detail    Switch off green LED
/// \warning   
/// \return   
/// \todo      
///
void resetRedLED()
{
   digitalWrite(LED1_PIN, LOW);
   
}




// ----------------------------------------------------------------------------
/// \brief     RGB Test
/// \detail    Tests all RGB LEDs.
/// \warning   
/// \return   
/// \todo      
///
void RGBTest()
{
   char buffer[20];
   Serial.println(F("------------------"));
   Serial.println(F("Starting RGBTest"));
   Serial.println(F("------------------"));
   Serial.println(F("RGB Rainbow"));

   rainbowCycle(10);
   delay(1000);
  
   Serial.println(F("------------------"));
   Serial.println(F("All off"));

   for(uint8_t i = 0; i < strip.numPixels() ; i++)
   {
    strip.setPixelColor(i, 0, 0, 0);
   }
   strip.show();
   delay(1000);
  
   // All red
   for(uint8_t i = 0; i < strip.numPixels() ; i++)
   {
      strip.setPixelColor(i, RGB_RED);
      sprintf(buffer, "RGB LED%d red", i);
      Serial.println(buffer);
      
      strip.show();
      delay(500);
   }
      // All green
   for(uint8_t i = 0; i < strip.numPixels() ; i++)
   {
      strip.setPixelColor(i, RGB_GREEN);
      sprintf(buffer, "RGB LED%d green", i);
      Serial.println(buffer);
      
      strip.show();
      delay(500);
   }
      // All blue
   for(uint8_t i = 0; i < strip.numPixels() ; i++)
   {
      strip.setPixelColor(i, RGB_BLUE);
      sprintf(buffer, "RGB LED%d blue", i);
      Serial.println(buffer);
      strip.show();
      delay(500);
   }
   
   // All white
   for(uint8_t i = 0; i < strip.numPixels() ; i++)
   {
      strip.setPixelColor(i, RGB_WHITE);
      sprintf(buffer, "RGB LED%d white", i);
      Serial.println(buffer);
      strip.show();
      delay(500);
   }
   
   Serial.println(F("------------------"));
   Serial.println(F("All RGB LEDs off"));
   for(uint8_t i = 0; i < strip.numPixels() ; i++)
   {
    strip.setPixelColor(i, RGB_BLACK);
   }
   strip.show();
   delay(1000);
   strip.show();
   delay(1000);
   Serial.println(F("RGB Test finished"));
}

// ----------------------------------------------------------------------------
/// \brief     LED Test
/// \detail    Tests all LEDs (without RGBs). Maximum 3 LEDs supported
/// \warning   
/// \return   
/// \todo      
///
void LEDTest()
{
   Serial.println(F("------------------"));
   Serial.println(F("Starting LEDTest"));
   Serial.println(F("------------------"));
   Serial.println(F("LED Test started"));
   Serial.println(F("All LEDs off"));
   digitalWrite(LED1_PIN, LOW);
   digitalWrite(LED2_PIN, LOW);
   digitalWrite(LED3_PIN, LOW);
   delay(1000);

   Serial.println(F("------------------"));
   Serial.println(F("LED1 on"));
   digitalWrite(LED1_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(1000);

   Serial.println(F("------------------"));
   Serial.println(F("LED2 on"));
   digitalWrite(LED2_PIN, HIGH);
   delay(1000);

   Serial.println(F("------------------"));
   Serial.println(F("LED3 on"));
   digitalWrite(LED3_PIN, HIGH);
   delay(1000);

   Serial.println(F("All LEDs off"));

   digitalWrite(LED1_PIN, LOW);
   digitalWrite(LED2_PIN, LOW);
   digitalWrite(LED3_PIN, LOW);
   delay(1000);
   Serial.println(F("LED Test finished"));
}

// ----------------------------------------------------------------------------
/// \brief     Turns all LEDs on
/// \detail    RGB LEDs: White, all other LEDs on
/// \warning   
/// \return   
/// \todo      
///
void LEDFullPower()
{
   // LEDs
   Serial.println(F("All LEDs on"));
   digitalWrite(LED1_PIN, HIGH);
   digitalWrite(LED2_PIN, HIGH);
   digitalWrite(LED3_PIN, HIGH);
   
   // RBG LEDs on, white, full
   Serial.println(F("------------------"));
   Serial.println(F("All RGB LEDs white"));
   for (uint8_t i = 0; i < strip.numPixels(); i++) 
   {
      strip.setPixelColor(i, RGB_WHITE);
   }
   strip.show();
   
}

// ----------------------------------------------------------------------------
/// \brief     Turns all LEDs off
/// \detail    RBG and "normal" LEDs off
/// \warning   
/// \return   
/// \todo      
///
void LEDOff()
{
   // LEDs
   Serial.println(F("All LEDs off"));
   digitalWrite(LED1_PIN, LOW);
   digitalWrite(LED2_PIN, LOW);
   digitalWrite(LED3_PIN, LOW);
   
   // RBG LEDs off
   Serial.println(F("------------------"));
   Serial.println(F("All RGB LEDs off"));
   for (uint8_t i = 0; i < strip.numPixels(); i++) 
   {
      strip.setPixelColor(i, RGB_BLACK);
   }
   strip.show();
   
}

// ----------------------------------------------------------------------------
/// \brief     RGB LED Bar
/// \detail    Switchs on RGB LEDs according to the ADC value. The constant RGB_STEPSIZE
///				defines the step between the different colors.
/// \warning   
/// \return    
/// \todo      At the moment, just 4 RGB LEDs in ascending order are supported.
///
void LEDBar(uint16_t ADCvalue)
{

   for(int i = 0; i < strip.numPixels() ; i++)
   {
      strip.setPixelColor(i, RGB_BLACK); // Switch off
   }
   
   uint16_t offsetADC = readOffsetADC();
   // LED 4 ++
   // LED 3 +
   // LED 2 -
   // LED 1 --
   // All off: 0 V
   
   // If order differs: See defines in LEDs.h file
   
   
   if (ADCvalue > offsetADC) // Positive voltage
   {
      if(ADCvalue < (offsetADC + RGB_STEPSIZE/2) )
      {
         // All off
      }
      else if (ADCvalue < (offsetADC + RGB_STEPSIZE/2 + RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED3, RGB_GREEN); 
      }
      else if (ADCvalue < (offsetADC + RGB_STEPSIZE/2 + 2*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED3, RGB_BLUE); 
      }
      else if (ADCvalue < (offsetADC + RGB_STEPSIZE/2 + 3*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED3, RGB_RED); 
      }
      else if (ADCvalue < (offsetADC + RGB_STEPSIZE/2 + 4*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED3, RGB_RED); 
         strip.setPixelColor(LED4, RGB_GREEN); 
      }
      else if (ADCvalue < (offsetADC + RGB_STEPSIZE/2 + 5*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED3, RGB_RED); 
         strip.setPixelColor(LED4, RGB_BLUE);
      }
      else
      {
         strip.setPixelColor(LED3, RGB_RED); 
         strip.setPixelColor(LED4, RGB_RED);  
      }
   }
   else // Negative voltage
   {
      if(ADCvalue > (offsetADC - RGB_STEPSIZE/2) )
      {
         // All off
      }
      else if (ADCvalue > (offsetADC - RGB_STEPSIZE/2 - RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED2, RGB_GREEN); 
      }
      else if (ADCvalue > (offsetADC - RGB_STEPSIZE/2 - 2*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED2, RGB_BLUE); 
      }
      else if (ADCvalue > (offsetADC - RGB_STEPSIZE/2 - 3*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED2, RGB_RED); 
      }
      else if (ADCvalue > (offsetADC - RGB_STEPSIZE/2 - 4*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED2, RGB_RED); 
         strip.setPixelColor(LED1, RGB_GREEN); 
      }
      else if (ADCvalue > (offsetADC - RGB_STEPSIZE/2 - 5*RGB_STEPSIZE) )
      {
         strip.setPixelColor(LED2, RGB_RED); 
         strip.setPixelColor(LED1, RGB_BLUE);
      }
      else
      {
         strip.setPixelColor(LED2, RGB_RED); 
         strip.setPixelColor(LED1, RGB_RED);  
      }
      
   }
   

   strip.show();
}








// ----------------------------------------------------------------------------
/// \brief     Helper Function for RGB test
/// \detail    Input a value 0 to 255 to get a color value.
///			   The colours are a transition r - g - b - back to r.
/// \warning   
/// \return   
/// \todo      
///
static uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Slightly different, this makes the rainbow equally distributed throughout
static void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}