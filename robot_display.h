#ifndef __OLED_DISPLAY_H__
#define __OLED_DISPLAY_H__

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DFRobot_BNO055.h"

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1         
#define SCREEN_ADDRESS  0x3C 

extern Adafruit_SSD1306 display;
extern DFRobot_BNO055 BNO055;

extern int menu;
extern int menu_program; 
extern int menu_sensor;
extern int menu_encoder; 
extern int menu_motor;
extern int menu_serial;
    
extern int pilih_menu;
extern int pilih_menu_program;
extern int pilih_menu_sensor;
extern int check_sensor;
extern int pilih_menu_encoder; 
extern int pilih_menu_motor;
extern int pilih_menu_serial;

void robotDisplay_init(void);
void robotBootScreen(void);
void robotHomeScreen(void);
void robotProgramMode(void);
void robotSensorCheck(void);
void robotEncoderCheck(void);
void robotMotorCheck(void);
void robotSerialCheck(void);
void robotAboutPlatform(void);
void robotDisplayMPU6050(void);
void robotDisplayBNO055(void);

#endif