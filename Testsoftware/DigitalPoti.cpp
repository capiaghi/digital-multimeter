// ****************************************************************************
/// \file      DigitalPoti.cpp
///
/// \brief     Driver for AD5271
///
/// \details   RWA = D/256*RWA (RWA = 100 kOhm)
///
/// \author    Christoph Capiaghi, ESA NTB Buchs
///
/// \version   0.1
///
/// \date      20171122
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
#include "DigitalPoti.h"

static SPISettings spiSettings;

// ----------------------------------------------------------------------------
/// \brief     Initialize digital Potentiometer AD5271
/// \detail    Disables wirte protection RDAC register
///            SPI: CPOL = 0, CPHA = 1
/// \warning   
/// \return    
/// \todo      
///
void digitalPotInit()
{
   pinMode(SPI_CS_POT_PIN, OUTPUT);
   digitalWrite(SPI_CS_POT_PIN, HIGH);
   SPI.begin();
   // POTI (CPOL = 0, CPHA = 1) , max 50 MHz
   spiSettings = SPISettings(SPI_FREQ_POTI, MSBFIRST, SPI_MODE1);	
   
   // To enable programming of the RDAC register, the
   // write protect bit (Bit C1), of the control register must first be
   // programmed by loading the serial data input register with
   // Command 7
   digitalPotWrite(COMMAND7, C1);      // 0x1C02
   uint16_t ctrlRegisterData = getCtrlRegister();  // 0x2000 and 0x0000
   
   // Check, if C1 bit is set
   // C1 C0 -> C1 is 1
   if (ctrlRegisterData & (1 << 1) )
   {
      Serial.println("Digital Poti write protection disabled");
   }      
   else
   {
      Serial.println("ERROR: Digital Poti write protection NOT disabled");
   }
   
   Serial.print("SPI Poti Ctrl Register: ");
   printHex(ctrlRegisterData, 4);
   Serial.println("-------");

}

// ----------------------------------------------------------------------------
/// \brief     Writes data to the digital Potentiometer AD5271
/// \detail    
/// \warning   Before sending data remove write protection of the RDAC register
/// \return    uint16_t SDO values
/// \todo      
///
uint16_t digitalPotWrite(uint16_t ctrl, uint16_t data)
{
   
   SPI.beginTransaction(spiSettings);
   // Take the SS pin low to select the chip:
   digitalWrite(SPI_CS_POT_PIN, LOW);
   // Send in the control and data via SPI
   // 0 0 C3 C2 C1 C0 D9 D8 D7 D6 D5 D4 D3 D2 X X
   //     |-- ctrl --|-------------data----------|
   // X = 0
   uint16_t dataBuf = 0;
   uint16_t dataReceived;
   
   // ctrl = 1: Data 0 and Data 1 don't care -> Shift 2x left
   if (ctrl == COMMAND1)
   {
      dataBuf = (ctrl << 10) | (data << 2);
   }
   else
   {
      dataBuf = (ctrl << 10) | data;
   }
   
   Serial.print(F("SPI Poti dataToSend: "));
   printHex(dataBuf, 4);
   
   dataReceived = SPI.transfer16(dataBuf);
   
   // take the SS pin high to de-select the chip:
   digitalWrite(SPI_CS_POT_PIN, HIGH);
   // Stop using the SPI bus.
   // Normally this is called after de-asserting the chip select,
   // to allow other libraries to use the SPI bus
   SPI.endTransaction();
   
   return dataReceived;
}

// ----------------------------------------------------------------------------
/// \brief     Read back control register of the digital Potentiometer AD5271
/// \detail    Sends Command 8 and dummy command 0 to receive data
/// \warning   
/// \return    uint16_t Register content
/// \todo      
///
uint16_t getCtrlRegister()
{
   uint16_t dataReceived;
   digitalPotWrite(COMMAND8, 0);
   dataReceived = digitalPotWrite(COMMAND0, 0);
   
   return dataReceived;
}


void printHex(int num, int precision)
{
   char tmp[16];
   char format[128];
   sprintf(format, "%%.%dX", precision);
   sprintf(tmp, format, num);
   Serial.print("0x");
   Serial.println(tmp);
}
