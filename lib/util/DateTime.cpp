#include "DateTime.h"
#include <Arduino.h>


String DateTime::convertEpochMSToUserFriendlyTimeStamp(uint64_t epochMS)
{
    time_t seconds = epochMS / 1000;
    int ms = epochMS % 1000;

    struct tm tm;
    localtime_r(&seconds, &tm);

    char buf[40];
    snprintf(buf, sizeof(buf),
             "%04d-%02d-%02d %02d:%02d:%02d.%03d",
             tm.tm_year + 1900,
             tm.tm_mon + 1,
             tm.tm_mday,
             tm.tm_hour,
             tm.tm_min,
             tm.tm_sec,
             ms);

    return String(buf);
}
void DateTime::setCurrentDateTime(uint64_t epochMS)
{
    //dirty but works, first request sets time
    if (clientSetCurrentTimeYet)
    {
        Serial.println("Client has already set the current time, ignoring subsequent setCurrentDateTime call.");
        return;
    }
    timeval tv;
    tv.tv_sec = epochMS / 1000;
    tv.tv_usec = (epochMS % 1000) * 1000;
    settimeofday(&tv, nullptr);
    clientSetCurrentTimeYet = true;
}

uint64_t DateTime::getCurrentEpochMs()
{
    //cheeky safeguard at least if client hasn't set time yet "should never happen"
    if (!clientSetCurrentTimeYet)
    {
        Serial.println("Client has not set the current time yet, returning 0.");
        throw new std::runtime_error("Client has not set the current time yet.");
    }
    timeval tv;
    gettimeofday(&tv, nullptr);
    return (uint64_t)tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
}