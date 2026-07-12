#include "RecordingController.h"
#include "../services/RecordingService.h"
#include "../schedulers/LeanScheduler.h"
#include <ArduinoJson.h>

RecordingController::RecordingController(
    WebServer& server,
    RecordingService& recordingService,
    LeanScheduler& leanScheduler)
    : server(server),
      recordingService(recordingService),
      leanScheduler(leanScheduler) 
{
}

void RecordingController::getLatestLeanStats(bool testOnly)
{
    std::vector<LeanStat> stats;

    if (testOnly)
    {
        stats = std::vector<LeanStat>{
            { "dummyDate1", 0.0f },
            { "dummyDate2", 10.0f },
            { "dummyDate3", -10.0f }
        };
    }
    else
    {
        stats = recordingService.getLeanStats();
    }

    StaticJsonDocument<512> doc;
    JsonArray array = doc.to<JsonArray>();

    for (const LeanStat& stat : stats)
    {
        JsonObject obj = array.createNestedObject();
        obj["capturedAt"] = stat.capturedAt;
        obj["leanAngle"] = stat.leanAngle;
    }

    String payload;
    serializeJson(doc, payload);
    server.send(200, "application/json", payload);
}

void RecordingController::registerRoutes()
{

    server.on(
        "/recording/scheduler/start",
        HTTP_GET,
        [this]()
        {
            if (leanScheduler.isSchedulerRunning())
            {
                server.send(400, "text/plain", "Scheduler is already running");
                return;
            }
            leanScheduler.startScheduler();
        });
            server.on(
        "/recording/scheduler/stop",
        HTTP_GET,
        [this]()
        {
            if (!leanScheduler.isSchedulerRunning())
            {
                server.send(400, "text/plain", "Scheduler is not running");
                return;
            }
            leanScheduler.stopScheduler();
        });


    server.on(
        "/recording/lean-stats/latest",
        HTTP_GET,
        [this]()
        {
            getLatestLeanStats(false);
        });

    server.on(
        "/test-only/recording/lean-stats/latest",
        HTTP_GET,
        [this]()
        {
            getLatestLeanStats(true);
        });
}



