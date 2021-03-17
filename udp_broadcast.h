//#include <WiFi.h>
#include "global_vars.h"
#include "auth_settings.h"
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#ifndef UDP_BROADCAST
#define UDP_BROADCAST

WiFiUDP udp;

#define BROADCAST_IP    "192.168.1.255"
#define BROADCAST_PORT  45678

#define BUFFER_LENGTH   200

byte buffJson[BUFFER_LENGTH];
String sJson;

void setupUdp(){
  udp.begin(BROADCAST_PORT);
}

void receiveUdp(){
  int pkSize = udp.parsePacket();
  if(pkSize){
    Serial.println("---------------receiveUdp");
    char pktBuf[pkSize];
    Serial.print(udp.remoteIP());
    Serial.print(":");
    Serial.println(udp.remotePort());
    udp.read(pktBuf, pkSize);
    udp.stop();
    //udp.begin(BROADCAST_PORT);
    String sJson = String(pktBuf);
    Serial.println(sJson);
//    for (int i = 0; i < pktSize; i++) {
//      Serial.print(pktBuf[i], HEX);
//      Serial.print("\t");
//    }
//    Serial.println();
  }
  
}

void buildMessage(){
  // https://arduinojson.org/v6/example/

  DynamicJsonDocument doc(256);
  doc["node"] = "livingroom";
  doc["runtime"] = runtimeMinutes;
  doc["battvolt"] = String(ssBatteryVolt, 2);
//  doc["temp"] = String(bmTemp, 2);
//  doc["humidity"] = String(bmHumidity, 2);
//  doc["ssDoorMain"] = ssDoorMain;
//  doc["doorMainOpenedMinutes"] = doorMainOpenedMinutes;
//  doc["ssDoorToBasement"] = ssDoorToBasement;
//  doc["doorToBasementOpenedMinutes"] = doorToBasementOpenedMinutes;
//  doc["ssDoorBasement"] = ssDoorBasement;
//  doc["doorBasementOpenedMinutes"] = doorBasementOpenedMinutes;
//  doc["ssLightBasementOn"] = ssLightBasementOn;
//  doc["ssEntranceMotion"] = ssEntranceMotion;
//  doc["entranceMotionSeconds"] = entranceMotionSeconds;
//  doc["ssWaterLeak"] = ssWaterLeak;
//  doc["acActuators"] = acActuators;

  serializeJson(doc, sJson);
}

void sendBroadcast(){
  buildMessage();
  int len = sJson.length();
  memset(buffJson, 0x00, sizeof(buffJson));

  byte plain[len];
  sJson.getBytes(plain, sJson.length());

  udp.beginPacket(BROADCAST_IP,BROADCAST_PORT);
  udp.write(plain, len);
  udp.endPacket();

  Serial.println("Broadcast sent: " + String(len));
}



#endif
