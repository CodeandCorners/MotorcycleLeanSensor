
# Motorcycle lean sensor app

## Hardware
- ESP32-C3
- 3 axis sensor (MPU6050)
- VS code
- PlatformIO

## How to use
- clone repo
- install VS code
- Add PlatformIO extension
- Plugin ESP32-C3
- TBC plugin MPU6050 sensor
- Use in built in tasks from PlatformIO to "Build" and "Upload and Monitor" (there are CLI commands for this also)
- On Client (phone/laptop) connect to new WIFI network
`MotorcycleLeanSensor`
`lean12345`
- hit urls based on reasdme


### GET /test-only/recording/lean-stats/latest

Returns the latest recorded lean statistics.

Example response:

```
[
  {
    "capturedAt": "2026-07-09T12:00:00Z",
    "leanAngle": 10
  }
]
```

## State of play
- WIFI hard coded to run on specific IP ADDRESS
`http://192.168.4.1/`
- test only route added and production route added
- orchestrator added
- scheduler added
- scheudler added to main.cpp
- fake DB added (will be in memory
)