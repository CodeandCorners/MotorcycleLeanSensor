#pragma once

#include <WebServer.h>
#include "../services/LeanService.h"
#include "../schedulers/LeanScheduler.h"
#include "../util/DateTime.h"

class RecordingController
{
public:

   explicit RecordingController(
        WebServer& server,
        LeanService& leanService,
        LeanScheduler& leanScheduler,
        DateTime& dateTime) : server(server),
      leanService(leanService),
      leanScheduler(leanScheduler),
      dateTime(dateTime){}

    /**
     * @brief Registers all recording-related routes with the web server.
     *
     * Call once during application startup.
     */
    void registerRoutes();

private:

    /// Reference to the web server hosting the API.
    WebServer& server;

    /// stats retriever only
    LeanService& leanService;

    LeanScheduler& leanScheduler;

    DateTime& dateTime;


    /// Handles 2 endpoints, test only utilised to get dummy data for testing the front end without having to record real data
    void getLatestLeanStats(bool testOnly);

    // Serve a static file from filesystem; returns true when file served.
    bool serveStaticFile(const String& path, const char* contentType);
};