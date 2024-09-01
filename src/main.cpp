#include <Arduino.h>
#include <MAVLinkHandler.h>
#include <DisplayHandler.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
// ################
#include <config.h>
#include <kinematics.h>
#include <A4988.h>
#include <ESP32Servo.h>

SSD1306AsciiWire Display;

void setup()
{
  // UART Initialization
  Serial.begin(115200);
  // I2C Initialization
  Wire.begin();
  // OLED Initialization
  Display.begin(&Adafruit128x64, I2C_ADDRESS);
  display_initialization(Display);
}

void loop()
{
  MAVLink_receive();
}
