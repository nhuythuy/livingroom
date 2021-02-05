#include <DHT.h>
#include "lib.h"


DHT dht(PIN_SS_DHT, DHT11, 15);

void setupSensors(){
  dht.begin();
}

bool updateHumidTemp(){
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");

    blinkLed();
    humidity = -100;
    temp = -100;
    return false;
  }

  return true;
}
