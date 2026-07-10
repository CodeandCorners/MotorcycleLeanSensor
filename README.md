
# Motorcycle lean sensor app

## Hardware
- ESP32-C3
- 3 axis sensor

### GET /recording/lean-stats/latest

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
-Currently hopefully does something with WIFI
- Currently hosts a basic REST GET API returning dummy data
- Hosts wifi network
- Returns dummy data on fixed URL

## TODO

- New endpoint to maybe POKE sensor to get current stat, maybe class as test only?/ ping ping
- Implement start and stop recording functionality (scheduler every x seconds? or do we just record every time movement is > 0?)
- look into if int is enough for angle?
- look into memory usage, are we going to have to store a small amount? / for only 5 mins? overwrite. how does it work??


