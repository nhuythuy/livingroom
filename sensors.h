#include <DHT.h>
#include "lib.h"
#include "cayenne.h"

DHT dht(PIN_SS_DHT, DHT11, 15);

void setupSensors(){
  dht.begin();
}

void setupDigitalSensors(){
  pinMode(PIN_SS_DOOR_BACK, INPUT);
  pinMode(PIN_SS_MOTION, INPUT);
}

void updateDigitalSensors(){
  yield();
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

//  ssMotion = digitalRead(PIN_SS_MOTION);
  state = digitalRead(PIN_SS_MOTION);
  if (state != ssMotion){
#ifdef ENABLE_CAYENNE
    writeCayenneDigitalState(CH_MOTION, state);
#endif
    if(!state)
      motionToLowAt = millis(); // 32 bits, could be roll over after ~49 days but assumming that at least one motion detected within those days
    else
      motionToLowAt = 0;

    if(state || ((motionToLowAt > 0) && (motionToLowAt <= 10000))) // 10 sec delay to activate actuator
      acMotion = true;
    else
      acMotion = false;

    ssMotion = state;
  }

}

bool updateHumidTemp(){
  yield();
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
