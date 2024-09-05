#pragma once
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <MAVLinkHandler.h>
#include "IST8310.h"

#define I2C_ADDRESS 0x3C

void display_initialization(SSD1306AsciiWire &Display);
void display_MAVLink(SSD1306AsciiWire &Display);
void display_direction(SSD1306AsciiWire &Display, Vec3f *MagnetometerValue);