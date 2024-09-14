#include <MagnetometerHandler.h>

float calc_heading(float mag_x, float mag_y)
{
    return atan2(mag_y, mag_x) * (180 / PI);
}

void magnetometer_check(IST8310 &Magnetometer, Vec3f *MagnetometerValue, float &mag_x, float &mag_y, float &mag_z)
{
    Magnetometer.update();
    MagnetometerValue = Magnetometer.get_magnetometer();
    mag_x = MagnetometerValue->x;
    mag_y = MagnetometerValue->y;
    mag_z = MagnetometerValue->z;
}

String estimate_heading(float mag_heading)
{
    if ((mag_heading >= 0 && mag_heading < 36) || (mag_heading >= -36 && mag_heading < 0))
        return "N";
    else if ((mag_heading >= 36 && mag_heading < 72))
        return "NE";
    else if ((mag_heading >= 72 && mag_heading < 108))
        return "E";
    else if ((mag_heading >= 108 && mag_heading < 144))
        return "SE";
    if ((mag_heading >= 144 && mag_heading < 180) || (mag_heading >= -180 && mag_heading < -144))
        return "S";
    else if ((mag_heading >= -144 && mag_heading < -108))
        return "SW";
    else if ((mag_heading >= -108 && mag_heading < -72))
        return "W";
    else if ((mag_heading >= -72 && mag_heading < -36))
        return "NW";
}

void handle_heading(IST8310 &Magnetometer, Vec3f *MagnetometerValue, float &mag_heading, String &est_heading)
{
    float x, y, z;
    magnetometer_check(Magnetometer, MagnetometerValue, x, y, z);
    mag_heading = calc_heading(x, y);
    est_heading = estimate_heading(mag_heading);
}