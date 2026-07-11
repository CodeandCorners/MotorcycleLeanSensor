#include "RecordingService.h"
#include "../schedulers/LeanScheduler.h"
#include <Arduino.h>


RecordingService::RecordingService(LeanScheduler& scheduler, LeanStatsRepo& stats) : leanScheduler(scheduler), leanStatsRepo(stats) {}

std::vector<LeanStat>
RecordingService::getLeanStats()
{
    // return leanStats;
       return std::vector<LeanStat>{
        { "dummyDate1", 0 },
        { "dummy", 10 }
    };
}