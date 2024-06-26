#include <unity.h>
#include <config.h>

float standarize_deg(int32_t lon_or_lat);
void standarize_deg_test();
float calculate_azimuth(int32_t tracker_x, int32_t tracker_y, int32_t object_x, int32_t object_y);
void calculate_azimuth_test();
int optimize_azimuth(int current_deg, int destination_deg);
void optimze_azimuth_test();
float standarize_gps(float object_position, float trakcer_position);
void standarize_gps_test();
float calculate_elevation(float tracker_x, float tracker_y, float object_x, float object_y, float object_alt);
void calculate_elevation_test();

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(standarize_deg_test);
    RUN_TEST(calculate_azimuth_test);
    RUN_TEST(standarize_deg_test);
    RUN_TEST(optimze_azimuth_test);
    RUN_TEST(standarize_gps_test);
    RUN_TEST(calculate_elevation_test);
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
    object_x = standarize_gps(object_x, tracker_x);
    object_y = standarize_gps(object_y, tracker_y);
    float standarized_object_x = standarize_deg(object_x);
    float standarized_object_y = standarize_deg(object_y);
    return ((atan2(object_x, object_y)) * (180 / 3.14));
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

int optimize_azimuth(int current_deg, int destination_deg)
{
    int A, B, C;
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
    int expected = 45;
    int acutal = optimize_azimuth(116, 161);
    TEST_ASSERT_EQUAL_INT(expected, acutal);
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

void standarize_gps_test()
{
    float tracker_x[5] = {1, -1, 2, -2, 3.25};
    float object_x[5] = {1, -1, -2, 2, -1.25};
    float acutal = standarize_gps(object_x[0], tracker_x[0]);
    TEST_ASSERT_EQUAL_FLOAT(0, acutal);
    float acutal1 = standarize_gps(object_x[1], tracker_x[1]);
    TEST_ASSERT_EQUAL_FLOAT(0, acutal1);
    float acutal2 = standarize_gps(object_x[2], tracker_x[2]);
    TEST_ASSERT_EQUAL_FLOAT(-4, acutal2);
    float acutal3 = standarize_gps(object_x[3], tracker_x[3]);
    TEST_ASSERT_EQUAL_FLOAT(4, acutal3);
    float acutal4 = standarize_gps(object_x[4], tracker_x[4]);
    TEST_ASSERT_EQUAL_FLOAT(-4.5, acutal4);
}

float calculate_elevation(float tracker_x, float tracker_y, float object_x, float object_y, float object_alt)
{
    float delta_x = standarize_gps(object_x, tracker_x);
    float delta_y = standarize_gps(object_y, tracker_y);
    float standarized_delta_x = standarize_deg(delta_x) * 111;
    float standarized_delta_y = standarize_deg(delta_y) * 111;
    float tracker_object_line = sqrt(pow(standarized_delta_x, 2) + pow(standarized_delta_y, 2));
    return (atan(tracker_object_line / (object_alt / 1000000)) * (180 / 3.14));
};

void calculate_elevation_test()
{
    float acutal = calculate_elevation(pow(10, 7), pow(10, 7), pow(10, 7) * 2, pow(10, 7) * 2, pow(10, 6) * 1);
    TEST_ASSERT_EQUAL_FLOAT(89.68, acutal);
}