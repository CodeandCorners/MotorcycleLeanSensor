#pragma once

#include <vector>
#include "../models/LeanStat.h"


class LeanScheduler;
class LeanStatsRepo;

class RecordingService
{
public:
    RecordingService(LeanScheduler& scheduler, LeanStatsRepo& stats);

    std::vector<LeanStat> getLeanStats();

    void startRecording();
    void stopRecording();

private:
    LeanScheduler& leanScheduler;
    LeanStatsRepo& leanStatsRepo;
};