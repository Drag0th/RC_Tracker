#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>
#include <config.h>

float standarize_deg(float lon_or_lat);
float calculate_azimuth(float tracker_x, float tracker_y, float object_x, float object_y);
float standarize_gps(float object_position, float trakcer_position);
int optimize_azimuth(int current_deg, int destination_deg);
float calculate_elevation(float tracker_x, float tracker_y, float object_x, float object_y, float object_alt);
float elevation_control(float current_angle, float destination_angle);