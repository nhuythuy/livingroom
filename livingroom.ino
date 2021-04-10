#include <DHT.h>
#include "global_vars.h"
#include "pin_define.h"
#include "wifi_cloud.h"
#include "sensors.h"
#include "actuators.h"
#include "blynk.h"
#include "cayenne.h"


void setup() {
  ESP.wdtDisable();
  setupActuators();

  Serial.begin(19200, SERIAL_8N1, SERIAL_TX_ONLY);

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

  setupSensors();
  setupDigitalSensors();
  ESP.wdtEnable(5000); // msec
}

unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
// =======================================================
void loop (){
  ESP.wdtFeed();

  yield();
  currentMillis = millis();
  runtimeMinutes = currentMillis / 60000;

  if(abs(currentMillis - previousMillis) > 2000){ // sampling sensors every 2 sec
#ifdef ENABLE_WIFI
    if(WiFi.status() == WL_DISCONNECTED){
      Serial.println("WiFi connection lost! Reconnecting...");
      WiFi.disconnect();
      WIFI_Connect();    
    }
  
    yield();
    getServerTime();
#endif

    previousMillis = currentMillis;
    yield();
    updateHumidTemp();
    yield();
    updateDigitalSensors();
    yield();
    updateCamPower();
    
    Serial.println("Living room: Runtime (" + String(runtimeMinutes)
      + "), Temp: (" + String(temp) + "), Humidity: (" + String(humidity)
      + "), Door back: (" + String(ssDoorBack)
      + "), Door back opened: (" + String(doorBackOpenedMinutes) + ") min");

    flipLed();
  }

#ifdef ENABLE_WIFI
#ifdef ENABLE_CAYENNE
  yield();
  Cayenne.loop();
#endif
#ifdef ENABLE_BLYNK
  yield();
  blynkLoop();
#endif
#endif

}
