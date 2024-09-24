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

void display_heading(SSD1306AsciiWire &Display, float mag_heading, String est_heading)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set1X();
    Display.println("Magnetometer:");
    Display.set1X();
    Display.print("Heading_Deg: ");
    Display.println(mag_heading, 2);
    Display.print("Heading_Est: ");
    Display.println(est_heading);
}

void display_tracker_location(SSD1306AsciiWire &Display, int32_t tracker_lat, int32_t tracker_lon, int32_t tracker_alt_ag)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set2X();
    Display.println("  Tracker ");
    Display.set1X();
    Display.print("Lattitude: ");
    Display.println(tracker_lat / 1E7, 7);
    Display.print("Longitude: ");
    Display.println(tracker_lon / 1E7, 7);
    Display.print("Altitude [AGL]: ");
    Display.println(tracker_alt_ag / 1000);
}

void display_azimuth(SSD1306AsciiWire &Display, float calculated_azimuth, int optimized_azimuth, int current_angle)
{
    Display.clear();
    Display.setFont(System5x7);
    Display.set2X();
    Display.println("  Azimuth ");
    Display.set1X();
    Display.print("Calc_Az: ");
    Display.println(calculated_azimuth, 6);
    Display.print("Opt_Az: ");
    Display.println(optimized_azimuth);
    Display.print("Curr_An: ");
    Display.println(current_angle);
}