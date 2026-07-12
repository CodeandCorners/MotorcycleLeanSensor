#include "RecordingController.h"
#include "../services/LeanService.h"
#include "../schedulers/LeanScheduler.h"
#include <ArduinoJson.h>

RecordingController::RecordingController(
    WebServer& server,
    LeanService& leanService,
    LeanScheduler& leanScheduler)
    : server(server),
      leanService(leanService),
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
            { "dummyDate2", 10.1f },
            { "dummyDate3", -10.2f }
        };
    }
    else
    {
        stats = leanService.getLeanStats();
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
            server.send(200, "text/plain", "Ride started, deleted previous ride data, recording new lean stats now");
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
            server.send(200, "text/plain", "Ride stopped, recording stopped");
        });


    // Return the current recorded stats.
    server.on(
        "/recording/lean-stats/latest",
        HTTP_GET,
        [this]()
        {
            getLatestLeanStats(false);
        });

            // Test-Only Dummy Data.
    server.on(
        "/test-only/recording/lean-stats/latest",
        HTTP_GET,
        [this]()
        {
            getLatestLeanStats(true);
        });
}



