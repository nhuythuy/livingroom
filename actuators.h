#include "global_vars.h"

#ifndef ACTUATORS
#define ACTUATORS

void setupActuators(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_AC_CAM_POWER, OUTPUT);
  pinMode(PIN_AC_TOILET_LED, OUTPUT);
}

void updateCamPower(){
  if(forceCamPower == true)
    digitalWrite(PIN_AC_CAM_POWER, LOW);
  else // if(forceCamPower == 0)
    digitalWrite(PIN_AC_CAM_POWER, HIGH);
}

bool updateToiletLed(){
  yield();
  bool ledOn = false;

  if(manualToiletLedCtrlEnabled){
    ledOn = forceLedPower;
  }
  else{
    if((currentMonth >= 4) && (currentMonth <= 10)){
      if ((currentHour >= 23) || (currentHour <= 8))
        ledOn = true;
    }
    else{
      if ((currentHour >= 22) || (currentHour <= 9))
        ledOn = true;
    }
  }

  digitalWrite(PIN_AC_TOILET_LED, ledOn);
#ifdef ENABLE_CAYENNE
//  writeCayenneDigitalState(CH_POWER_RADIO, ledOn);
#endif

  return ledOn;
}

void updateActuators(){
  updateCamPower();
  acToiletLedOn = updateToiletLed();
}



#endif
