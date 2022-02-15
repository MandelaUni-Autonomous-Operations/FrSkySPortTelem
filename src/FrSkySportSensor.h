/*
  FrSky sensor base class for Teensy LC/3.x/4.x, ESP8266, ATmega2560 (Mega) and ATmega328P based boards (e.g. Pro Mini, Nano, Uno)
  (c) Pawelsky 20210509
  Not for commercial use
*/

#ifndef _FRSKY_SPORT_SENSOR_H_
#define _FRSKY_SPORT_SENSOR_H_

#include "Arduino.h"
#include "FrSkySportSingleWireSerial.h"

#define SENSOR_NO_DATA_ID 0x0000
#define SENSOR_EMPTY_DATA_ID 0xFFFF // Data ID of an empty data frame

class FrSkySportSensor
{
  public:
    // IDs of sensors (including the CRC)
    enum SensorId { ID1  = 0x00, ID2  = 0xA1, ID3  = 0x22, ID4  = 0x83, ID5  = 0xE4, ID6  = 0x45, ID7  = 0xC6,
                    ID8  = 0x67, ID9  = 0x48, ID10 = 0xE9, ID11 = 0x6A, ID12 = 0xCB, ID13 = 0xAC, ID14 = 0x0D,
                    ID15 = 0x8E, ID16 = 0x2F, ID17 = 0xD0, ID18 = 0x71, ID19 = 0xF2, ID20 = 0x53, ID21 = 0x34,
                    ID22 = 0x95, ID23 = 0x16, ID24 = 0xB7, ID25 = 0x98, ID26 = 0x39, ID27 = 0xBA, ID28 = 0x1B, ID_IGNORE = 0xFF };
    // virtual function for sending a byte of data 
    virtual uint16_t send(FrSkySportSingleWireSerial& serial, uint8_t id, uint32_t now);
    // virtual function for reading sensor data 
    virtual uint16_t decodeData(uint8_t id, uint16_t appId, uint32_t data);

  protected:
    FrSkySportSensor(SensorId id);
    static void sendSingleData(FrSkySportSingleWireSerial& serial, uint16_t dataIdConst, uint16_t& dataIdRef, uint32_t data, uint32_t dataTimeConst, uint32_t& dataTimeRef, uint32_t now);
    SensorId sensorId;
    uint8_t sensorDataIdx;

  private:
    FrSkySportSensor();
};

#endif // _FRSKY_SPORT_SENSOR_H_
