#include <Arduino.h>
#include <config.h>
#include <kinematics.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <A4988.h>
#include <ESP32Servo.h>

// Variables:
//  -Tracker postition
float tracker_x = 1;
float tracker_y = 1;
//  -Azimuth variables
float current_azimuth_deg = 0;
float current_elevation_deg = 0;
float calculated_azimuth = 0;
float calculated_elevation = 0;
float optimized_azimuth = 0;
//  -Test object variables
int32_t test_x[6] = {2, 2, 2, 1, -2, 2};
int32_t test_y[6] = {2, 1, -2, -2, 1, 1};
// Azimuth_deg: 45, 90, 135, +180, -90, -45
int32_t test_alt[6] = {2, 1, -2, -2, 1, 1};

SSD1306AsciiWire oled_display;
A4988 stepper_motor((STEPS_PER_REVOLUTION * AZIMUTH_GEAR_RATIO), STEPPER_DRIVER_DIR_PIN, STEPPER_DRIVER_STEP_PIN);
Servo servo_motor;

void setup()
{
  Wire.begin();
  Wire.setClock(400000L);
  oled_display.begin(&Adafruit128x32, I2C_ADDRESS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  oled_display.set2X();
  oled_display.setFont(System5x7);
  oled_display.println("BOOTING");
  stepper_motor.setSpeedProfile(A4988::LINEAR_SPEED, STEPPER_MOTOR_ACCELERATION, STEPPER_MOTOR_DECELERATION);
  stepper_motor.begin(STEPPER_MOTOR_RPM, STEPPER_MOTOR_MICROSTEPS);
  stepper_motor.rotate(-360);
  stepper_motor.rotate(360);
  servo_motor.attach(SERVO_MOTOR_PIN);
  oled_display.clear();
  oled_display.set1X();
  oled_display.setFont(System5x7);
}

void loop()
{
  for (int i = 0; i < 6; i++)
  {
    calculated_azimuth = calculate_azimuth(tracker_x, tracker_y, test_x[i], test_y[i]);
    optimized_azimuth = optimize_azimuth(current_azimuth_deg, calculated_azimuth);
    delay(100);
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
    }
    oled_display.clear();
    oled_display.println("Current_x_y: x:" + String(test_x[i]) + " y:" + String(test_y[i]));
    oled_display.println("Current_azimuth_deg: " + String((int)current_azimuth_deg));
    oled_display.println("Destination_deg: " + String((int)calculated_azimuth));
    oled_display.println("Optimized_move: " + String((int)optimized_azimuth));
    stepper_motor.rotate(optimized_azimuth);
    current_azimuth_deg = calculated_azimuth;
    calculated_elevation = calculate_elevation(tracker_x, tracker_y, test_x[i], test_y[i], test_alt[i]);
    delay(100);
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
    }
    oled_display.clear();
    oled_display.println("Current_alt: " + String(test_alt[i]));
    oled_display.println("Current_elevation_deg: " + String((int)current_elevation_deg));
    oled_display.println("Destination_elevation: " + String((int)calculated_elevation));
    servo_motor.write(calculated_elevation);
    current_elevation_deg = calculated_elevation;
  }
}
