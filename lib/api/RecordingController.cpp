#include "RecordingController.h"
#include "../services/LeanService.h"
#include "../schedulers/LeanScheduler.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <WiFi.h>
#include "../util/DateTime.h"

   

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

    // Stream JSON array directly to client using server.sendContent()
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.sendHeader("Content-Type", "application/json");
    server.sendHeader("Connection", "close");
    server.send(200, "application/json", "");

    server.sendContent("[");
    bool first = true;

    for (const LeanStat& stat : stats)
    {
        if (!first) server.sendContent(",");
        first = false;

        StaticJsonDocument<256> doc; // per-object pool
        JsonObject obj = doc.to<JsonObject>();
        obj["capturedAt"] = stat.capturedAt;
        obj["leanAngle"] = stat.leanAngle;

        String out;
        serializeJson(doc, out);
        server.sendContent(out);
    }

    server.sendContent("]");
    server.sendContent("");
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
                server.send(200, "text/plain", "Scheduler is already running");
                return;
            }
            if (!serveStaticFile("/StartRecording.html", "text/html")) {
                // serveStaticFile already sent an error response
                return;
            }
        });

       server.on(
    "/recording/scheduler/start",
    HTTP_POST,
    [this]()
    {
        if (leanScheduler.isSchedulerRunning())
        {
            server.send(400, "text/plain", "Scheduler is already running");
            return;
        }

        // server.arg should be validated, but too messy for POC
        uint64_t clientEpochMS = strtoull(server.arg("epoch").c_str(), nullptr, 10);

        Serial.printf("Client epoch: %llu\n", clientEpochMS);
        // Important, only works once, first client wins
        dateTime.setCurrentDateTime(clientEpochMS);
        leanScheduler.startScheduler();

        server.send(200, "text/plain", "Ride started ");
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
};
// co pilot did this, too much error handling for poc, but its in now
bool RecordingController::serveStaticFile(const String& path, const char* contentType)
{
    if (!LittleFS.exists(path)) {
        server.send(404, "text/plain", "Not found");
        return false;
    }

    File f = LittleFS.open(path, "r");
    if (!f) {
        server.send(500, "text/plain", "Failed to open file");
        return false;
    }

    server.streamFile(f, contentType);
    f.close();
    return true;
};



