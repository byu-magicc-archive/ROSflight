#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "common/axis.h"

#include "drivers/sensor.h"
#include "drivers/airspeed.h"

#include "sensors/sensors.h"
//#include "io/beeper.h"
//#include "sensors/boardalignment.h"
//#include "config/runtime_config.h"
#include "config/config.h"

#include "sensors/airspeed.h"

airspeed_t airspeed;
int16_t airspeedVelocity = 0;
int16_t airspeedTemp = 0;

void airspeedUpdate(uint32_t currentTime)
{
    static uint32_t lastMeasurement = 0;
    static int32_t delay = 50000; // ~20 hz

    if (lastMeasurement > currentTime) // protect from overflow of currentTime
        lastMeasurement = currentTime;

    if ((int32_t)(currentTime - lastMeasurement) < delay)
        return;

    lastMeasurement = currentTime;

    int16_t airspeedData[2];

    if(airspeed.read(airspeedData))
    {
        airspeedVelocity = airspeedData[0];
        airspeedTemp = airspeedData[1];
    }
}
