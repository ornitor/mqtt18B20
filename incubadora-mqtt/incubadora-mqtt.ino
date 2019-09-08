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

void pub_temperaturas(long delayT);
void pub_extremes(long delayT);
// Hardware
// barramento onewire no D4 ok 
// roxo D5  amarelo D6   verde D7   azul D8
int driver[5] = {D5,D6,D7,D8};

void setup() 
{
      delay(1000);
      pinMode(BUILTIN_LED, OUTPUT);     // Inicializa pino BUILTIN_LED como output
      pinMode(D5, OUTPUT);
      pinMode(D6, OUTPUT);
      pinMode(D7, OUTPUT);
      pinMode(D8, OUTPUT);
      Serial.begin(115200);
      Serial.println("\r\n\r\n***************************\r\nMonitor de Temperatura IoT\r\nBom dia!\r\n");
      setup_wifi();
      setup_broker();
      setupTemp18B20();
      

}

long iteration = 1;

void loop()    /// loop faz muito pouco: reconecta se necessario e chama o loop() do cliente mqtt
{
        LE18B20();
        if (!client.connected()) {
             conectaBroker( mqttUser, mqttPassword , 1);
             client.subscribe("#");  //  "#" significa subscribe todas as mensagens

        }
        client.loop();   

/*        if(temp[0] < setpoint[0]){
              analogWrite(D6,1024);
              digitalWrite(BUILTIN_LED,LOW);
        }
        else{
              analogWrite(D6,0);
              digitalWrite(BUILTIN_LED,HIGH);
        }
        */
        for(int i=0;i<ntemp && i<4;i++){
              int acao = satura(1000,setpoint[i]-temp[i]);
              analogWrite(driver[i],acao);
              if(i==1)analogWrite(BUILTIN_LED,1023-acao);
        }
        if(iteration%10==0)
              sendLine();
        if(iteration%600==0 && fgPub == 1){
              pub_temperaturas(2000);
        }
        delay(100);
        iteration++;
}

char msg[50];
char topic[50];

void pub_temperaturas(long delayT)
{
       for(int i=0;i<ntemp;i++){
             snprintf (topic, 50, "temp%d", i);        
             snprintf (msg, 50, "%5.2f", temp[i]);        
             client.publish(topic,msg);
             if(fgVerbose){
                   Serial.print(topic) ;
                   Serial.print(": ") ;
                   Serial.println(msg) ;
             }
             delay(delayT);
             //temp_1[i] = temp[i] ;
            }
}


void pub_extremes(long delayT)
{
       for(int i=0;i<ntemp;i++){
             snprintf (topic, 50, "tmin%d", i);        
             snprintf (msg, 50, "%5.2f", tmin[i]);   
             tmin[i] = 100;     
             client.publish(topic,msg);
             if(fgVerbose){
                   Serial.print(topic) ;
                   Serial.print(": ") ;
                   Serial.println(msg) ;
             }
             delay(delayT);
             snprintf (topic, 50, "tmax%d", i);        
             snprintf (msg, 50, "%5.2f", tmax[i]);  
             tmax[i] = 0;      
             client.publish(topic,msg);
             if(fgVerbose){
                   Serial.print(topic) ;
                   Serial.print(": ") ;
                   Serial.println(msg) ;
             }
             delay(delayT);
             //temp_1[i] = temp[i] ;
            }
}

int  satura(float Kp, float erro)
{

        float acao = Kp*erro;
        if ( acao > 1023) return 1023;
        if ( acao < 0 ) return 0;
        return (int)acao;
}
