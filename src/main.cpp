#include <Arduino.h>
#include <MAVLinkHandler.h>
#include <DisplayHandler.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <Wire.h>
#include "IST8310.h"
#include <MagnetometerHandler.h>
#include <A4988.h>
// ################
#include <config.h>
#include <kinematics.h>
#include <ESP32Servo.h>

#define RXD2 16
#define TXD2 17

IST8310 Magnetometer;
Vec3f *MagnetometerValue;
SSD1306AsciiWire Display;
A4988 StepperMotor(STEPS_PER_REVOLUTION *AZIMUTH_GEAR_RATIO, STEPPER_DRIVER_DIR_PIN, STEPPER_DRIVER_STEP_PIN);
Servo ServoMotor;

// Heading variables
float mag_heading;
String est_heading;

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
  // Stepper Motor Initialization
  StepperMotor.setSpeedProfile(A4988::LINEAR_SPEED, STEPPER_MOTOR_ACCELERATION, STEPPER_MOTOR_DECELERATION);
  StepperMotor.begin(STEPPER_MOTOR_RPM, STEPPER_MOTOR_MICROSTEPS);
  delay(100);
  StepperMotor.rotate(360);
  delay(100);
  StepperMotor.rotate(-360);
  // Servo Initialization
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  ServoMotor.setPeriodHertz(50);
  ServoMotor.attach(SERVO_MOTOR_PIN);
  ServoMotor.write(0);
  delay(100);
  //
  Display.clear();
}

void loop()
{
  // MAVLink_receive();
  //  display_MAVLink(Display);
  handle_heading(Magnetometer, MagnetometerValue, mag_heading, est_heading);
  display_heading(Display, mag_heading, est_heading);
  delay(200);
}
