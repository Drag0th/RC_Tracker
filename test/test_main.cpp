#include <unity.h>

float standarize_deg(int32_t lon_or_lat);
void standarize_deg_test();
float calculate_azimuth(int32_t tracker_x, int32_t tracker_y, int32_t object_x, int32_t object_y);

int main(int argc, char **argv)
{
    UNITY_BEGIN();
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
    TEST_ASSERT_EQUAL_DOUBLE(expected, acutal);
}

float calculate_azimuth(int32_t tracker_x, int32_t tracker_y, int32_t object_x, int32_t object_y)
{
}