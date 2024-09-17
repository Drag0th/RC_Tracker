#pragma once
#include <Arduino.h>

#define AZIMUTH_GEAR_RATIO 3
#define STEPS_PER_REVOLUTION 200
#define STEPPER_MOTOR_ACCELERATION 50
#define STEPPER_MOTOR_DECELERATION 50
#define STEPPER_MOTOR_MICROSTEPS 16
#define STEPPER_MOTOR_RPM 15

#define STEPPER_DRIVER_DIR_PIN 12
#define STEPPER_DRIVER_STEP_PIN 14

float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y);
int optimize_azimuth(int current_angle, int destination_angle);
float handle_azimuth(float tracker_x, float tracker_y, float object_x, float object_y, int current_angle);