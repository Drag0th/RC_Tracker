#pragma once
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <MAVLinkHandler.h>
#include "IST8310.h"
#include <MagnetometerHandler.h>
#include <AzimuthHandler.h>

#define I2C_ADDRESS 0x3C

void display_initialization(SSD1306AsciiWire &Display);
void display_MAVLink(SSD1306AsciiWire &Display);
void display_heading(SSD1306AsciiWire &Display, float mag_heading, String est_heading);