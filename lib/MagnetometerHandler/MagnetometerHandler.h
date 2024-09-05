#pragma once

#include "IST8310.h"
#include <AzimuthHandler.h>

extern float mag_x, mag_y, mag_z;

void magnetometer_check(IST8310 &Magnetometer, Vec3f *MagnetometerValue);