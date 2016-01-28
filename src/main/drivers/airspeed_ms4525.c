#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#include "sensor.h"
#include "airspeed.h"
#include "airspeed_ms4525.h"

#include "gpio.h"
#include "system.h"
#include "bus_i2c.h"

// MS4525, address 0x28 for the most common version
#define MS4525_ADDR                 0x28
#define STATUS_MASK                 0x3F

static bool ms4525_read(int16_t *airspeedData);

bool ms4525Detect(airspeed_t *airspeed)
{
    bool ack;
    uint8_t buf[1];

    ack = i2cRead(MS4525_ADDR, 0xFF, 1, buf);

    if(!ack)
        return false;

    airspeed->read = ms4525_read;
    airspeed->scale = 0;

    return true;
}

static bool ms4525_read(int16_t *airspeedData)
{
    uint8_t buf[4];
    int16_t data[2];

    i2cRead(MS4525_ADDR, 0xFF, 4, buf);

    uint8_t status = (buf[0] >> 5); // first two bits are status bits
    if(status == 0x00) // good data packet
    {
        data[0] = (int16_t)(((STATUS_MASK | buf[0]) << 8) | buf[1]);
        data[1] = (int16_t)((buf[2] << 3) | (buf[3] >> 5));
    }
    else if(status == 0x02) // stale data packet
    {
        data[0] = (int16_t)(((STATUS_MASK | buf[0]) << 8) | buf[1]);
        data[1] = (int16_t)((buf[2] << 3) | (buf[3] >> 5));
    }
    else
    {
        return false;
    }

    airspeedData[0] = data[0];
    airspeedData[1] = data[1];

    return true;
}
