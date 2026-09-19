/*
  AQUA STASIS REGULATOR
  Arduino UNO
  pH + DS18B20 Temperature + Water Level
  Serial output for Python → Blynk gateway
*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 2

OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  int phRaw = analogRead(A0);
  int levelRaw = analogRead(A2);

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Convert sensor readings
  float pH = (phRaw * 14.0) / 1023.0;
  float waterLevel = (levelRaw * 100.0) / 1023.0;

  // Send formatted data to Python
  Serial.print("pH:");
  Serial.print(pH, 2);

  Serial.print(",Temp:");
  Serial.print(temperature, 2);

  Serial.print(",Level:");
  Serial.println(waterLevel, 0);

  delay(1500);
}