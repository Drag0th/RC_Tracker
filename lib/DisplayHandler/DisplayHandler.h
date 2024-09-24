#pragma once
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <MAVLinkHandler.h>
#include "IST8310.h"
#include <MagnetometerHandler.h>

#define I2C_ADDRESS 0x3C

void display_initialization(SSD1306AsciiWire &Display);
void display_MAVLink(SSD1306AsciiWire &Display);
void display_heading(SSD1306AsciiWire &Display, float mag_heading, String est_heading);
void display_tracker_location(SSD1306AsciiWire &Display, int32_t tracker_lat, int32_t tracker_lon, int32_t tracker_alt_ag);
void display_azimuth(SSD1306AsciiWire &Display, float calculated_azimuth, int optimized_azimuth, int current_angle);
void display_elevation(SSD1306AsciiWire &Display, float calculated_elevation);