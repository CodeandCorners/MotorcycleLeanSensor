#pragma once

#include "../db/LeanStatsRepo.h"

class LeanOrchestrator
{
public:
    explicit LeanOrchestrator(LeanStatsRepo& leanStatsRepo, MPU6050Reader& mpuReader);
    void run();

private:
    LeanStatsRepo& leanStatsRepo;
    MPU6050Reader& mpuReader;
};
