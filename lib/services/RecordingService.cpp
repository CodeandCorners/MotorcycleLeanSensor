#include "RecordingService.h"
#include "../schedulers/LeanScheduler.h"
#include <Arduino.h>


RecordingService::RecordingService(LeanScheduler& scheduler, LeanStatsRepo& stats) : leanScheduler(scheduler), leanStatsRepo(stats) {}

std::vector<LeanStat>
RecordingService::getLeanStats()
{
       return std::vector<LeanStat>{
        { "dummyDate1", 0.0f },
        { "dummyDate2", 10.0f },
        { "dummyDate3", -10.0f }
    };
}