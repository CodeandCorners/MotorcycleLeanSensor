#include "LeanStatsRepo.h"

void LeanStatsRepo::update(const LeanStat& newStat)
{
    leanStats.push_back(newStat);
}
void LeanStatsRepo::reset()
{
    leanStats.clear();
}

std::vector<LeanStat> LeanStatsRepo::get()
{
    return leanStats;
}
