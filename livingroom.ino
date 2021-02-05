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
#include "comm_main.h"

#define DELAY_LONG        5000      // 5,0 seconds
#define DELAY_SHORT       2500

long delayMs = DELAY_SHORT;

int serverHomeCounter = 0;


void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(19200, SERIAL_8N1, SERIAL_TX_ONLY);
  setupSensors();
  WIFI_Connect();
}


void blinkLed(){
  digitalWrite(PIN_LED, false);
  delay(1000);
  digitalWrite(PIN_LED, true);
  delay(1000);
}

void delayWithErrorCheck(){
    if(globalState > 0)
    blinkLed();
  else
    delay(delayMs);
}


// =======================================================
void loop (){
  runtimeMinutes = millis() / 60000;

  delay(1000);
  updateHumidTempe();
  delay(1000);

  CommMain();

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  delay(5000);
}
