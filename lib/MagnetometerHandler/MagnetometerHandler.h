#pragma once

#include "IST8310.h"
#include <AzimuthHandler.h>

float calc_heading(float mag_x, float mag_y);
void magnetometer_check(IST8310 &Magnetometer, Vec3f *MagnetometerValue, float &mag_x, float &mag_y, float &mag_z);
String estimate_heading(float mag_heading);
void handle_heading(IST8310 &Magnetometer, Vec3f *MagnetometerValue, float &mag_heading, String &est_heading);
