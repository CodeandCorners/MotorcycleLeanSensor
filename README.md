
# ESP32 Motorcycle lean sensor tool

## Flow
1. Connect to WIFI
2. Utilise endpoints via fixed IP address
3. Start Scheduler
4. Ride
5. Stop Scheduler
6. Fetch lean stats
7. Export lean stats for further analysis

## Hardware
- ESP32 with wifi and bluetooth
- 6 axis sensor (MPU6050)

## How to use
- clone repo
- install VS code
- Add PlatformIO extension
- Plugin ESP32
- plugin MPU6050 sensor into ports

| ESP32  | MPU6050 |
|--------|---------|
| 3V3    | VCC     |
| GND    | GND     |
| GPIO21 | SDA     |
| GPIO22 | SCL     |
- Mount MPU (experiment)
Keyes MPU (red), wires to right, logo reads face up correctly to rider
(x axis left/right)
(y front of bike)

- Use in built in tasks from PlatformIO to "Build" and "Upload and Monitor" (there are CLI commands for this also) `pio run -t uploadfs -t upload -e esp32dev`
- On Client (phone/laptop) connect to new WIFI network
`MotorcycleLeanSensor`
`lean12345`

- hit urls based on readme (start is a good start)

### GET /recording/scheduler/start

Returns form && JS required to run on submit

- If the scheduler is already running, the endpoint returns `400` with the message `Scheduler is already running`.

200 response
### POST /recording/scheduler/start

Takes form from GET, form needs to contain EPOCH MS to setup ESP32 datetime (only once, will not override)

200 response


### GET /recording/scheduler/stop

Stops the lean scheduler if it is currently running.

- If the scheduler is already stopped, the endpoint returns `400` with the message `Scheduler is not running`.



### GET /recording/lean-stats/latest

Returns the latest recorded lean statistics from the recording service.
Streamed

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
- POST route added with form to send Datetime.now() from client to setup datetime on ESP32 for the first time
- Sheduler added
- scheduler disabled by default see comments in main.cpp
- Delay of scheduler set within main.cpp in loop method. `  unsigned long delayBetweenRunsMs = 10;`
- Response of results streamed as standard Json hit limit quickly
- Added "LittleFs" file system to store html file, needs to be uploaded seperately to esp32

## Notes
- platformio.ini declares dev board and nuances based on board such as log flags, might need to change if variation of ESP32

## Recommended:
POC, will fall over after a certain amount of time due to internal memory being used

- Keep interval 200MS for scheudler
- Run for < 10 mins