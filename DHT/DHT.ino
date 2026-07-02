#include "DHT.h"

#define DHTPIN 23
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("initializing");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if(isnan(humidity) || isnan(temperature)) {
    Serial.println("not reading data from DHT 22");
  }

  Serial.print("Humidity(%): ");
  Serial.println(humidity);
  Serial.print("Temperature(degC): ");
  Serial.println(temperature);
}
