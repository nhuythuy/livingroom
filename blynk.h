#include <BlynkSimpleEsp8266.h>

#include "wifi_cloud.h"
#include "global_vars.h"

int blynkCounter = 0;

#ifndef BLYNK
#define BLYNK

#define MESSAGE_DELAY                       100

#define VP_RUNTIME                          V0   // living room node
#define VP_CLOCK                            V1
#define VP_BATT_VOLTAGE                     V2
#define VP_TEMPERATURE                      V3
#define VP_HUMIDITY                         V4


#define VP_DOOR_BACK_OPENED_MINUTES         V20

// digital states
#define VP_DOOR_BACK                V51
#define VP_MOTION                   V52

#define VP_FORCE_CAMERA_POWER       V100
#define VP_FORCE_RADIO_POWER        V101

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

BLYNK_READ(VP_RUNTIME){
    Blynk.virtualWrite(VP_RUNTIME, runtimeMinutes);
}

BLYNK_READ(VP_TEMPERATURE){
  Blynk.virtualWrite(VP_TEMPERATURE, temp);
}

BLYNK_READ(VP_HUMIDITY){
  Blynk.virtualWrite(VP_HUMIDITY, humidity);
}

BLYNK_READ(VP_CLOCK){
  Blynk.virtualWrite(VP_CLOCK, systemClock);
}


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void blynkTimerEvent()
{
  blynkReconnect();
  yield();  

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(VP_DOOR_BACK, (ssDoorBack ? 255 : 0));
  delay(MESSAGE_DELAY);

  Blynk.virtualWrite(VP_MOTION, (ssMotion ? 255 : 0));
  delay(MESSAGE_DELAY);

  yield();
  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once
  Serial.println("Counter: " + String(runtimeMinutes));
  Serial.println("Clock: " + String(systemClock));
  Serial.println("Batt. Volt.: " + String(ssBatteryVolt));
  Serial.println("Temperature: " + String(temp));
  Serial.println("Humidity: " + String(humidity));


  Blynk.virtualWrite(VP_RUNTIME, runtimeMinutes);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_CLOCK, systemClock);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_BATT_VOLTAGE, ssBatteryVolt);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_TEMPERATURE, temp);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_HUMIDITY, humidity);
  delay(MESSAGE_DELAY);

  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once

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
