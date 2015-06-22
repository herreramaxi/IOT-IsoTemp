#include "IsoTemp.h"

void setup() {
  Serial.begin(BAUD_RATE);

#if !defined(TEST)
  dht.begin();
#endif
}

void loop() {
  struct SensorsValues values = GetSensorsValues();
  String serialString;

  serialString += SerializeSensorValue(values.gas);
  serialString += SPACE_TOKEN;
  serialString += SerializeSensorValue(values.temperature);
  serialString += SPACE_TOKEN;
  serialString += SerializeSensorValue(values.humidity);

  Serial.println(serialString);

  delay(DELAY);
}

#ifdef TEST
//Si esta definido TEST (#define TEST), se utiliza esta funcion para obtener valores aleatorios
struct SensorsValues GetSensorsValues()
{
  struct SensorsValues values;

  values.temperature = MakeSensorValue(NAME_TEMPERATURE_SENSOR, random(-10, 100), UNIT_TEMPERATURE);
  values.humidity = MakeSensorValue(NAME_HUMIDITY_SENSOR, random(100), UNIT_HUMIDITY);
  values.gas = MakeSensorValue(NAME_GAS_SENSOR, random(100), UNIT_GAS);

  return values;
}

#else
//Si NO esta definido TEST (//#define TEST), se utiliza esta funcion para obtener valores de los sensores
struct SensorsValues GetSensorsValues()
{
  struct SensorsValues values;

  values.temperature = MakeSensorValue(NAME_TEMPERATURE_SENSOR, dht.readTemperature(), UNIT_TEMPERATURE);
  values.humidity = MakeSensorValue(NAME_HUMIDITY_SENSOR, dht.readHumidity(), UNIT_HUMIDITY);
  values.gas = MakeSensorValue(NAME_GAS_SENSOR, analogRead(MQ2PIN), UNIT_GAS);

  return values;
}

#endif

struct  SensorValue MakeSensorValue(String name, float value, String unit)
{
  struct SensorValue sensorValue;

  sensorValue.name = name;
  sensorValue.value = value;
  sensorValue.unit = unit;

  return sensorValue;
}

String SerializeSensorValue(struct SensorValue value)
{
  String valueString;

  valueString += "<";
  valueString += value.name;
  valueString += ": ";
  valueString += isnan(value.value) ? "NaN" : (String)value.value;
  valueString += "[" + value.unit + "]";
  valueString += ">";

  return valueString;
}

//Ejemplo de lo que se recibiria por serial
//Caso de lectura exitosa
//<Gas: xxx [Unit]>  <Temperature: xxx [Unit]>  <Humidity: xxx [Unit]>

//Caso de que el valor obtenido del sensor sea nan
//<Gas: NaN [Unit]>  <Temperature: NaN [Unit]>  <Humidity: NaN [Unit]>
