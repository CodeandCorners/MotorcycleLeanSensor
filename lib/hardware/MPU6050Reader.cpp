
#include <Adafruit_MPU6050.h>
#include <MadgwickAHRS.h>
#include <time.h>
#include "../models/LeanStat.h"

#include "MPU6050Reader.h"

 MPU6050Reader::MPU6050Reader(Adafruit_MPU6050& mpu, Madgwick& filter) : mpu(mpu), filter(filter) {}


    // Pull from one library, update another
    void MPU6050Reader::readAndUpdateFilter()
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

    const float degToRad = 3.14159265359f / 180.0f;
    float gx = g.gyro.x * degToRad;
    float gy = g.gyro.y * degToRad;
    float gz = g.gyro.z * degToRad;

    filter.updateIMU(gx, gy, gz, a.acceleration.x, a.acceleration.y, a.acceleration.z);
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
    time_t now = time(nullptr);
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    unsigned long ms = millis() % 1000;

    char buffer[32];
    snprintf(buffer, sizeof(buffer),
             "%04d-%02d-%02dT%02d:%02d:%02d.%03luZ",
             timeinfo.tm_year + 1900,
             timeinfo.tm_mon + 1,
             timeinfo.tm_mday,
             timeinfo.tm_hour,
             timeinfo.tm_min,
             timeinfo.tm_sec,
             ms);

    return String(buffer);
}
