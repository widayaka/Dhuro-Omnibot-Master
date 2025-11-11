#include "robot_display.h"
#include "robot_gpio.h"
#include "robot_serial.h"
#include "robot_motor_encoder.h"
#include "robot_program_mode.h"
#include "robot_rtos_handler.h"

#include <EEPROM.h>
#include <Ps3Controller.h>
#define JOYSTICK_MACADDRESS "4a:e5:4a:ec:a1:00"

#define EEPROM_SIZE 64

void setup() {
  robotSerial_init();
  robotDisplay_init();
  robotGPIO_init();
  robotMotorEncoder_init();
  EEPROM.begin(EEPROM_SIZE);
  while (!BNO055.init()){Serial.println("ERROR! Unable to initialize the chip!");delay(50);}
  Ps3.begin(JOYSTICK_MACADDRESS);
  robotBootScreen();
  setPIDMinMax(-255, 255);
  setPIDGainYaw(10, 0.5, 0.1);
  setPIDGainPitch(10, 0.5, 0.1);
  setPIDGainRoll(10, 0.5, 0.1);
  setPIDGainRPM(0.5, 1.25, 0.001);
  rtosCreateTaskSerial1();
  rtosCreateTaskSerial2();
}

void loop() {
  while (menu == 0) {robotHomeScreen();}              // homescreen
  while (menu == 1) {robotProgramMode();}             // robot mode menu
  while (menu == 2) {robotSensorCheck();}             // sensor check inside the robot
  while (menu == 3) {robotEncoderCheck();}            // encoder check for master encoder and slave encoder
  while (menu == 4) {robotMotorCheck();}              // motor check for master motor and slave motor
  while (menu == 5) {robotSerialCheck();}             // serial connection check between master and slave
  while (menu == 6) {robotAboutPlatform();}           // about the robot

  while (menu == 7) {robotHoldPosition();}            // hold position mode
  while (menu == 8) {robotJoystickControl();}         // ps3 controller mode
  // while (menu == 9) {robotOdometry();}                // odometry mode
  // while (menu == 10) {robotObjectTracking();}         // object tracking mode
  // while (menu == 11) {robotROS2Navigation();}         // ROS2 navigation mode

  // while (menu == 12) {robotDispayMPU6050();}
  while (menu == 13) {robotDisplayBNO055();}          // check BNO055 sensor
  // while (menu == 14) {robotDisplayEncoderMaster();}   // check 2 encoder master
  while (menu == 15) {robotDisplayEncoderSlave();}    // check 4 encoder slave
  // while (menu == 16) {robotChcekMotorMaster();}       // check 2 motor master
  // while (menu == 17) {robotCheckMotorSlave();}        // check 4 motor slave
}
