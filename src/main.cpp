#include <Arduino.h>
#include <MAVLinkHandler.h>
#include <DisplayHandler.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <Wire.h>
#include "IST8310.h"
#include <MagnetometerHandler.h>
// ################
#include <config.h>
#include <kinematics.h>
#include <A4988.h>
#include <ESP32Servo.h>

#define RXD2 16
#define TXD2 17

IST8310 Magnetometer;
Vec3f *MagnetometerValue;
SSD1306AsciiWire Display;

void setup()
{
  // I2C Initialization
  Wire.begin();
  // OLED Initialization
  Display.begin(&Adafruit128x64, I2C_ADDRESS);
  display_initialization(Display);
  // UART Initialization
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  // IST8310 Initialization
  Magnetometer.setup(&Wire);
  Magnetometer.set_flip_x_y(true);
  //
  Display.clear();
}

void loop()
{
  // MAVLink_receive();
  //  display_MAVLink(Display);
  magnetometer_check(Magnetometer, MagnetometerValue);
  display_heading(Display);
  delay(200);
}
