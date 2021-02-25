#include "global_vars.h"

#ifndef ACTUATORS
#define ACTUATORS

void setupActuators(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_AC_CAM_POWER, OUTPUT);  
}

void updateCamPower(){
  if(forceCamPower == 1)
    digitalWrite(PIN_AC_CAM_POWER, LOW);
  else // if(forceCamPower == 0)
    digitalWrite(PIN_AC_CAM_POWER, HIGH);
}

void updateActuators(){
}



#endif
