#pragma once

#include <WebServer.h>

class RecordingService;


class RecordingController
{
public:

    /**
     * @brief Create a new RecordingController.
     *
     * @param server HTTP server that hosts the REST API.
     * @param recordingService Business logic for recording.
     */
    RecordingController(
        WebServer& server,
        RecordingService& recordingService);

    /**
     * @brief Registers all recording-related routes with the web server.
     *
     * Call once during application startup.
     */
    void registerRoutes();

private:

    /// Reference to the web server hosting the API.
    WebServer& server;

    /// Business logic for recording.
    RecordingService& recordingService;


    /// Handles GET /recording/lean-stats/latest
    void getLatestLeanStats(bool testOnly);
};