#pragma once
#include <Adafruit_MPU6050.h>
#include <MadgwickAHRS.h>
#include "../models/LeanStat.h"
#include "../util/DateTime.h"

class MPU6050Reader
{
public:
    explicit MPU6050Reader(Adafruit_MPU6050& mpu, Madgwick& filter, DateTime& dateTime) : mpu(mpu), filter(filter), dateTime(dateTime) {};

    // Pull from one library, update another
    void readAndUpdateFilter();

    float getRoll();
    // not used
    float getPitch();
    // not used
    float getYaw();

    // Its calling mutable, forced immutable after set DateTime helper
    String getCurrentDateTime();

    LeanStat getLeanStat();

private:
    Adafruit_MPU6050& mpu;
    Madgwick& filter;
    DateTime& dateTime;
};
