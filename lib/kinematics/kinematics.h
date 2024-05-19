#pragma once

#include <math.h>
#include <config.h>

float standarize_deg(int32_t lon_or_lat);
float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y);
int optimize_azimuth(int current_deg, int destination_deg);