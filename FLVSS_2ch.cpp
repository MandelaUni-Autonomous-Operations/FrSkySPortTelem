/*
  Adapted from FrSky S-Port Telemetry Decoder library example
  by Pawel Spychalski
  
  Note that you need Teensy LC/3.x/4.x, ESP8266, ATmega2560 (Mega) or ATmega328P based (e.g. Pro Mini, Nano, Uno), the FrSkySportDecoder library and the MAVLink C library for this script to work
*/

// Uncomment the #define below to enable internal polling of data.
// Use only when there is no device in the S.Port chain (e.g. S.Port capable FrSky receiver) that normally polls the data.
#define POLLING_ENABLED

#include "FrSkySportSensor.h"
#include "FrSkySportSensorFlvss.h"
#include "FrSkySportSensorSp2uart.h"
#include "FrSkySportSingleWireSerial.h"
#include "FrSkySportDecoder.h"
#include "SoftwareSerial.h"

#define bRate 115200

FrSkySportSensorFlvss flvss1(FrSkySportSensor::ID1);                            // Create FLVSS sensor with default ID             
FrSkySportSensorFlvss flvss2(FrSkySportSensor::ID2);                            // Create FLVSS sensor with default ID 
                  
#ifdef POLLING_ENABLED
  #include "FrSkySportPollingSimple.h"
  FrSkySportDecoder decoder(new FrSkySportPollingSimple()); // Create telemetry object with simple polling
#else
  FrSkySportDecoder decoder;                           // Create decoder object without polling
#endif

// Instantiate message variable and preload with impossible values
uint16_t decodeResult;

// Channel/ID 1 : FLVSS
float ch1Volts_cell1 = -10;
float ch1Volts_cell2 = -10;
float ch1Volts_cell3 = -10;
float ch1Volts_cell4 = -10;

// Channel/ID 2 : FLVSS 
float ch2Volts_cell1 = -10;
float ch2Volts_cell2 = -10;
float ch2Volts_cell3 = -10;
float ch2Volts_cell4 = -10;


// Timer variables
int lastSet, curStopwatch;
int loopTimer = 1000; // 1 sec update rate

void setup()
{
  decoder.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_2, &flvss1, &flvss2);
  Serial.begin(bRate);
  lastSet = millis();
}

void loop()
{

   // ------------------------------------------Timer Update 
  curStopwatch = millis() - lastSet;
  
  decodeResult = decoder.decode();    // Decodes the data from the FrSky S.Port Sensors
  
  if(curStopwatch >= loopTimer){
    // Update variables whenever new sensor data is available
    ch1Volts_cell1 = flvss1.getCell1();
    ch1Volts_cell2 = flvss1.getCell2();
    ch1Volts_cell3 = flvss1.getCell3();
    ch1Volts_cell4 = flvss1.getCell4();
    ch2Volts_cell1 = flvss2.getCell1();
    ch2Volts_cell2 = flvss2.getCell2();
    ch2Volts_cell3 = flvss2.getCell3();
    ch2Volts_cell4 = flvss2.getCell4();
    
    // Timer Reset
    curStopwatch = 0;
    lastSet = millis();
  
    // display values
    Serial.println("-------------------------------");
    Display(1,ch1Volts_cell1,ch1Volts_cell2,ch1Volts_cell3,ch1Volts_cell4);
    Display(2,ch2Volts_cell1,ch2Volts_cell2,ch2Volts_cell3,ch2Volts_cell4);
  }

}

void Display(int ch, float c1, float c2, float c3, float c4){
  Serial.print("Channel ");
  Serial.print(ch); 
  Serial.print(" : ");
  Serial.print(c1);
  Serial.print(" ; ");
  Serial.print(c2);
  Serial.print(" ; ");
  Serial.print(c3);
  Serial.print(" ; ");
  Serial.println(c4);

}
