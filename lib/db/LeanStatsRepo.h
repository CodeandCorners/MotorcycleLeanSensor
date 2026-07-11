#pragma once

#include <vector>
#include "../models/LeanStat.h"

class LeanStatsRepo
{
public:
    void set(const std::vector<LeanStat>& stats);
    std::vector<LeanStat> get() const;

private:
    std::vector<LeanStat> leanStats;
};