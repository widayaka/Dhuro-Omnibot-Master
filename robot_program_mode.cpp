#include "robot_program_mode.h"
#include "robot_motor_encoder.h"
#include "robot_display.h"
#include "robot_gpio.h"
#include "robot_serial.h"
#include <Ps3Controller.h>
#include <EEPROM.h>
#include "esp_bt.h"

float compass;

float dataYaw;
float eepromYaw;
float setPointYaw;
float errorYaw;
float lastErrorYaw;
float P_Yaw;
float I_Yaw; 
float D_Yaw;
float PID_Yaw;

float dataPitch;
float eepromPitch;
float setPointPitch; 
float errorPitch; 
float lastErrorPitch;
float P_Pitch;
float I_Pitch;
float D_Pitch;
float PID_Pitch;

float dataRoll;
float eepromRoll;
float setPointRoll;
float errorRoll;
float lastErrorRoll;
float P_Roll;
float I_Roll;
float D_Roll;
float PID_Roll;

float KP_Yaw;
float KI_Yaw;
float KD_Yaw;

float KP_Pitch;
float KI_Pitch;
float KD_Pitch;

float KP_Roll;
float KI_Roll;
float KD_Roll;

void setPIDGainYaw(float kp, float ki, float kd){
  KP_Yaw = kp;
  KI_Yaw = ki;
  KD_Yaw = kd;
}

void setPIDGainPitch(float kp, float ki, float kd){
  KP_Pitch = kp;
  KI_Pitch = ki;
  KD_Pitch = kd;
}

void setPIDGainRoll(float kp, float ki, float kd){
  KP_Roll = kp;
  KI_Roll = ki;
  KD_Roll = kd;
}

void setPIDGainRPM(float kp, float ki, float kd){
  motor_p = kp;
  motor_i = kd;
  motor_d = kd;
}

void setPIDMinMax(int min, int max){
  motor_pid_min = min;
  motor_pid_max = max;
}

void robotHoldPosition(){
  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE); 
  
  FlagMode = menu; 
   
  BNO055.readEuler();
  dataYaw = BNO055.EulerAngles.x;
  setPointYaw = EEPROM.read(0) + EEPROM.read(1);
  // setPointYaw = EEPROM.get(0, T &t);
  // EEPROM.get(0, setPointYaw);
  errorYaw = dataYaw - setPointYaw;

  display.setCursor(0,0);     display.print("Hold Position Mode");
  
  display.setCursor(0,10);    display.print("Data Yaw");
  display.setCursor(60,10);   display.print(":");
  display.setCursor(70, 10);  display.print(dataYaw);

  display.setCursor(0,20);    display.print("Set Point");
  display.setCursor(60,20);   display.print(":");
  display.setCursor(70,20);   display.print(setPointYaw);

  display.setCursor(0,30);    display.print("Error Yaw");
  display.setCursor(60,30);   display.print(":");
  display.setCursor(70,30);   display.print(errorYaw);

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               dataYaw + dataSeparator + 
                                               setPointYaw + stopDataIdentifier;
  
  display.setCursor(0,40);    display.print("Package Transmitted");
  display.setCursor(0,50);    display.print(dataPackage2);

  display.display();

  MasterSerial2.println(String(dataPackage2));

  while (PUSH_BUTTON_OK_IS_PRESSED) {
    for (int i=0; i<10; i++){
      int speedStop = 0;
      FlagMode = 1;

      dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator +
                                                   speedStop + dataSeparator + 
                                                   speedStop + dataSeparator + 
                                                   speedStop + dataSeparator + 
                                                   speedStop + stopDataIdentifier;

      MasterSerial2.println(String(dataPackage2));
    }    
    
    delay(100);
    menu = 1;
  }
}

void robotJoystickControl(){
  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);    display.print("Joystick Control");
  display.setCursor(0,10);   display.print("Status");
  display.setCursor(40,10);  display.print(":");

  if     (Ps3.isConnected())  {display.setCursor(50,10);  display.print("Connected");}
  else if(!Ps3.isConnected()) {display.setCursor(50,10);  display.print("Disonnected");}

  FlagMode = menu;

  BNO055.readEuler();
  dataYaw = BNO055.EulerAngles.x;

  int joystickLX = 0;
  int joystickLY = 0;
  int joystickRX = 0;
  int joystickRY = 0;

  joystickLX = Ps3.data.analog.stick.lx;
  joystickLY = Ps3.data.analog.stick.ly;
  joystickRX = Ps3.data.analog.stick.rx;
  joystickRY = Ps3.data.analog.stick.ry;
  
  display.setCursor(0,20);   display.print("LX");
  display.setCursor(15,20);  display.print(":");
  display.setCursor(25,20);  display.print(joystickLX);

  display.setCursor(0,30);   display.print("LY");
  display.setCursor(15,30);  display.print(":");
  display.setCursor(25,30);  display.print(joystickLY);

  display.setCursor(60,20);  display.print("RX");
  display.setCursor(75,20);  display.print(":");
  display.setCursor(85,20);  display.print(joystickRX);

  display.setCursor(60,30);  display.print("RY");
  display.setCursor(75,30);  display.print(":");
  display.setCursor(85,30);  display.print(joystickRY);

  display.setCursor(0,40);   display.print("H");
  display.setCursor(10,40);  display.print(dataYaw);

  display.setCursor(0,50);   display.print("X");
  display.setCursor(10,50);  display.print(SerialData2[1]);
  
  display.setCursor(50,50);   display.print("Y");
  display.setCursor(60,50);  display.print(SerialData2[2]);
  
  display.display();

  int dataLXtoSend = joystickLX * 0.05;
  int dataLYtoSend = joystickLY * 0.05;
  int dataRXtoSend = joystickRX * 0.25;

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator +
                                               dataLXtoSend + dataSeparator +
                                               dataLYtoSend + dataSeparator +
                                               dataRXtoSend + dataSeparator +
                                               dataYaw + stopDataIdentifier;
                                               
  MasterSerial2.println(String(dataPackage2));

  while (PUSH_BUTTON_OK_IS_PRESSED) {
    Ps3.end();
    for (int i=0; i<10; i++){
      int speedStop = 0;
      FlagMode = 1;
      dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator +
                                                   speedStop + dataSeparator + 
                                                   speedStop + dataSeparator + 
                                                   speedStop + dataSeparator + 
                                                   speedStop + stopDataIdentifier;
      MasterSerial2.println(String(dataPackage2));
    }    
    
    delay(100);
    menu = 1;
  }
}

void robotROS2LineFollowing(){
  int error_pixel = SerialData1[1];
  int linear_speed = SerialData1[2];
  int angular_speed = SerialData1[3];

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);     display.print("Line Following");
  
  display.setCursor(0,10);    display.print("Error Position");
  display.setCursor(90,10);   display.print(":");
  display.setCursor(100, 10); display.print(error_pixel);

  display.setCursor(0, 20); display.print("Linear Speed");
  display.setCursor(90, 20); display.print(":");
  display.setCursor(100, 20); display.print(linear_speed);

  display.setCursor(0, 30); display.print("Angular Speed");
  display.setCursor(90,30);  display.print(":");
  display.setCursor(100, 30); display.print(angular_speed);

  display.display();

  dataPackage2 = (String) startDataIdentifier + menu + error_pixel + dataSeparator + linear_speed + dataSeparator + angular_speed + stopDataIdentifier;
  MasterSerial2.println(String(dataPackage2));

  while (PUSH_BUTTON_OK_IS_PRESSED) {
    for (int i=0; i<10; i++){
      int speedStop = 0;
      FlagMode = 1;
      dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator +
                                                   speedStop + dataSeparator + 
                                                   speedStop + dataSeparator + 
                                                   speedStop + dataSeparator + 
                                                   speedStop + stopDataIdentifier;
      MasterSerial2.println(String(dataPackage2));
    }    
    delay(100);
    menu = 1;
  }
}

void onConnect(){
  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);    display.print("Joystick Connected...");
  display.display();
}