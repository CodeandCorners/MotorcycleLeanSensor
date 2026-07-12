#include "LeanService.h"
#include "../schedulers/LeanScheduler.h"
#include "../db/LeanStatsRepo.h"
#include <Arduino.h>

LeanService::LeanService(LeanStatsRepo& repo)
    :leanStatsRepo(repo)
{
}

std::vector<LeanStat> LeanService::getLeanStats()
{
    return leanStatsRepo.get();
}