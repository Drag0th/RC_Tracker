#include <ElevationHandler.h>

float calculate_elevation(float tracker_x, float tracker_y, float tracker_alt, float object_x, float object_y, float object_alt)
{
    float delta_x = (float(object_x) - float(tracker_x)) / 1E7;
    float delta_y = (float(object_y) - float(tracker_y)) / 1E7;
    float tracker_object_line = sqrt(pow(delta_x * DEG_M_RATIO, 2) + pow(delta_y * DEG_M_RATIO, 2));
    return (atan(((object_alt / 1000) - (tracker_alt / 1000)) / tracker_object_line) * (180 / 3.14));
}