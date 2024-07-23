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
float optimized_elevation = 0;
//  -Test object variables
int32_t test_x[6] = {2, 2, 2, 2, 2, 4};
int32_t test_y[6] = {2, 2, 2, 2, 2, 5};
// Azimuth_deg: 45, 90, 135, +180, -90, -45
float test_alt[6] = {0.05, 0.1, 0.05, 0.156, 0.05, 150};
// Elevation_deg: 45, 30, 15, 45, 15, 14

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
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo_motor.setPeriodHertz(50);
  servo_motor.attach(SERVO_MOTOR_PIN);
  oled_display.clear();
  oled_display.set1X();
  oled_display.setFont(System5x7);
}

void loop()
{
  for (int i = 0; i < 6; i++)
  {
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
    }
    delay(200);
    calculated_elevation = calculate_elevation(tracker_x * 10000, tracker_y * 10000, test_x[i] * 10000, test_y[i] * 1000, test_alt[i] * 1000000);
    optimized_elevation = elevation_control(current_elevation_deg, calculated_elevation);
    float time_delay = ((0.165 * abs(optimized_elevation)) / 60) * 1000;
    oled_display.println("Alt: " + String(test_alt[i]));
    oled_display.println("C_elevation: " + String(current_elevation_deg));
    oled_display.println("Destination: " + String(calculated_elevation));
    oled_display.println("Optimized: " + String(optimized_elevation));
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
    }
    current_elevation_deg = calculated_elevation;
    delay(200);
    if (optimized_elevation > 0)
    {
      servo_motor.write(65);
      delay(time_delay);
      servo_motor.write(90);
    }
    else
    {
      servo_motor.write(125);
      delay(time_delay);
      servo_motor.write(90);
    }
  }
}
