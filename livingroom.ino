
#include "sensors.h"
#include "actuators.h"
#include "datetime.h"
#include "blynk.h"


#define MESSAGE_DELAY 50

void setup()
{
  ESP.wdtDisable();

  Serial.begin(115200);
  Serial.println("-- Node name:         LIVING ROOM");
  delay(100);

  setupSensors();
  setupDigitalSensors();
  delay(100);

  setupActuators();
  delay(100);

#ifdef ENABLE_WIFI
  WIFI_Connect();
  setupDateTime();

#ifdef ENABLE_CAYENNE
  cayenneSetup();
#endif
#ifdef ENABLE_BLYNK
  blynkSetup();
#endif
#endif

  setupDateTime();

  ESP.wdtEnable(5000); // msec
}

unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
long diffMillis = 0;

void loop() {
  currentMillis = millis();
  runtimeMinutes = currentMillis / 60000;
  diffMillis = currentMillis - previousMillis;
  if(abs(diffMillis) > 2000){         // sampling sensors every 2 sec
    previousMillis = currentMillis;   // save the last time  

    yield();
    getServerTime();

    yield();
//    updateBattVolt();
//    yield();
    updateHumidTemp();
    yield();
    updateDigitalSensors();
    yield();
    updateCamPower();

    Serial.println("-- Node name:              LIVING ROOM");
    Serial.println("0. Runtime (min):          " + String(runtimeMinutes));
    Serial.println("1. Temperature (*C):       " + String(temp));
    Serial.println("2. Humidity (%):           " + String(humidity));
    Serial.println("3. Door back opened (0/1): " + String(ssDoorBack) + " in (min)" + String(doorBackOpenedMinutes));
    Serial.println("4. Motion IN (0/1):        " + String(ssMotion) + " OUT: " + String(acMotion));
    Serial.println();
  
    flipLed();
  }
  
#ifdef ENABLE_WIFI
#ifdef ENABLE_CAYENNE
  yield();
  Cayenne.loop();
#endif
#ifdef ENABLE_BLYNK
  yield();
  blynkUpdate();
#endif
#endif
}
