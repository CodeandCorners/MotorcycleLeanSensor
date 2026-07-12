#include "LeanOrchestrator.h"
#include <Arduino.h>

LeanOrchestrator::LeanOrchestrator(LeanStatsRepo& leanStatsRepo, MPU6050Reader& mpuReader)
    : leanStatsRepo(leanStatsRepo), mpuReader(mpuReader)
{
}

void LeanOrchestrator::run()
{
    mpuReader.readAndUpdateFilter();
    LeanStat newStat = mpuReader.getLeanStat();
    leanStatsRepo.update(newStat);
    Serial.println("LeanOrchestrator run() called and completed");
}
