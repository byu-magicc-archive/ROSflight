#pragma once

typedef struct airspeed_s {
    sensorInitFuncPtr init;                                 // initialize function
    sensorReadFuncPtr read;                                 // read data function pressure and temp
    float scale;                                            // scalefactor (currently used for gyro only, todo for accel)
} airspeed_t;
