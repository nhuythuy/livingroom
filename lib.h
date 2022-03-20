#include "global_vars.h"
#include "pin_define.h"


#ifndef LIB
#define LIB


void flipLed(){
  heartbeatLed = !heartbeatLed;
  digitalWrite(PIN_LED, heartbeatLed);
}

void printlnValue(String desc, double value){
  Serial.print(desc);
  Serial.println(value);
}

void printlnStringField(String desc, String value){
  Serial.print(desc);
  Serial.println(value);
}

void printDebugSerial(){
  Serial.println();
  Serial.println("--------------------------------------------");
  Serial.println("Node: LIVING ROOM, clock: " + String(systemClock));
  printlnValue("0. Battery volt. (V):       ", ssBatteryVolt);
  printlnValue("1. Temperature (deg C):     ", temp);
  printlnValue("2. Humidity (%):            ", humidity);
  printlnValue("3. Door back:               ", ssDoorBack);
  printlnValue("4. Motion:                  ", ssMotion);
  printlnValue("5. Water Smoke:             ", ssWaterLeak);
  printlnValue("6. Runtime (minutes):       ", runtimeMinutes);

  Serial.println("--------------------------------------------");
  printlnValue("1. Camera power force:      ", forceCamPower);
  printlnValue("2. Toilet light manual:     ", manualToiletLedCtrlEnabled);
  printlnValue("3. Toilet light force ON:   ", forceLedPower);
  printlnValue("3. Toilet light ON:         ", acToiletLedOn);

  Serial.println("--------------------------------------------");
  printlnValue("Door back opened (min):     ", doorBackOpenedMinutes);
//  printlnValue("Entrance motion ON (sec):   ", entranceMotionSeconds);
  Serial.println();
}


#endif
