#include "RecordingController.h"
#include "../services/RecordingService.h"
#include <ArduinoJson.h>

RecordingController::RecordingController(
    WebServer& server,
    RecordingService& recordingService)
    : server(server),
      recordingService(recordingService)
{
}

void RecordingController::getLatestLeanStats(bool testOnly)
{
    std::vector<LeanStat> stats;

    if (testOnly)
    {
        stats = std::vector<LeanStat>{
            { "dummyDate1", 0 },
            { "dummy", 10 }
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



