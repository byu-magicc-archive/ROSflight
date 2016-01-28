#pragma once

// Type of accelerometer used/detected
typedef enum {
    AIRSPEED_DEFAULT = 0,
    AIRSPEED_NONE = 1,
    AIRSPEED_MS4525 = 2,
} airspeedSensor_e;

extern int16_t airspeedVelocity;
extern int16_t airspeedTemp;

void airspeedUpdate(uint32_t currentTime);
