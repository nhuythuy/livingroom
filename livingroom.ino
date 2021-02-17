/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates clients as diff. nodes
 */

#include <DHT.h>
#include "global_vars.h"
#include "pin_define.h"
#include "wifi_cloud.h"
#include "sensors.h"
//#include "comm_main.h"
#include "blynk.h"
#include "cayenne.h"

#define ENABLE_WIFI
#define ENABLE_BLYNK
#define ENABLE_CAYENNE


void setup() {
  ESP.wdtDisable();
  pinMode(PIN_LED, OUTPUT);

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

  ESP.wdtEnable(5000); // msec
}


// =======================================================
void loop (){
  ESP.wdtFeed();

  long mill = millis();
  runtimeMinutes = millis() / 60000;

  if((mill - ssSamplingTimer) > 2000){ // sampling sensors every 1 sec
#ifdef ENABLE_WIFI
    getServerTime();
#endif

    updateHumidTemp();
    ssSamplingTimer = mill;

    Serial.println("Living room: Runtime (" + String(runtimeMinutes)
      + "), Temp: (" + String(temp)
      + "), Humidity: (" + String(humidity)
      + "), Door back: (" + String(ssDoorBack)
      + "), Door back opened: (" + String(doorBackOpenedMinutes) + ") min");
  }

//  CommMain();
#ifdef ENABLE_WIFI
#ifdef ENABLE_CAYENNE
  Cayenne.loop();
#endif
#ifdef ENABLE_BLYNK
  blynkLoop();
#endif

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();    
  }
#endif

  flipLed();

}
