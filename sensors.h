#include <DHT.h>
#include "lib.h"
#include "Adafruit_SHTC3.h"


DHT dht(PIN_SS_DHT, DHT11, 15);
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();




void setupSensors(){
  dht.begin();

  if (! shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1) delay(1);
  }
  Serial.println("Found SHTC3 sensor");
}

bool updateTemp(){
  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  return true;
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
