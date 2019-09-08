
#include <OneWire.h>
#include <DallasTemperature.h>

#define NUM_MAX_SENSORES 8
#define PINO_BARRAMENTO_ONEWIRE D4   // barramento onewire no D4 ok 
#define TEMPERATURE_PRECISION 12


#ifdef MASTER_18B20
OneWire oneWire(PINO_BARRAMENTO_ONEWIRE);
DallasTemperature sensors18B20(&oneWire);
DeviceAddress sensorTemp[NUM_MAX_SENSORES];
float temp[NUM_MAX_SENSORES];
float temp_1[NUM_MAX_SENSORES];
float tmax[NUM_MAX_SENSORES] ={0,0,0,0,0,0,0,0};
float tmin[NUM_MAX_SENSORES]={100,100,100,100,100,100,100,100};
float setpoint[NUM_MAX_SENSORES] = {21,21,21,21,21,21,21,21};
float atua[NUM_MAX_SENSORES];
unsigned int ntemp;
#else
extern OneWire oneWire;
extern DallasTemperature sensors18B20;
extern DeviceAddress sensorTemp[];
extern float temp[];
extern float temp_1[];
extern float tmax[];
extern float tmin[];
extern float setpoint[];
extern float atua[];

extern unsigned int ntemp;
#endif


void setupTemp18B20();
void LE18B20();
void sendLine();
void printDallasAddress(DeviceAddress deviceAddress);
