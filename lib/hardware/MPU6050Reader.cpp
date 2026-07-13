
#include <Adafruit_MPU6050.h>
#include <MadgwickAHRS.h>
#include <time.h>
#include "../models/LeanStat.h"
#include "../util/DateTime.h"

#include "MPU6050Reader.h"

    // Pull from one library, update another
    void MPU6050Reader::readAndUpdateFilter()
    {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    filter.updateIMU(
        g.gyro.x,
        g.gyro.y,
        g.gyro.z,
        a.acceleration.x,
        a.acceleration.y,
        a.acceleration.z
    );
}

float MPU6050Reader::getRoll()
{
    return filter.getRoll();
}

float MPU6050Reader::getPitch()
{
    return filter.getPitch();
}

float MPU6050Reader::getYaw()
{
    return filter.getYaw();
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
