#pragma once

#include <math.h>
#include <config.h>

float standarize_deg(int32_t lon_or_lat);
float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y);
float optimize_azimuth(float current_deg, float destination_deg);