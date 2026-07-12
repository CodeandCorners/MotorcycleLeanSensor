
# Motorcycle lean sensor app

## Hardware
- ESP32 with wifi and bluetooth
- 6 axis sensor (MPU6050)


## How to use
- clone repo
- install VS code
- Add PlatformIO extension
- Plugin ESP32
- plugin MPU6050 sensor into ports
ESP32                     MPU6050
-----                     -------
3V3   ------------------> VCC
GND   ------------------> GND
GPIO21 -----------------> SDA
GPIO22 -----------------> SCL
- Use in built in tasks from PlatformIO to "Build" and "Upload and Monitor" (there are CLI commands for this also)
- On Client (phone/laptop) connect to new WIFI network
`MotorcycleLeanSensor`
`lean12345`
- hit urls based on readme

### GET /recording/scheduler/start

Starts the lean scheduler if it is not already running.

- If the scheduler is already running, the endpoint returns `400` with the message `Scheduler is already running`.

### GET /recording/scheduler/stop

Stops the lean scheduler if it is currently running.

- If the scheduler is already stopped, the endpoint returns `400` with the message `Scheduler is not running`.



### GET /recording/lean-stats/latest

Returns the latest recorded lean statistics from the recording service.

Example response:

```
[
  {
    "capturedAt": "2026-07-09T12:00:00Z",
    "leanAngle": 10
  }
]
```

### GET /test-only/recording/lean-stats/latest

Returns dummy lean statistics for testing purposes.

Example response:

```
[
  {
    "capturedAt": "dummyDate1",
    "leanAngle": 0
  },
  {
    "capturedAt": "dummyDate2",
    "leanAngle": 10
  },
  {
    "capturedAt": "dummyDate3",
    "leanAngle": -10
  }
]
```

## Whats built
- WIFI hard coded to run on specific IP ADDRESS
`http://192.168.4.1/`
- test only route added to test connectivity and format of response
- routes added to start and stop RIDE
- Sheduler added
- scheduler disabled by default see comments in main.cpp
- Delay of scheduler set within main.cpp in loop method

## Notes
- platformio.ini declares dev board, might need to change if variation of ESP32