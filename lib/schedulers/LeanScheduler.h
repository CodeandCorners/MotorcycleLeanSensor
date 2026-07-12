#pragma once

class LeanOrchestrator;

class LeanScheduler
{
public:
    explicit LeanScheduler(LeanOrchestrator& orchestrator, bool defaultEnabled)
        : orchestrator(orchestrator), enabled(defaultEnabled) {};

    void startScheduler();
    void stopScheduler();
    void loop(unsigned long delayBetweenRunsMs);
    bool isSchedulerRunning();

private:
    LeanOrchestrator& orchestrator;
    bool enabled;
};