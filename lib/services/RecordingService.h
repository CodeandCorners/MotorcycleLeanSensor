#pragma once

#include <vector>
#include "../models/LeanStat.h"



class RecordingService
{
public:

    std::vector<LeanStat> getLeanStats();


private:

    std::vector<LeanStat> leanStats;
};