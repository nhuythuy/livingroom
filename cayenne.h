#include "wifi_cloud.h"
#include "global_vars.h"
#include <CayenneMQTTESP8266.h>


// Name convention: Area_SensorType_Time_Type, ex.: DOOR_MAIN_MINUTES_OPENED, LR_HUMIDITY

#ifndef MY_DEVICES
#define MY_DEVICES

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char dvUsername[] = CAYENNE_USERNAME;
char dvPassword[] = CAYENNE_PASSWORD;
char dvClientID[] = CAYENNE_CLIENT_ID;

#define MESSAGE_DELAY                       100 // millisec
#define CH_DOOR_BACK_OPENED_MINUTES         9

#define CH_SYSTEM_TIME                      10

#define CH_LR_RUNTIME                       21   // living room node
#define CH_LR_TEMPERATURE                   22
#define CH_LR_HUMIDITY                      23


// digital states
#define CH_DOOR_BACK                        51
#define CH_MOTION                           52
#define CH_TOILET_LED_ON                    53

#define CH_FORCE_CAMERA_POWER               100
#define CH_FORCE_RADIO_POWER                101


void cayenneSetup(){
  Serial.println("Cayenne connecting...");
  Cayenne.begin(dvUsername, dvPassword, dvClientID, wifiSsid, wifiPassword);
  Serial.println("Cayenne connected!");
  delay(200);
}

CAYENNE_OUT_DEFAULT(){
  //blynkReconnect();

//    Cayenne.virtualWrite(CH_BATT_VOLTAGE, ssBatteryVolt, "batt", "V");
    yield();
    Cayenne.virtualWrite(CH_DOOR_BACK_OPENED_MINUTES, doorBackOpenedMinutes, "counter");
    Cayenne.virtualWrite(CH_LR_RUNTIME, runtimeMinutes, "counter");
    Cayenne.celsiusWrite(CH_LR_TEMPERATURE, temp);
    Cayenne.virtualWrite(CH_LR_HUMIDITY, humidity, "rel_hum", "p");
    Cayenne.virtualWrite(CH_SYSTEM_TIME, systemClock);

  // digital signals
    Cayenne.virtualWrite(CH_TOILET_LED_ON, acToiletLedOn);
}

void writeCayenneDigitalState(int channelId, int value){
  delay(MESSAGE_DELAY);
  Cayenne.virtualWrite(channelId, value, "digital_sensor", "d");
}

CAYENNE_IN(CH_FORCE_RADIO_POWER)
{
  forceRadioPower = getValue.asInt(); // Get value as integer
//  Serial.println("Radio power force: " + String(forceRadioPower));
}


#endif
