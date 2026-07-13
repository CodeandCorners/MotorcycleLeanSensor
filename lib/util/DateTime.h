#pragma once

#include <Arduino.h>


class DateTime 
{
public:
    uint64_t getCurrentEpochMs();
    void setCurrentDateTime(uint64_t epochMS);
    String convertEpochMSToUserFriendlyTimeStamp(uint64_t epochMS);

private:
  
    bool clientSetCurrentTimeYet = false;
};