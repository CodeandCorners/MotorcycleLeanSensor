#include "LeanOrchestrator.h"
#include <Arduino.h>

LeanOrchestrator::LeanOrchestrator(LeanStatsRepo& leanStatsRepo, MPU6050Reader& mpuReader)
    : leanStatsRepo(leanStatsRepo), mpuReader(mpuReader)
{
}
void LeanOrchestrator::reset()
{
    leanStatsRepo.reset();
    Serial.println("LeanOrchestrator reset() stats in repo");
}
void LeanOrchestrator::run()
{
    mpuReader.readAndUpdateFilter();
    LeanStat newStat = mpuReader.getLeanStat();
    leanStatsRepo.update(newStat);
    Serial.println("LeanOrchestrator run() called and completed");
}
