#include "LeanScheduler.h"
#include "../orchestrators/LeanOrchestrator.h"
#include <Arduino.h>

void LeanScheduler::startScheduler()
{
    // Delete previous ride data
    orchestrator.reset();
    enabled = true;
}

void LeanScheduler::stopScheduler()
{
    enabled = false;
}

void LeanScheduler::loop(unsigned long delayBetweenRunsMs)
{
    if (!enabled)
    {
        return;
    }

    orchestrator.run();
    delay(delayBetweenRunsMs);
}

bool LeanScheduler::isSchedulerRunning()
{
    return enabled;
}
