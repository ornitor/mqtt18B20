/*
    Esta sketch:
      le temperaturas 18B20 conectado num barramento
      SOMENTE TEMPERATURAS
      NAO FOI VALIDADO A MULTIPLICAÇAO DOS pids
*/


#include <OneWire.h>
#include <DallasTemperature.h>

#define MASTER_18B20
#include "sensors-18B20.h"
#include "broker.h"


void setupTemp18B20()
{
        sensors18B20.begin();
        ntemp = sensors18B20.getDeviceCount();
        Serial.print("Quantos: ");Serial.println(ntemp);
        for(int i=0;i<ntemp;i++){
              Serial.print("Device ");
              Serial.print(i);
              Serial.print(":");
              Serial.print(sensors18B20.getAddress(sensorTemp[i], i));
              Serial.print("\t");
              printDallasAddress(sensorTemp[i]);
              Serial.println("");
              sensors18B20.setResolution(sensorTemp[i], TEMPERATURE_PRECISION);
        }   
}


void LE18B20()
{
      sensors18B20.requestTemperatures();
      for(int i=0;i<ntemp;i++){
            float t = sensors18B20.getTempC(sensorTemp[i]);
            if (t > 0 ) temp[i] = t;
            if(temp[i] < tmin[i]) tmin[i] = temp[i];
            if(temp[i] > tmax[i]) tmax[i] = temp[i];
    }
}

void sendLine()
{
      for (int i = 0; i < ntemp; i++) {
              Serial.print(temp[i]);
              Serial.print("\t");
      }
      Serial.print("\n");

}

void printDallasAddress(DeviceAddress deviceAddress)
{
        for (uint8_t i = 0; i < 8; i++){
                // zero pad the address if necessary
                if (deviceAddress[i] < 16) Serial.print("0");
                Serial.print(deviceAddress[i], HEX);
                }
}
