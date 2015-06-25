#include "DHT.h"

#define BAUD_RATE 9600

//Comentar si se esta probando con sensores conectados.
//En otro caso dejar descomentado y se obtendran valores aleatorios.
#define TEST

#define NAME_TEMPERATURE_SENSOR "Temperatura"
#define NAME_HUMIDITY_SENSOR "Humedad"
#define NAME_GAS_SENSOR "Gas"
#define UNIT_TEMPERATURE "*C"
#define UNIT_HUMIDITY "%"
#define UNIT_GAS "PPM"
#define SPACE_TOKEN "\t\t"

#define DELAY 2000
#define MQ2PIN A0
#define DHTPIN 8

//Descomentar DHTTYPE segun el sensor de temperatura que se utilice
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#if !defined(TEST)
DHT dht(DHTPIN, DHTTYPE);
#endif

struct SensorValue
{
  String name;
  float value;
  String unit;
};

struct SensorsValues
{
  struct SensorValue temperature;
  struct SensorValue humidity;
  struct SensorValue gas;
};

struct SensorsValues GetSensorsValues();
struct SensorValue MakeSensorValue(String name, float value, String unit);
String SerializeSensorValue(struct SensorValue value);
