#pragma once

#include <math.h>

#define DEG_M_RATIO 111000

float calculate_elevation(float tracker_x, float tracker_y, float tracker_alt, float object_x, float object_y, float object_alt);