#include <AzimuthHandler.h>

float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y)
{
    float ref_x, ref_y, calculated_az;
    ref_x = object_x - tracker_x;
    ref_y = object_y - tracker_y;
    calculated_az = ((atan2(ref_y, ref_x)) * (180 / PI));
    if (calculated_az > 0)
        return calculated_az;
    else
        return (180 - calculated_az) + 180;
}

int optimize_azimuth(int current_angle, int destination_angle)
{
    int A, B, C;
    A = destination_angle - current_angle;
    B = destination_angle - current_angle - 360;
    C = destination_angle - current_angle + 360;
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

float handle_azimuth(float tracker_x, float tracker_y, float object_x, float object_y, int current_angle)
{
    float calculated_azimuth;
    calculated_azimuth = calculate_azimuth(tracker_x, tracker_y, object_x, object_y);
    return optimize_azimuth(current_angle, calculated_azimuth);
}