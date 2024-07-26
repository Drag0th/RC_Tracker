#include <kinematics.h>

float standarize_gps(float object_position, float trakcer_position)
{
    return object_position - trakcer_position;
}

float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y)
{
    object_x = standarize_gps(object_x, tracker_x);
    object_y = standarize_gps(object_y, tracker_y);
    return ((atan2(object_x, object_y)) * (180 / 3.14));
}

int optimize_azimuth(int current_deg, int destination_deg)
{
    int A, B, C;
    A = destination_deg - current_deg;
    B = destination_deg - current_deg - 360;
    C = destination_deg - current_deg + 360;
    if (fabs(A) < fabs(B))
    {
        if (fabs(A) < fabs(C))
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
        if (fabs(B) < fabs(C))
        {
            return B;
        }
        else
        {
            return C;
        }
    }
}

float calculate_elevation(float tracker_x, float tracker_y, float object_x, float object_y, float object_alt)
{
    float delta_x = standarize_gps(object_x, tracker_x);
    float delta_y = standarize_gps(object_y, tracker_y);
    float tracker_object_line = sqrt(pow(delta_x * DEG_KM_RATIO, 2) + pow(delta_y * DEG_KM_RATIO, 2));
    return (atan(object_alt / tracker_object_line) * (180 / 3.14));
}