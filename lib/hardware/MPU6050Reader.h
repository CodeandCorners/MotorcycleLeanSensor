#pragma once
#include <Adafruit_MPU6050.h>
#include <MadgwickAHRS.h>
#include "../models/LeanStat.h"


class MPU6050Reader
{
public:
    MPU6050Reader(Adafruit_MPU6050& mpu, Madgwick& filter);

    // Pull from one library, update another
    void readAndUpdateFilter();

    float getRoll();
    // not used
    float getPitch();
    // not used
    float getYaw();

   String getCurrentDateTime();

    LeanStat getLeanStat();

private:
    Adafruit_MPU6050& mpu;
    Madgwick& filter;

};
