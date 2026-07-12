#pragma once

#include "../db/LeanStatsRepo.h"
#include "../hardware/MPU6050Reader.h"

class LeanOrchestrator
{
public:
    explicit LeanOrchestrator(LeanStatsRepo& leanStatsRepo, MPU6050Reader& mpuReader);
    void run();
    void reset();

private:
    LeanStatsRepo& leanStatsRepo;
    MPU6050Reader& mpuReader;
};
