#pragma once

#include <vector>
#include "../models/LeanStat.h"

class LeanStatsRepo
{
public:
    void update(const LeanStat& newStat);
    void reset();
    std::vector<LeanStat> get();

private:
    std::vector<LeanStat> leanStats;
};