#pragma once

#include <WebServer.h>

class LeanService;
class LeanScheduler;


class RecordingController
{
public:

    /**
     * @brief Create a new RecordingController.
     *
     * @param server HTTP server that hosts the REST API.
     * @param leanService returns lean stats from the repo
     * @param leanScheduler scheduler that controls the recording of lean stats 
     */
    RecordingController(
        WebServer& server,
        LeanService& leanService,
        LeanScheduler& leanScheduler);

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


    /// Handles 2 endpoints, test only utilised to get dummy data for testing the front end without having to record real data
    void getLatestLeanStats(bool testOnly);
};