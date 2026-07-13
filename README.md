
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
- Need to upload image & Build to Esp32 (2 seperate uploads) `pio run -t uploadfs -t upload -e esp32dev`
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
- Delay of scheduler set within main.cpp in loop method
- Response of results streamed as standard Json hit limit quickly
- Added "LittleFs" file system to store html file, needs to be uploaded seperately to esp32

## Notes
- platformio.ini declares dev board, might need to change if variation of ESP32
- will this run out memory if left unattended, probably
