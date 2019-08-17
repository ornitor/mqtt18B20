
/*
 *   Alterna estado do LED da placa do NodeMCU ESP8266
 *   atraves de um broker MQTT
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#define MASTER_BROKER
#include "sensors-18B20.h"
#include "broker.h"



void setup_wifi() 
{
        WiFi.begin(ssid, password);
        Serial.println("Conectando WiFi:");
        for(int i=1; WiFi.status() != WL_CONNECTED; i++) {
                  delay(500);
                  if(i%80==0)
                          Serial.println(i);
                  Serial.print(".");
                  }
        Serial.print("\nWiFi conectado IP: ");
        Serial.println(WiFi.localIP());
}

void setup_broker() 
{
        delay(10);
        client.setServer(mqttServer, mqttPort);
        client.setCallback(minhaFuncaoSubscritora);
        Serial.print("Conectando ");
        Serial.print(mqttServer);
        Serial.print(":");
        Serial.println(mqttPort);
        conectaBroker(mqttUser, mqttPassword ) ;
        client.subscribe("#");  //  "#" significa subscribe todas as mensagens
}


void minhaFuncaoSubscritora(char* topic, byte* payload, unsigned int length) 
{
        Serial.print("Chegou mensagem [");  // avisando recebimento de qualquer mensagem
        Serial.print(topic);
        Serial.print("] ");
        for (int i = 0; i < length; i++) {
              Serial.print((char)payload[i]);
              }
        Serial.println();
        if(strcmp(topic,"LED" )==0){   // interpretando a mensagem especifica para o LED
                if ((char)payload[0] == '1') {
                        digitalWrite(BUILTIN_LED, LOW);   // Liga o LED da placa (no NodeMCU nivel Low liga o led))
                }
                else {
                        digitalWrite(BUILTIN_LED, HIGH);  // Desiga o LED da placa (no NodeMCU nivel High liga o led))
                }
        } 
}

void conectaBroker(char* user, char* password) 
{
      while (!client.connected()) {   // fica em loop ate conectar
            Serial.print("... ");
            String clientId = "ETH0";
            clientId += String(random(0xffff), HEX);
            if (client.connect(clientId.c_str(), user,password)) {
                Serial.println("Conectado.");
            } else {
                Serial.print("Falhou, rc=");
                Serial.print(client.state());
                Serial.println(" retentando em 5 seconds");
                delay(5000);  // espere 5 segundos antes de retentar
            } 
        }
}
