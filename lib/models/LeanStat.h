#pragma once

#include <Arduino.h>

 
struct LeanStat
{
    String capturedAt;

    float leanAngle;

     String toString() const
    {
        return "LeanStat{capturedAt=\"" + capturedAt +
               "\", leanAngle=" + String(leanAngle, 2) + "}";
    };
};