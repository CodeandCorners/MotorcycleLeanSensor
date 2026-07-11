#pragma once

#include "../db/LeanStatsRepo.h"

class LeanOrchestrator
{
public:
    explicit LeanOrchestrator(LeanStatsRepo& leanStatsRepo);
    void run();

private:
    LeanStatsRepo& leanStatsRepo;
};
