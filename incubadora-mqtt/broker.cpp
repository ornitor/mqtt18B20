
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

void pub_temperaturas(long delayT);
void pub_extremes(long delayT);


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
        delay(100);
        client.setServer(mqttServer, mqttPort);
        delay(100);
        client.setCallback(minhaFuncaoSubscritora);
        Serial.print("Conectando ");
        Serial.print(mqttServer);
        Serial.print(":");
        Serial.println(mqttPort);
        conectaBroker(mqttUser, mqttPassword , 5) ;
        client.subscribe("#");  //  "#" significa subscribe todas as mensagens
}


void minhaFuncaoSubscritora(char* topic, byte* payload, unsigned int length) 
{
        if(fgVerbose){
              Serial.print("Chegou mensagem [");  // avisando recebimento de qualquer mensagem
              Serial.print(topic);
              Serial.print("] ");
              for (int i = 0; i < length; i++) {
                    Serial.print((char)payload[i]);
                    }
              Serial.println();
        }
        if(strcmp(topic,"LED" )==0){   // so exemplo  LED poisser usado para fins de sinalizaação
                if ((char)payload[0] == '1') {
                        digitalWrite(BUILTIN_LED, LOW);   // Liga o LED da placa (no NodeMCU nivel Low liga o led))
                }
                else {
                        digitalWrite(BUILTIN_LED, HIGH);  // Desiga o LED da placa (no NodeMCU nivel High liga o led))
                }
        } 
        if(strcmp(topic,"setp" )==0){   //  muda o set point 21<>25
                if ((char)payload[0] == '1') {
                        setpoint[1] = 25;   // Liga o LED da placa (no NodeMCU nivel Low liga o led))
                }
                else {
                        setpoint[1] = 21;  // Desiga o LED da placa (no NodeMCU nivel High liga o led))
                }
        } 
        if(strcmp(topic,"atualiza" )==0){   // atende demanda de publicacao de temperatura
                if ((char)payload[0] == '1') {
                        pub_temperaturas(100);
                }
                else {
                         pub_temperaturas(100);
                }
        } 
        if(strcmp(topic,"extreme" )==0){   //  atende demanda de publicacao de maximos e minimos
                if ((char)payload[0] == '1') {
                        pub_extremes(100);
                }
                else {
                        pub_extremes(100);
                }
        } 
        if(strcmp(topic,"pub" )==0){   // interpretando a mensagem especifica para o LED
                if ((char)payload[0] == '1') {
                        fgPub = 1;
                }
                else {
                         fgPub = 0;
                }
        } 
        if(strcmp(topic,"t1" )==0){   // interpretando a mensagem especifica para o LED
                if ((char)payload[0] == '1') {
                        fgPub = 1;
                }
                else {
                         fgPub = 0;
                }
        } 
}



void conectaBroker(char* user, char* password, int n) 
{
     for(int i=0;  i<n && !client.connected();  i++) {   // fica em loop ate conectar
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
