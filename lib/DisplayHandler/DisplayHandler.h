#pragma once
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C

void display_initialization(SSD1306AsciiWire &Display);