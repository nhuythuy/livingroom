#ifndef LIVINGROOM_IO
#define LIVINGROOM_IO

// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
// IMPORTANT NOTE: Remove PIN_SS_DOOR_MAIN connector b4 uploading code to NodeMcu, uploading fail otherwise
//   Serial.begin(19200, SERIAL_8N1, SERIAL_TX_ONLY);

// inputs D1, D2, D5, D6, D7
#define PIN_SS_SUPPLY_VOLT          A0 // battery voltage

#define PIN_SS_DHT                  D5 // DHT sensor pin
#define PIN_SS_DOOR_BACK            D7 // D7 ok as In, Out

#define PIN_SS_WATER_SMOKE          D0 // smoke, water leak
#define PIN_SS_MOTION               D1 // No. 2, motion sensor for entrance

//#define PIN_SS_DOOR_BASEMENT      D6 // No. 1, door to go down to basement and door to renting area
//#define PIN_LIGHT_LIVING_ROOM     Dx


// outputs
#define PIN_LED                     D4 // D4: same as built in LED GPIO2
#define PIN_TONE_MELODY             D8

#define PIN_CAM_POWER               D2 // No. 1, power for entrance led
#define PIN_AC_POWER_RADIO          D3 // OK as output, not possible to connect to OPTO input: connected to FLASH button, boot fails if pulled LOW

// remaining pins: RX (in), D3

#define FIELD_ID_POWER_CAM  8
#define FIELD_ID_POWER_LOAD 9

#endif
