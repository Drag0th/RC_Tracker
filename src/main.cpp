#include <Arduino.h>
#include <MAVLinkHandler.h>
#include <DisplayHandler.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <Wire.h>
#include <A4988.h>
#include <AzimuthHandler.h>
#include <ESP32Encoder.h>
#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#include <ElevationHandler.h>

#define CLK 32
#define DT 33
#define SW 25

#define SERVO_MOTOR_PIN 26


SSD1306AsciiWire Display;
A4988 StepperMotor(STEPS_PER_REVOLUTION *AZIMUTH_GEAR_RATIO, STEPPER_DRIVER_DIR_PIN, STEPPER_DRIVER_STEP_PIN);
Servo ServoMotor;
ESP32Encoder Encoder;
BluetoothSerial SerialBT;

// Heading variables
float mag_heading;
String est_heading;
// Non-Blocking delay
unsigned long previous_millis;
unsigned long current_millis;
const long interval = 2000;
// Encoder variables
long encoder_position;
// GPS variables
int32_t tracker_lat;
int32_t tracker_lon;
int32_t tracker_alt_ag;
// BT variables
const char *bt_pin = "1337";
String bt_name = "MAVLink-Slave";
// Code flags
bool set_tracker_location = true;
int display_flag;
// Azimuth variables
float calculated_azimuth;
int optimized_azimuth;
int current_angle;
// Elevation variables
float calculated_elevation;
// Test
float delta_x;
float delta_y;
float tracker_object_line;

void setup()
{
  // I2C Initialization
  Wire.begin();
  // OLED Initialization
  Display.begin(&Adafruit128x64, I2C_ADDRESS);
  display_initialization(Display);
  // Stepper Motor Initialization
  StepperMotor.setSpeedProfile(A4988::LINEAR_SPEED, STEPPER_MOTOR_ACCELERATION, STEPPER_MOTOR_DECELERATION);
  StepperMotor.begin(STEPPER_MOTOR_RPM, STEPPER_MOTOR_MICROSTEPS);
  delay(100);
  StepperMotor.rotate(360);
  delay(100);
  StepperMotor.rotate(-360);
  //  Servo Initialization
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  ServoMotor.setPeriodHertz(50);
  ServoMotor.attach(SERVO_MOTOR_PIN, 500, 2400);
  ServoMotor.write(100);
  delay(1000);
  ServoMotor.write(180);
  delay(1000);
  //  Encoder Initialization
  Encoder.attachHalfQuad(DT, CLK);
  Encoder.setCount(0);
  pinMode(SW, INPUT_PULLUP);
  // BT Initialization
  SerialBT.begin(bt_name);
  SerialBT.setPin(bt_pin);
  //
  Display.clear();
  // Manual heading calibration
  while (digitalRead(SW))
  {
    if (encoder_position > (Encoder.getCount() / 2))
    {
      StepperMotor.rotate(-5);
      encoder_position = Encoder.getCount() / 2;
    }
    else if (encoder_position < (Encoder.getCount() / 2))
    {
      StepperMotor.rotate(5);
      encoder_position = Encoder.getCount() / 2;
    }
    else
    {
    }
    delay(200);
  }
  delay(1000);
}

void loop()
{
  MAVLink_receive(SerialBT);
  // Set tracker location
  while ((digitalRead(SW) == 0) && set_tracker_location)
  {
    tracker_lat = ap_lat;
    tracker_lon = ap_lon;
    tracker_alt_ag = ap_alt_ag;
    set_tracker_location = false;
  }
  // Calculate Azimuth
  if (set_tracker_location == false)
  {
    calculated_azimuth = calculate_azimuth(tracker_lat, tracker_lon, ap_lat, ap_lon);
    optimized_azimuth = optimize_azimuth(current_angle, calculated_azimuth);
    StepperMotor.rotate(optimized_azimuth);
    current_angle = calculated_azimuth;
  }
  if (set_tracker_location == false)
  {
    calculated_elevation = calculate_elevation(tracker_lat, tracker_lon, tracker_alt_ag, ap_lat, ap_lon, ap_alt_ag);
    ServoMotor.write(map(calculated_elevation, 0, 90, 180, 100));
  }
  // Non-blockin delay
  current_millis = millis();
  if (current_millis - previous_millis >= interval)
  {
    if (display_flag == 0)
    {
      display_flag = 1;
    }
    else if (display_flag == 1)
    {
      display_flag = 2;
    }
    else if (display_flag == 2)
    {
      display_flag = 3;
    }
    else if (display_flag == 3)
    {
      display_flag = 0;
    }
    previous_millis = current_millis;
  }

  // Display switch
  switch (display_flag)
  {
  case 0:
    display_MAVLink(Display);
    delay(200);
    break;
  case 1:
    display_tracker_location(Display, tracker_lat, tracker_lon, tracker_alt_ag);
    delay(200);
    break;
  case 2:
    display_azimuth(Display, calculated_azimuth, optimized_azimuth, current_angle);
    delay(200);
    break;
  case 3:
    display_elevation(Display, calculated_elevation);
    delay(200);

    break;
  default:
    break;
  }
}
