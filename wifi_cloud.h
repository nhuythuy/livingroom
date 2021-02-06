#include <ESP8266WiFi.h>
#include "global_vars.h"
#include "auth_settings.h"
#include "lib.h"


#ifndef WIFI_CLOUD
#define WIFI_CLOUD

const char* wifiSsid = WIFI_AP;
const char* wifiPassword = WIFI_PW;

IPAddress ip(192, 168, 1, 5);             // IP address of the server
IPAddress gateway(192,168,1,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network
WiFiServer server(80);

void WIFI_Connect(){
  Serial.println();
  Serial.println("MAC: " + WiFi.macAddress()); Serial.println();
  Serial.println("Connecting to " + String(wifiSsid));

  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(wifiSsid, wifiPassword);

  bool ledStatus = false;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    flipLed();
    if(debugCounter++ > 80)
    {
      debugCounter = 0;
      Serial.println("!");
    }
  }

  delay(100);
  Serial.println();
  Serial.println("Connected to wifi");
  Serial.print("Status: ");   Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");       Serial.println(WiFi.localIP());
  Serial.print("Subnet: ");   Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");  Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: ");     Serial.println(WiFi.SSID());
  Serial.print("Signal: ");   Serial.println(WiFi.RSSI());
  Serial.println();
  delay(100);

  server.begin(); // starts the server
  delay(100);
}

#endif
