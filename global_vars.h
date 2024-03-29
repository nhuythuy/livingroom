#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#define ENABLE_WIFI
#define ENABLE_BLYNK
#define ENABLE_CAYENNE

#define SLOW_UPDATE_CYCLE_SECOND  10000     // 10 seconds

#define DELAY_LONG                5000      // 5,0 seconds
#define DELAY_SHORT               2500
long delayMs = DELAY_SHORT;

#define APP_VERSION               1.2

long globalState = 0;
int debugCounter = 0;

bool heartbeatLed = 0;

// sensors
float humidity = 0.0;
float temp = 0.0;

int ssBatteryVoltRaw = 0;
float ssBatteryVolt = 0;
bool ssDoorBack = 0;
bool ssMotion = 0;

int ssWaterLeak = 0;


// actuators
bool acBuzzer = false;
bool acMotion = false;

bool forceCamPower = false;
bool forceRadioPower = false;

bool acToiletLedOn = false;
bool manualToiletLedCtrlEnabled = false;
bool forceLedPower = false;

int doorBackOpenedMinutes = 0;
int doorBackOpenedAt = 0;
int motionToLowAt = 0;

int playMelodyCounter = 0;
int runtimeMinutes = 0;

int currentYear = -1;
int currentMonth = -1;
int currentDate = -1;
int currentHour = -1;
int currentDay = -1;
int currentMin = -1;
float systemClock = 0.0;

#endif
