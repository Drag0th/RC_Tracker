#include <MagnetometerHandler.h>

float mag_x, mag_y, mag_z;

void magnetometer_check(IST8310 &Magnetometer, Vec3f *MagnetometerValue)
{
    Magnetometer.update();
    MagnetometerValue = Magnetometer.get_magnetometer();
    mag_x = MagnetometerValue->x;
    mag_y = MagnetometerValue->y;
    mag_z = MagnetometerValue->z;
}