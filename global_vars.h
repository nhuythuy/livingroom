#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#define DELAY_LONG        5000      // 5,0 seconds
#define DELAY_SHORT       2500
long delayMs = DELAY_SHORT;

long globalState = 0;
int debugCounter = 0;

bool stateLed = 0;

// sensors
float humidity = 0.0;
float temp = 0.0;

int ssBatteryVoltRaw = 0;
float ssBatteryVolt = 0;
bool ssDoorBack = 0;

int ssWaterLeak = 0;


// actuators
bool acBuzzer = 0;

bool forceCamPower = 0;
bool forceRadioPower = 0;

int doorBackOpenedMinutes = 0;

int playMelodyCounter = 0;
int runtimeMinutes = 0;
#endif
