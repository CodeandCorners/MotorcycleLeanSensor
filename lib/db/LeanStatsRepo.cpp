#include "LeanStatsRepo.h"

void LeanStatsRepo::set(const std::vector<LeanStat>& stats)
{
    leanStats = stats;
}

std::vector<LeanStat> LeanStatsRepo::get() const
{
    return leanStats;
}
