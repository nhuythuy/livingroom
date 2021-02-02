/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates clients as diff. nodes
 */

//#include <DHT.h>
#include "global_vars.h"
#include "pin_define.h"
#include "wifi_cloud.h"
#include "comm_main.h"

#define DELAY_LONG        5000      // 5,0 seconds

int serverHomeCounter = 0;
                    
//DHT dht(PIN_SS_DHT, DHT11, 15);

long delayMs = DELAY_LONG;

void setup() {
  pinMode(PIN_LED, OUTPUT);

//  dht.begin();
  Serial.begin(19200);
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

bool updateHumidTempe(){
//  humidity = dht.readHumidity();
//  temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");

    delayWithErrorCheck();
    humidity = -100;
    temp = -100;
    return false;
  }

  return true;
}

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
