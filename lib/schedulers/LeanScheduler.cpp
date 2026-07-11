#include "LeanScheduler.h"
#include "../orchestrators/LeanOrchestrator.h"
#include <Arduino.h>

LeanScheduler::LeanScheduler(LeanOrchestrator& orchestrator)
    : orchestrator(orchestrator)
{
}

bool LeanScheduler::startScheduler()
{
    enabled = true;
    return true;
}

bool LeanScheduler::stopScheduler()
{
    enabled = false;
    return true;
}

void LeanScheduler::loop()
{
    if (!enabled)
    {
        return;
    }

    orchestrator.run();
    delay(1000);
}

bool LeanScheduler::isSchedulerRunning()
{
    return enabled;
}
