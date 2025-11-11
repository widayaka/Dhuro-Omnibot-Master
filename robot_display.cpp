#include <Arduino.h>
#include "EEPROM.h"
#include "robot_display.h"
#include "robot_gpio.h"
#include "robot_serial.h"
#include "robot_program_mode.h"

int menu = 0;
int menu_program = 0; 
int menu_sensor = 0;
int menu_encoder = 0; 
int menu_motor = 0;
int menu_serial = 0;
    
int pilih_menu = 0;
int pilih_menu_program = 0;
int pilih_menu_sensor = 0;
int check_sensor = 0;
int pilih_menu_encoder = 0; 
int pilih_menu_motor = 0;
int pilih_menu_serial = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DFRobot_BNO055 BNO055;

void robotDisplay_init(void){
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void robotBootScreen(void){
  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0,0); display.println(F("Research of 2025"));
  display.setCursor(0,10); display.println(F("Omni 4 Wheel Robot"));
  display.setCursor(0,20); display.println(F("By: Parama Diptya W"));
  display.setCursor(0,30); display.println(F("FT - UNESA"));
  display.setCursor(0,40); display.println(F("Microprocessor"));
  display.setCursor(0,50); display.println(F("Laboratory"));
  
  display.display();  delay(2000);  display.clearDisplay();
}

void robotHomeScreen(void){
  int speed = 0;

  FlagMode = menu;
  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;     

  MasterSerial2.println(String(dataPackage2));  

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  switch(pilih_menu){
    case 0: pilih_menu = 1; break;

    // Menu Program Mode
    case 1: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Program Mode"));
            display.setCursor(10,10);   display.println(F("Sensor Check"));
            display.setCursor(10,20);   display.println(F("Encoder Check"));
            display.setCursor(10,30);   display.println(F("Motor Check"));
            display.setCursor(10,40);   display.println(F("Serial Check"));
            display.setCursor(10,50);   display.println(F("About Platform"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=1; break;

    // Menu Sensor Check
    case 2: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Program Mode"));
            display.setCursor(10,10);   display.println(F("Sensor Check"));
            display.setCursor(10,20);   display.println(F("Encoder Check"));
            display.setCursor(10,30);   display.println(F("Motor Check"));
            display.setCursor(10,40);   display.println(F("Serial Check"));
            display.setCursor(10,50);   display.println(F("About Platform"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=2; break;

    // Menu Encoder Check       
    case 3: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,20);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Program Mode"));
            display.setCursor(10,10);   display.println(F("Sensor Check"));
            display.setCursor(10,20);   display.println(F("Encoder Check"));
            display.setCursor(10,30);   display.println(F("Motor Check"));
            display.setCursor(10,40);   display.println(F("Serial Check"));
            display.setCursor(10,50);   display.println(F("About Platform"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=3; break;

    // Menu Motor Check
    case 4: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,30);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Program Mode"));
            display.setCursor(10,10);   display.println(F("Sensor Check"));
            display.setCursor(10,20);   display.println(F("Encoder Check"));
            display.setCursor(10,30);   display.println(F("Motor Check"));
            display.setCursor(10,40);   display.println(F("Serial Check"));
            display.setCursor(10,50);   display.println(F("About Platform"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=4; break;

    // Menu Serial Check
    case 5: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,40);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Program Mode"));
            display.setCursor(10,10);   display.println(F("Sensor Check"));
            display.setCursor(10,20);   display.println(F("Encoder Check"));
            display.setCursor(10,30);   display.println(F("Motor Check"));
            display.setCursor(10,40);   display.println(F("Serial Check"));
            display.setCursor(10,50);   display.println(F("About Platform"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=5; break;    

    // Menu About Platform
    case 6: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,50);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Program Mode"));
            display.setCursor(10,10);   display.println(F("Sensor Check"));
            display.setCursor(10,20);   display.println(F("Encoder Check"));
            display.setCursor(10,30);   display.println(F("Motor Check"));
            display.setCursor(10,40);   display.println(F("Serial Check"));
            display.setCursor(10,50);   display.println(F("About Platform"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) {menu=6; delay(200); display.clearDisplay();} break; 

    case 7: pilih_menu = 6; break;
  }
  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); pilih_menu++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); pilih_menu--;}
}

void robotProgramMode(){
  int speed = 0;
  FlagMode = menu;

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2));

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  
  switch(pilih_menu_program){
    case 0: pilih_menu_program = 1; break;
    
    // Hold Position Mode
    case 1: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Hold Position"));
            display.setCursor(10,10);   display.println(F("Joystick Control"));
            display.setCursor(10,20);   display.println(F("Robot Odometry"));
            display.setCursor(10,30);   display.println(F("ROS2 Navigation"));
            display.setCursor(10,40);   display.println(F("ROS2 Obj Track"));
            display.setCursor(10,50);   display.println(F("ROS2 Line Follow"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=7; break;
            
    // Joystick Control Mode        
    case 2: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Hold Position"));
            display.setCursor(10,10);   display.println(F("Joystick Control"));
            display.setCursor(10,20);   display.println(F("Robot Odometry"));
            display.setCursor(10,30);   display.println(F("ROS2 Navigation"));
            display.setCursor(10,40);   display.println(F("ROS2 Obj Track"));
            display.setCursor(10,50);   display.println(F("ROS2 Line Follow"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=8; break;
            
    // Robot Odomotery Mode
    case 3: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,20);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Hold Position"));
            display.setCursor(10,10);   display.println(F("Joystick Control"));
            display.setCursor(10,20);   display.println(F("Robot Odometry"));
            display.setCursor(10,30);   display.println(F("ROS2 Navigation"));
            display.setCursor(10,40);   display.println(F("ROS2 Obj Track"));
            display.setCursor(10,50);   display.println(F("ROS2 Line Follow"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=9; break;
            
    // Robot ROS2 Navigation
    case 4: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,30);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Hold Position"));
            display.setCursor(10,10);   display.println(F("Joystick Control"));
            display.setCursor(10,20);   display.println(F("Robot Odometry"));
            display.setCursor(10,30);   display.println(F("ROS2 Navigation"));
            display.setCursor(10,40);   display.println(F("ROS2 Obj Track"));
            display.setCursor(10,50);   display.println(F("ROS2 Line Follow"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=10; break;
            
    // ROS2 Object Tracking
    case 5: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,40);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Hold Position"));
            display.setCursor(10,10);   display.println(F("Joystick Control"));
            display.setCursor(10,20);   display.println(F("Robot Odometry"));
            display.setCursor(10,30);   display.println(F("ROS2 Navigation"));
            display.setCursor(10,40);   display.println(F("ROS2 Obj Track"));
            display.setCursor(10,50);   display.println(F("ROS2 Line Follow"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=11; break;
    
    // ROS2 Line Following
    case 6: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,50);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Hold Position"));
            display.setCursor(10,10);   display.println(F("Joystick Control"));
            display.setCursor(10,20);   display.println(F("Robot Odometry"));
            display.setCursor(10,30);   display.println(F("ROS2 Navigation"));
            display.setCursor(10,40);   display.println(F("ROS2 Obj Track"));
            display.setCursor(10,50);   display.println(F("ROS2 Line Follow"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=12; break;
            break;

    // ROS2 Wall Follow
    case 7: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.println(F(">"));
            display.setCursor(10,0);    display.println(F("ROS2 Wall Follow"));
            display.setCursor(10,10);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=13; break;
            break;

    case 8: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("ROS2 Wall Follow"));
            display.setCursor(10,10);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) {pilih_menu_program = 0; menu=0;}
            break;

    case 9: pilih_menu_program = 7; break;
  }

  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); pilih_menu_program++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); pilih_menu_program--;}
}

void robotSensorCheck(){
  int speed = 0;
  FlagMode = menu;  

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2));  

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  switch(pilih_menu_sensor){
    case 0: pilih_menu_sensor = 1; break;

    // MPU6050 Sensor Check
    case 1: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.println(F(">"));
            display.setCursor(10,0);    display.println(F("MPU6050"));
            display.setCursor(10,10);   display.println(F("BNO055"));
            display.setCursor(10,20);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=12; break;

    // BNO055 Sensor Check
    case 2: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("MPU6050"));
            display.setCursor(10,10);   display.println(F("BNO055"));
            display.setCursor(10,20);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=13; break;

    // Exit       
    case 3: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,20);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("MPU6050"));
            display.setCursor(10,10);   display.println(F("BNO055"));
            display.setCursor(10,20);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) {pilih_menu_sensor = 0; menu=0;}  break; 

    case 4: pilih_menu_sensor = 3; break;
  }
  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); pilih_menu_sensor++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); pilih_menu_sensor--;}
}

void robotEncoderCheck(){
  int speed = 0;
  FlagMode = menu;

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2));  

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);  
  switch(pilih_menu_encoder){
    case 0: pilih_menu_encoder = 1; break;
    
    // 2 Encoder Master
    case 1: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);   display.println(F(">"));
            display.setCursor(10,0);  display.println(F("2 Encoder Master"));
            display.setCursor(10,10);  display.println(F("4 Encoder Slave"));
            display.setCursor(10,20);  display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu = 14;
            break;
    
    // 4 Encoder Slave
    case 2: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);   display.println(F(">"));
            display.setCursor(10,0);  display.println(F("2 Encoder Master"));
            display.setCursor(10,10);  display.println(F("4 Encoder Slave"));
            display.setCursor(10,20);  display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu = 15;
            break;
    
    // Exit   
    case 3: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,20);   display.println(F(">"));
            display.setCursor(10,0);  display.println(F("2 Encoder Master"));
            display.setCursor(10,10);  display.println(F("4 Encoder Slave"));
            display.setCursor(10,20);  display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) {pilih_menu_encoder = 0; menu=0;}
            break;                    
    
    case 4: pilih_menu_encoder = 3; break;
  }
  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); pilih_menu_encoder++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); pilih_menu_encoder--;}
}

void robotMotorCheck(){
  int speed = 0;
  FlagMode = menu;  

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2));  

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE); 
  switch(pilih_menu_motor){
    case 0: pilih_menu_motor = 1; break;
    
    // 2 Motor Master
    case 1: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);   display.println(F(">"));
            display.setCursor(10,0);  display.println(F("2 Motor Master"));
            display.setCursor(10,10);  display.println(F("4 Motor Slave"));
            display.setCursor(10,20);  display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=1;
            break;
    
    // 4 Motor Slave
    case 2: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);   display.println(F(">"));
            display.setCursor(10,0);  display.println(F("2 Motor Master"));
            display.setCursor(10,10);  display.println(F("4 Motor Slave"));
            display.setCursor(10,20);  display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=2;
            break;
    
    // Exit     
    case 3: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,20);   display.println(F(">"));
            display.setCursor(10,0);  display.println(F("2 Motor Master"));
            display.setCursor(10,10);  display.println(F("4 Motor Slave"));
            display.setCursor(10,20);  display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) {pilih_menu_motor = 0; menu=0;}
            break;                    
    
    case 4: pilih_menu_motor = 3; break;
  }
  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); pilih_menu_motor++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); pilih_menu_motor--;}
}

void robotSerialCheck(){
  int speed = 0;
  FlagMode = menu;  

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2));  

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE); 
  switch(pilih_menu_serial){
    case 0: pilih_menu_serial = 1; break;

    // Serial Monitor Check
    case 1: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Serial Monitor"));
            display.setCursor(10,10);   display.println(F("Master to Slave"));
            display.setCursor(10,20);   display.println(F("Slave to Master"));
            display.setCursor(10,30);   display.println(F("Biderictional Data"));
            display.setCursor(10,40);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu_serial=7;
            break;

    // Master to Slave Check
    case 2: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,10);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Serial Monitor"));
            display.setCursor(10,10);   display.println(F("Master to Slave"));
            display.setCursor(10,20);   display.println(F("Slave to Master"));
            display.setCursor(10,30);   display.println(F("Biderictional Data"));
            display.setCursor(10,40);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=1;
            break;

    // Slave to Master Check        
    case 3: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,20);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Serial Monitor"));
            display.setCursor(10,10);   display.println(F("Master to Slave"));
            display.setCursor(10,20);   display.println(F("Slave to Master"));
            display.setCursor(10,30);   display.println(F("Biderictional Data"));
            display.setCursor(10,40);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=1;
            break;

    // Bidirectional Data Check
    case 4: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,30);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Serial Monitor"));
            display.setCursor(10,10);   display.println(F("Master to Slave"));
            display.setCursor(10,20);   display.println(F("Slave to Master"));
            display.setCursor(10,30);   display.println(F("Biderictional Data"));
            display.setCursor(10,40);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu=1;
            break; 

    // Exit
    case 5: display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,40);    display.println(F(">"));
            display.setCursor(10,0);    display.println(F("Serial Monitor"));
            display.setCursor(10,10);   display.println(F("Master to Slave"));
            display.setCursor(10,20);   display.println(F("Slave to Master"));
            display.setCursor(10,30);   display.println(F("Biderictional Data"));
            display.setCursor(10,40);   display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) {pilih_menu_serial = 0; menu=0;}
            break;   

    case 6: pilih_menu_serial = 5; break;
  }
  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); pilih_menu_serial++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); pilih_menu_serial--;}
}

void robotAboutPlatform(){
  display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);     display.println(F("Omni 4 Wheel Robot"));
  display.setCursor(0,10);    display.println(F("Version: 1.0"));
  display.setCursor(0,20);    display.println(F("Year: 2025"));
  display.setCursor(0,30);    display.println(F("Author: Widayaka"));
  display.setCursor(0,40);    display.println(F("Microprocessor"));
  display.setCursor(0,50);    display.println(F("Library"));
  display.display();
  while (PUSH_BUTTON_OK_IS_PRESSED) {menu=0; delay(200); display.clearDisplay();}
}

void robotDisplayMPU6050(){
  
}

void robotDisplayBNO055(){
  int speed = 0;
  FlagMode = menu;

  dataPackage2 = (String) startDataIdentifier + FlagMode + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + dataSeparator + 
                                               speed + stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2)); 

  display.clearDisplay(); display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  
  BNO055.readEuler();
  
  dataYaw   = BNO055.EulerAngles.x;
  dataPitch = BNO055.EulerAngles.y;
  dataRoll  = BNO055.EulerAngles.z;
  
  switch(check_sensor){
    case 0: check_sensor = 1; break;

    // Save Set Point
    case 1: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.print("BNO055 Sensor Reading");
  
            display.setCursor(0,10);    display.print("Data Yaw");
            display.setCursor(70,10);   display.print(":");
            display.setCursor(80,10);   display.print(dataYaw);
              
            display.setCursor(0,20);    display.print("Data Pitch");
            display.setCursor(70,20);   display.print(":");
            display.setCursor(80,20);   display.print(dataPitch);
            
            display.setCursor(0,30);    display.print("Data Roll");
            display.setCursor(70,30);   display.print(":");
            display.setCursor(80,30);   display.print(dataRoll);
          
            display.setCursor(0,40);    display.print("Data SP Yaw");
            display.setCursor(70,40);   display.print(":");
            display.setCursor(80,40);   display.print(setPointYaw);
            display.setCursor(0,50);    display.println(F(">"));
            display.setCursor(10,50);   display.println(F("Save SP"));
            display.setCursor(80,50);   display.println(F("Init"));
            
            display.display();
            
            while (PUSH_BUTTON_OK_IS_PRESSED) {setPointYaw = dataYaw;}

            if (setPointYaw > 255){
                eepromYaw = 255;
                EEPROM.write(0, eepromYaw);
                EEPROM.write(1, dataYaw - eepromYaw);
                EEPROM.commit();
            }
            
            else{
                eepromYaw = dataYaw;
                EEPROM.write(0, eepromYaw);
                EEPROM.write(1, 0);
                EEPROM.commit();
            }
            
            break;
    
    // Initialize BNO055        
    case 2: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.print("BNO055 Sensor Reading");
  
            display.setCursor(0,10);    display.print("Data Yaw");
            display.setCursor(70,10);   display.print(":");
            display.setCursor(80,10);   display.print(dataYaw);
              
            display.setCursor(0,20);    display.print("Data Pitch");
            display.setCursor(70,20);   display.print(":");
            display.setCursor(80,20);   display.print(dataPitch);
            
            display.setCursor(0,30);    display.print("Data Roll");
            display.setCursor(70,30);   display.print(":");
            display.setCursor(80,30);   display.print(dataRoll);
          
            display.setCursor(0,40);    display.print("Data SP Yaw");
            display.setCursor(70,40);   display.print(":");
            display.setCursor(80,40);   display.print(setPointYaw);
            
            display.setCursor(70,50);    display.println(F(">"));
            display.setCursor(10,50);    display.println(F("Save SP"));
            display.setCursor(80,50);    display.println(F("Init"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) BNO055.init(); break;
    
    // Exit
    case 3: display.setTextSize(1);     display.setTextColor(SSD1306_WHITE);
            display.setCursor(0,0);     display.print("BNO055 Sensor Reading");
  
            display.setCursor(0,10);    display.print("Data Yaw");
            display.setCursor(70,10);   display.print(":");
            display.setCursor(80,10);   display.print(dataYaw);
              
            display.setCursor(0,20);    display.print("Data Pitch");
            display.setCursor(70,20);   display.print(":");
            display.setCursor(80,20);   display.print(dataPitch);
            
            display.setCursor(0,30);    display.print("Data Roll");
            display.setCursor(70,30);   display.print(":");
            display.setCursor(80,30);   display.print(dataRoll);
          
            display.setCursor(0,40);    display.print("Data SP Yaw");
            display.setCursor(70,40);   display.print(":");
            display.setCursor(80,40);   display.print(setPointYaw);
            
            display.setCursor(0,50);    display.println(F(">"));
            display.setCursor(10,50);    display.println(F("Exit"));
            display.display(); 
            while (PUSH_BUTTON_OK_IS_PRESSED) menu = 2; break;
    
    case 4: check_sensor = 3; break;
  }
  if (PUSH_BUTTON_DOWN_IS_PRESSED)  {delay(200); display.clearDisplay(); check_sensor++;}
  if (PUSH_BUTTON_UP_IS_PRESSED)    {delay(200); display.clearDisplay(); check_sensor--;}
  display.display();
}