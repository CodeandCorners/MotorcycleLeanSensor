#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "../lib/api/RecordingController.h"
#include "../lib/services/RecordingService.h"
#include "../lib/schedulers/LeanScheduler.h"
#include "../lib/orchestrators/LeanOrchestrator.h"
#include "../lib/db/LeanStatsRepo.h"

const char* AP_SSID = "MotorcycleLeanSensor";
const char* AP_PASSWORD = "lean12345";

WebServer server(80);
LeanStatsRepo leanStatsRepo;
LeanOrchestrator leanOrchestrator(leanStatsRepo);
LeanScheduler leanScheduler(leanOrchestrator);
RecordingService recordingService(leanScheduler, leanStatsRepo);

RecordingController recordingController(server, recordingService);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting Wi-Fi access point...");
  WiFi.mode(WIFI_AP);
  //http://192.168.4.1/recording/lean-stats/latest
  // driven by config
  IPAddress local_IP(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  bool apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD);

  if (!apStarted) {
    Serial.println("Failed to start access point");
    return;
  }

  recordingController.registerRoutes();
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  leanScheduler.loop();
  server.handleClient();
}