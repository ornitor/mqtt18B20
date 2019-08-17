/*
    Esta sketch:
      le temperaturas 18B20 conectado num barramento
      SOMENTE TEMPERATURAS
      NAO FOI VALIDADO A MULTIPLICAÇAO DOS pids
*/


#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "sensors-18B20.h"
#include "broker.h"


void setup() 
{
      delay(1000);
      pinMode(BUILTIN_LED, OUTPUT);     // Inicializa pino BUILTIN_LED como output
      Serial.begin(115200);
      Serial.println("\r\n\r\n***************************\r\nMonitor de Temperatura IoT\r\nBom dia!\r\n");
      setup_wifi();
      setup_broker();
      setupTemp18B20();

}

void loop()    /// loop faz muito pouco: reconecta se necessario e chama o loop() do cliente mqtt
{
        if (!client.connected()) 
               conectaBroker( mqttUser, mqttPassword );
        client.loop();   
        LE18B20();
        sendLine();
        pub_temperaturas(2000);
        delay(10000);
}

char msg[50];
char topic[50];

void pub_temperaturas(long delayT)
{
       for(int i=0;i<ntemp;i++){
             snprintf (topic, 50, "temp%d", i);        
             snprintf (msg, 50, "%5.2f", current[i]);        
             client.publish(topic,msg);
             Serial.print(topic) ;
             Serial.print(": ") ;
             Serial.println(msg) ;
             delay(delayT);
             //current_1[i] = current[i] ;
            }
}
