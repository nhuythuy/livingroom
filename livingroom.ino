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
#include <ArduinoJson.h>

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

  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      digitalWrite(PIN_LED, LOW);  // to show the communication only (inverted logic)
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("Request from client: "); Serial.println(request);
      client.flush();
      //client.println("Hi client! No, I am listening.\r"); // sends the answer to the client

      DynamicJsonDocument doc(100);
      doc["node"] = "homelivingroom";
      doc["heartbeat"] = heartbeat++;
      doc["runtime"] = runtimeMinutes;
      doc["temp"] = String(temp, 2);
      doc["humidity"] = String(humidity, 2);
      ssDoorBack = !ssDoorBack;
      doc["ssDoorBack"] = ssDoorBack;
      doc["ssDoorBackOpenMin"] = minutesDoorBackOpened++;
    
      char jsonHomeMain[100];
      serializeJson(doc, jsonHomeMain);
      client.println(String(jsonHomeMain) + "\r");
      Serial.println("Reply from server: " + String(jsonHomeMain));

      digitalWrite(PIN_LED, HIGH);
    }
    client.stop();                // tarminates the connection with the client
  }

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  delay(5000);
}
