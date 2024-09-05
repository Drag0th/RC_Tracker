#include <DisplayHandler.h>

void display_initialization(SSD1306AsciiWire &Display)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set2X();
    Display.println(" ");
    Display.println("  BOOTING ");
    Display.println("    UP    ");
}

void display_MAVLink(SSD1306AsciiWire &Display)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set2X();
    Display.println("  MAVLink ");
    Display.set1X();
    Display.print("Lattitude: ");
    Display.println(ap_lat / 1E7, 7);
    Display.print("Longitude: ");
    Display.println(ap_lon / 1E7, 7);
    Display.print("Altitude [AGL]: ");
    Display.println(ap_alt_ag / 1000);
    Display.print("GPS Fixtype: ");
    Display.println(ap_fixtype);
}

void display_direction(SSD1306AsciiWire &Display, Vec3f *MagnetometerValue)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set1X();
    Display.println("Magnetometer:");
    Display.set1X();
    Display.print("X: ");
    Display.println(MagnetometerValue->x, 7);
    Display.print("Y: ");
    Display.println(MagnetometerValue->y, 7);
    Display.print("Z: ");
    Display.println(MagnetometerValue->z, 7);
}