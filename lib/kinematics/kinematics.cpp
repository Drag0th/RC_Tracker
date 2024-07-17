#include <kinematics.h>

float standarize_deg(int32_t lon_or_lat)
{
    return (lon_or_lat / 10000000);
}

float standarize_gps(float object_position, float trakcer_position)
{
    if (trakcer_position <= 0 && object_position <= 0) // --
    {
        return object_position - trakcer_position;
    }
    if (trakcer_position > 0 && object_position > 0) // ++
    {
        return object_position - trakcer_position;
    }
    if (trakcer_position > 0 && object_position < 0) // +-
    {
        return object_position - trakcer_position;
    }
    if (trakcer_position < 0 && object_position > 0) // -+
    {
        return object_position - trakcer_position;
    }
}

float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y)
{
    object_x = standarize_gps(object_x, tracker_x);
    object_y = standarize_gps(object_y, tracker_y);
    float standarized_object_x = standarize_deg(object_x);
    float standarized_object_y = standarize_deg(object_y);
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
    float standarized_delta_x = standarize_deg(delta_x);
    float standarized_delta_y = standarize_deg(delta_y);
    float tracker_object_line = sqrt(pow(standarized_delta_x, 2) + pow(standarized_delta_y, 2) * 111);
    return (atan((object_alt / 1000000) / tracker_object_line) * (180 / 3.14));
};
