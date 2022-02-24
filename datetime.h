#include "global_vars.h"
#include <WiFiUdp.h>
#include <NTPClient.h>


#ifndef DATE_TIME
#define DATE_TIME


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov");
char* DayOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setupDateTime(){
  timeClient.begin(); // Initialize a NTPClient to get time
// Set offset time in seconds to adjust for your timezone
// ex.: GMT +1 = 3600, GMT +8 = 28800, GMT -1 = -3600, GMT 0 = 0
  timeClient.setTimeOffset(3600); // Norway GMT + 1
}

void getYearMonthDate() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  currentYear = ti->tm_year + 1900;
  currentMonth = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1);
  currentDate = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);
}

int getYear() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  int year = ti->tm_year + 1900;
  
  return year;
}

int getMonth() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  int month = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1);
  
  return month;
}

int getDate() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  int date = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);
  
  return date;
}

void getServerTime(){
  Serial.println();
  timeClient.update();
  currentDay = timeClient.getDay();
  currentHour = timeClient.getHours();
  currentMin = timeClient.getMinutes();

  getYearMonthDate();

  systemClock = (float)currentHour + currentMin / 100.0;
  Serial.println("Date YYYY-MM-DD:  " + String(currentYear) + "-" + String(currentMonth) + "-" + String(currentDate));  
  Serial.println("Today:  " + String(DayOfWeek[currentDay]) + " (" + String(currentDay) + ") - " + timeClient.getFormattedTime());  
}

#endif
