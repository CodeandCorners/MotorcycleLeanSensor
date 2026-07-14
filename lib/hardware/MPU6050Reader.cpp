
#include <Adafruit_MPU6050.h>
#include <math.h>

#include "../models/LeanStat.h"
#include "../util/DateTime.h"

#include "MPU6050Reader.h"

static float roll = 0.0f;
static float pitch = 0.0f;

void MPU6050Reader::readAndUpdateFilter()
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Accelerometer values (m/s²)
    float ax = a.acceleration.x;
    float ay = a.acceleration.y;
    float az = a.acceleration.z;

    // Calculate angles directly from gravity
    roll  = atan2f(ay, az) * 180.0f / PI;
    pitch = atan2f(-ax, sqrtf(ay * ay + az * az)) * 180.0f / PI;

}

float MPU6050Reader::getRoll()
{
    return roll;
}

float MPU6050Reader::getPitch()
{
    return pitch;
}

float MPU6050Reader::getYaw()
{
    // Cannot determine yaw from an accelerometer alone.
    return 0.0f;
}

LeanStat MPU6050Reader::getLeanStat()
{
    LeanStat stat;
    stat.capturedAt = getCurrentDateTime();
    stat.leanAngle = getRoll();
    return stat;
}

// complicated because millis has to be calculated seperately library apparently doesn't provide milliseconds in the time struct
String MPU6050Reader::getCurrentDateTime()
{
    u_int64_t currentEpochMs = dateTime.getCurrentEpochMs();
    String userFriendlyTime = dateTime.convertEpochMSToUserFriendlyTimeStamp(currentEpochMs);
    return userFriendlyTime;
  
}
