#include "LeanOrchestrator.h"
#include <Arduino.h>

LeanOrchestrator::LeanOrchestrator(LeanStatsRepo& leanStatsRepo)
    : leanStatsRepo(leanStatsRepo)
{
}

void LeanOrchestrator::run()
{
    Serial.println("LeanOrchestrator run() called");
}
