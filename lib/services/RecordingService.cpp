#include "RecordingService.h"
#include <Arduino.h>



std::vector<LeanStat>
RecordingService::getLeanStats()
{
    // return leanStats;
       return std::vector<LeanStat>{
        { "dummyDate1", 0 },
        { "dummy", 10 }
    };
}