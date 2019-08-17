
#include <OneWire.h>
#include <DallasTemperature.h>

#define NUM_MAX_SENSORES 8
#define PINO_BARRAMENTO_ONEWIRE D5
#define TEMPERATURE_PRECISION 12


#ifdef MASTER_18B20
OneWire oneWire(PINO_BARRAMENTO_ONEWIRE);
DallasTemperature sensors18B20(&oneWire);
DeviceAddress temp[NUM_MAX_SENSORES];
float current[NUM_MAX_SENSORES];
unsigned int ntemp;
#else
extern OneWire oneWire;
extern DallasTemperature sensors18B20;
extern DeviceAddress temp[];
extern float current[];
extern unsigned int ntemp;
#endif


void setupTemp18B20();
void LE18B20();
void sendLine();
void printDallasAddress(DeviceAddress deviceAddress);
