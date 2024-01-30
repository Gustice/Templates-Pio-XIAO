#pragma once

#include "RTClib.h"
#include <string>

class Time {
  private:
    char *daysOfTheWeek[7] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday", "Saturday"};
    RTC_PCF8563 _rtc;

  public:
    void begin() {
        if (!_rtc.begin()) {
            Serial.println("Couldn't find RTC");
        }

        if (_rtc.lostPower()) {
            _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
            // _rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        }
        _rtc.start();
    }

    std::string getDateStringNow() {
        char buf[24];
        DateTime now = _rtc.now();
        sprintf(buf, "%4d.%02d.%02d", now.year(), now.month(), now.day());
        return std::string(buf);
    }

    std::string getTimeStringNow() {
        char buf[24];
        DateTime now = _rtc.now();
        sprintf(buf, "%02d:%02d:%02d",  now.hour(),
                now.minute(), now.second());
        return std::string(buf);
    }
};
