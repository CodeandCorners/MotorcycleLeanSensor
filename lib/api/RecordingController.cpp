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

void RecordingController::getLatestLeanStats()
{
    const std::vector<LeanStat> stats = recordingService.getLeanStats();
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
            getLatestLeanStats();
        });
}



