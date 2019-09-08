
/*
 *   Alterna estado do LED da placa do NodeMCU ESP8266
 *   atraves de um broker MQTT
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#ifdef MASTER_BROKER
// configure a tua rede wireless
const char* ssid =  "minha-rede"; 
const char* password = "minha-senha-de-rede"; 

// Configure o teu broker e a instancia
char* mqttServer = "url-do-broker";
const int mqttPort = 8300; //  "configuire porta do broker";
char* mqttUser = "user-do-broker";
char* mqttPassword = "senha-do-user-do-broker";


//Variáveis de wifi e broker mqtt
WiFiClient espClient;
PubSubClient client(espClient);

unsigned int fgPub = 0;
unsigned int fgVerbose = 0;

#else
// configure a tua rede wireless
extern const char* ssid ; 
extern const char* password ; 

// Configure o teu broker e a instancia
extern char* mqttServer;
extern const int mqttPort ;
extern char* mqttUser;
extern char* mqttPassword ;

//Variáveis de wifi e broker mqtt
extern WiFiClient espClient;
extern PubSubClient client;

extern unsigned int fgPub;
extern unsigned int fgVerbose;
#endif


void setup_wifi() ;
void setup_broker() ;
void minhaFuncaoSubscritora(char* topic, byte* payload, unsigned int length);
void conectaBroker(char* user, char* password, int n) ;
