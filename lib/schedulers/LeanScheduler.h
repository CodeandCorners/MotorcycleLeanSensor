#pragma once

class LeanOrchestrator;

class LeanScheduler
{
public:
    explicit LeanScheduler(LeanOrchestrator& orchestrator);

    bool startScheduler();
    bool stopScheduler();
    void loop();
    bool isSchedulerRunning();

private:
    LeanOrchestrator& orchestrator;
    bool enabled = false;
};