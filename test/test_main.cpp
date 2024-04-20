#include <unity.h>
#include <config.h>

float standarize_deg(int32_t lon_or_lat);
void standarize_deg_test();
float calculate_azimuth(int32_t tracker_x, int32_t tracker_y, int32_t object_x, int32_t object_y);
void calculate_azimuth_test();
float optimize_azimuth(float current_deg, float destination_deg);
void optimze_azimuth_test();

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(standarize_deg_test);
    RUN_TEST(calculate_azimuth_test);
    RUN_TEST(standarize_deg_test);
    UNITY_END();
    return 0;
}

float standarize_deg(int32_t lon_or_lat)
{
    return ((float)lon_or_lat / 10000000);
}

void standarize_deg_test()
{
    int32_t lon_or_lat = 61.256 * pow(10, 7);
    float expected = 61.256;
    float acutal = standarize_deg(lon_or_lat);
    TEST_ASSERT_EQUAL_FLOAT(expected, acutal);
}

float calculate_azimuth(int32_t tracker_x, int32_t tracker_y, int32_t object_x, int32_t object_y)
{
    object_x = object_x - tracker_x;
    object_y = object_y - tracker_y;
    float standarized_object_x = standarize_deg(object_x);
    float standarized_object_y = standarize_deg(object_y);
    return ((float)(atan2(object_x, object_y)) * (180 / PI));
}

void calculate_azimuth_test()
{
    int32_t tracker_x = 1 * pow(10, 7);
    int32_t tracker_y = 1 * pow(10, 7);
    int32_t object_x = 2 * pow(10, 7);
    int32_t object_y = 2 * pow(10, 7);
    float expected = 45.02282;
    float acutal = calculate_azimuth(tracker_x, tracker_y, object_x, object_y);
    TEST_ASSERT_EQUAL_FLOAT(expected, acutal);
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

void optimze_azimuth_test()
{
    float expected = -32.4;
    float acutal = optimize_azimuth(20, 352.4);
    TEST_ASSERT_EQUAL_FLOAT(expected, acutal);
}