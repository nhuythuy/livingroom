#include <DHT.h>
#include "lib.h"


DHT dht(PIN_SS_DHT, DHT11, 15);

void setupSensors(){
  dht.begin();
}

bool updateHumidTemp(){
  float bmHumidity = dht.readHumidity();
  float bmTemp = dht.readTemperature();
  if (isnan(bmHumidity) || isnan(bmTemp)) {
    Serial.println("Failed to read from DHT sensor!");

    blinkLed();
    bmHumidity = -100;
    bmTemp = -100;
    return false;
  }

  return true;
}
