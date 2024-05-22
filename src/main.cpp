#include <Arduino.h>
#include <config.h>
#include <kinematics.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <A4988.h>

float tracker_x = 1, tracker_y = 1;
float current_deg = 0, calculated_azimuth = 0, optimized_azimuth = 0;
float standarized_tracker_x = 0, standarized_tracker_y = 0, standarized_test_x = 0, standarized_test_y = 0;
int32_t test_x[6] = {2, 2, 2, 1, -2, 2};
int32_t test_y[6] = {2, 1, -2, -2, 1, 1};
// 45, 90, 135, +180, -90, -45
SSD1306AsciiWire oled_display;
A4988 stepper_motor(STEPS_PER_REVOLUTION, STEPPER_DRIVER_DIR_PIN, STEPPER_DRIVER_STEP_PIN);

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
  delay(5000);
  stepper_motor.rotate(360);
  delay(100);
  stepper_motor.rotate(-360);
  oled_display.clear();
  oled_display.set1X();
  oled_display.setFont(System5x7);
}

void loop()
{
  for (int i = 0; i < 6; i++)
  {
    standarized_tracker_x = standarize_deg(tracker_x * pow(10, 7));
    standarized_tracker_y = standarize_deg(tracker_y * pow(10, 7));
    standarized_test_x = standarize_deg(test_x[i] * pow(10, 7));
    standarized_test_y = standarize_deg(test_y[i] * pow(10, 7));
    calculated_azimuth = calculate_azimuth(standarized_tracker_x, standarized_tracker_y, standarized_test_x, standarized_test_y);
    optimized_azimuth = optimize_azimuth(current_deg, calculated_azimuth);
    stepper_motor.rotate(optimized_azimuth);
    delay(100);
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
    }
    oled_display.clear();
    oled_display.println("Current_x_y: x:" + String(test_x[i]) + " y:" + String(test_y[i]));
    oled_display.println("Current_deg: " + String((int)current_deg));
    oled_display.println("Destination_deg: " + String((int)calculated_azimuth));
    oled_display.println("Optimized_move: " + String((int)optimized_azimuth));
    current_deg = calculated_azimuth;
  }
}
