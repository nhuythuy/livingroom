#include <BlynkSimpleEsp8266.h>
#include "wifi_cloud.h"
#include "global_vars.h"

int blynkCounter = 0;

#ifndef BLYNK
#define BLYNK

#define MESSAGE_DELAY                       100

#define VP_BATT_VOLTAGE                     V1
#define VP_DOOR_BACK_OPENED_MINUTES         V9

#define VP_SYSTEM_TIME                      V10

#define VP_LR_RUNTIME                       V21   // living room node
#define VP_LR_TEMPERATURE                   V22
#define VP_LR_HUMIDITY                      V23


// digital states
#define VP_DOOR_BACK                V54
#define VP_POWER_RADIO              V59

#define VP_FORCE_RADIO_POWER        V100
#define VP_FORCE_CAMERA_POWER       V101

#define BLYNK_PRINT Serial

#ifndef WIFI_INFO
#define WIFI_INFO
char ssid[] = WIFI_AP;
char pass[] = WIFI_PW;
#endif

char auth[] = BLYNK_PW;

BlynkTimer timer;

void blynkReconnect() {
  if (!Blynk.connected()) {
    if (Blynk.connect()) {
      BLYNK_LOG("Reconnected");
    }
    else {
      BLYNK_LOG("Not reconnected");
    }
  }
}

BLYNK_WRITE(VP_FORCE_CAMERA_POWER)
{
  int pinVal = param.asInt(); // assigning incoming value from pin VP_FORCE_CAMERA_POWER to a variable
  forceCamPower = (boolean)pinVal;
  Serial.println("Force camera power: " + String(forceCamPower) + " - " + String(pinVal));
  // process received value
}

BLYNK_WRITE(VP_FORCE_RADIO_POWER)
{
  int pinVal = param.asInt(); // assigning incoming value from pin VP_FORCE_RADIO_POWER to a variable
  Serial.println("Force radio power: " + String(pinVal));
}

// for all signals requested by Blynk app (slow response)
BLYNK_READ(VP_BATT_VOLTAGE){
  Blynk.virtualWrite(VP_BATT_VOLTAGE, ssBatteryVolt);
}

BLYNK_READ(VP_DOOR_BACK_OPENED_MINUTES){
  Blynk.virtualWrite(VP_DOOR_BACK_OPENED_MINUTES, doorBackOpenedMinutes);
}

BLYNK_READ(VP_LR_RUNTIME){
    Blynk.virtualWrite(VP_LR_RUNTIME, runtimeMinutes);
}

BLYNK_READ(VP_LR_TEMPERATURE){
  Blynk.virtualWrite(VP_LR_TEMPERATURE, temp);
}

BLYNK_READ(VP_LR_HUMIDITY){
  Blynk.virtualWrite(VP_LR_HUMIDITY, humidity);
}

BLYNK_READ(VP_SYSTEM_TIME){
  Blynk.virtualWrite(VP_SYSTEM_TIME, systemHourMinute);
}


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void blynkTimerEvent()
{
  blynkReconnect();
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  yield();
  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once

  Blynk.virtualWrite(VP_DOOR_BACK, (ssDoorBack ? 255 : 0));
  delay(MESSAGE_DELAY);
}

void blynkSetup(){
  Serial.println("Connecting to Blynk ...");
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, blynkTimerEvent);
  Serial.println("Connected to Blynk !");
  delay(200);
}

void blynkLoop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

#endif
