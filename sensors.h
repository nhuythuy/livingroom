#include <DHT.h>
#include "lib.h"
#include "cayenne.h"

DHT dht(PIN_SS_DHT, DHT11, 15);

void setupSensors(){
  dht.begin();
}

void setupDigitalSensors(){
  pinMode(PIN_SS_DOOR_BACK, INPUT);
}

void updateDigitalSensors(){
  bool state;
  state = !digitalRead(PIN_SS_DOOR_BACK);
  if (state != ssDoorBack){
#ifdef ENABLE_CAYENNE
    writeCayenneDigitalState(CH_DOOR_BACK, state);
#endif
    if(state)
      doorBackOpenedAt = millis();
    else
      doorBackOpenedAt = 0;

    ssDoorBack = state;
  }

}

bool updateHumidTemp(){
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");

    flipLed();
    humidity = -100;
    temp = -100;
    return false;
  }

  return true;
}
