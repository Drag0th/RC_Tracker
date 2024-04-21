#include <kinematics.h>

float standarize_deg(int32_t lon_or_lat)
{
    return ((float)lon_or_lat / 10000000);
}

float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y)
{
    object_x = object_x - tracker_x;
    object_y = object_y - tracker_y;
    float standarized_object_x = standarize_deg(object_x);
    float standarized_object_y = standarize_deg(object_y);
    return ((float)(atan2(object_x, object_y)) * (180 / 3.14));
}

float optimize_azimuth(float current_deg, float destination_deg)
{
    float A, B, C;
    A = destination_deg - current_deg;
    B = destination_deg - current_deg - 360;
    B = destination_deg - current_deg + 360;
    if (abs(A) < abs(B))
    {
        if (abs(A) < abs(C))
        {
            return A;
        }
        else
        {
            return C;
        }
    }
    else
    {
        if (abs(B) < abs(C))
        {
            return B;
        }
        else
        {
            return C;
        }
    }
}