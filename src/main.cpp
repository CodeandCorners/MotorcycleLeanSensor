#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <MadgwickAHRS.h>

#include "../lib/api/RecordingController.h"
#include "../lib/services/LeanService.h"
#include "../lib/schedulers/LeanScheduler.h"
#include "../lib/orchestrators/LeanOrchestrator.h"
#include "../lib/db/LeanStatsRepo.h"
#include "../lib/hardware/MPU6050Reader.h"



const char* AP_SSID = "MotorcycleLeanSensor";
const char* AP_PASSWORD = "lean12345";

WebServer server(80);
LeanStatsRepo leanStatsRepo;
Adafruit_MPU6050 mpu;
Madgwick filter;
MPU6050Reader mpuReader(mpu, filter);
LeanOrchestrator leanOrchestrator(leanStatsRepo, mpuReader);
// lean scheduler is disabled by default, it will be enabled when the user starts recording
const bool defaultEnabled = false;
LeanScheduler leanScheduler(leanOrchestrator, defaultEnabled);
LeanService leanService(leanStatsRepo);

RecordingController recordingController(server, leanService, leanScheduler);

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

  // MPU6050, 200Hz
  Wire.begin();
  mpu.begin();
  filter.begin(200);

  // Start the HTTP server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Adjust this value as needed
  unsigned long delayBetweenRunsMs = 1000;
  leanScheduler.loop(delayBetweenRunsMs);
  server.handleClient();
}