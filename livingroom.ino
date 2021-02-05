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


void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(19200, SERIAL_8N1, SERIAL_TX_ONLY);
  WIFI_Connect();
  setupSensors();
}


// =======================================================
void loop (){
  runtimeMinutes = millis() / 60000;

  updateHumidTemp();
  delay(500);

  Serial.println("Living room: Runtime (" + String(runtimeMinutes)
  + "), Temp: (" + String(temp)
  + "), Humidity: (" + String(humidity)
  + "), Door back: (" + String(ssDoorBack)
  + "), Door back opened: (" + String(doorBackOpenedMinutes) + ") min");

  CommMain();

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  delay(5000);
}
