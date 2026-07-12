#pragma once

#include <vector>
#include "../models/LeanStat.h"


class LeanScheduler;
class LeanStatsRepo;

class LeanService
{
public:
    LeanService(LeanStatsRepo& leanStatsRepo);

    std::vector<LeanStat> getLeanStats();

private:
    LeanStatsRepo& leanStatsRepo;
};