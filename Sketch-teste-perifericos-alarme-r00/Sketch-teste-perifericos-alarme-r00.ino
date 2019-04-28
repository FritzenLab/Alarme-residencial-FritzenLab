// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define zona1 2  // Zona (entrada) 1 (um) do alarme
#define zona2 3  // Zona (entrada) 2 (dois) do alarme
#define teclado A0 // Teclado analógico
#define DHTPIN A3 // Sensor temperatura DHT
#define buzzer A4 // Buzzer soldado na placa
#define sirene A5 // saída para sirene piezoelétrica externa
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

double tecladoRaw = 0.0;
boolean zonaum;
boolean zonadois;

void setup() {
  
  Serial.begin(9600);
  dht.begin();
  
  pinMode(sirene, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(zona1, INPUT);
  pinMode(zona2, INPUT);

  
}

void loop() {
  // Wait a few seconds between measurements.
  //tone(buzzer, 2860);
  digitalWrite(sirene, HIGH);
  tecladoRaw = analogRead(teclado) * 0.09765;
  zonaum= digitalRead(zona1);
  zonadois= digitalRead(zona2);
  delay(2000);
  noTone(buzzer);
  digitalWrite(sirene, LOW);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Sensor DHT11 falhou"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.print("teclado % = ");
  Serial.println(tecladoRaw);
  Serial.print("zona 1=");
  Serial.print(zonaum);
  Serial.print("   zona2=");
  Serial.println(zonadois);
}
