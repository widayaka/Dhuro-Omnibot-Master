#include "WString.h"
#include <Arduino.h>
#include "robot_motor_encoder.h"
#include "robot_display.h"
#include "robot_serial.h"
#include "robot_gpio.h"

int frequency = 5000;
int resolution = 8;
int pwmChannel1 = 0;
int pwmChannel2 = 1;

int VAL_ENC_1A = 0;
int VAL_ENC_1B = 0;
int VAL_ENC_2A = 0;
int VAL_ENC_2B = 0;

int16_t encoder_cnt[NUM_OF_MOTORS];
int16_t encoder_prev_cnt[NUM_OF_MOTORS];
int16_t encoder_last_cnt[NUM_OF_MOTORS];
int16_t encoder_velocity[NUM_OF_MOTORS];
int16_t encoder_velocity_monitor[NUM_OF_MOTORS];

float error[NUM_OF_MOTORS]; 
float error_w[NUM_OF_MOTORS];
float lastError[NUM_OF_MOTORS];
float lastError_w[NUM_OF_MOTORS];
float P[NUM_OF_MOTORS];
float P_w[NUM_OF_MOTORS];
float I[NUM_OF_MOTORS];
float I_w[NUM_OF_MOTORS];
float D[NUM_OF_MOTORS];
float D_w[NUM_OF_MOTORS];
float PID[NUM_OF_MOTORS];
float PID_w[NUM_OF_MOTORS];

float motor_p;
float motor_i;
float motor_d;

float motor_pid_min;
float motor_pid_max;

float motor[NUM_OF_MOTORS];
float motor_setPoint[NUM_OF_MOTORS];
float pwm_motor[NUM_OF_MOTORS];

unsigned long currentTime;
unsigned long previousTime = 0;
              
int interval = 20;

void encoder1_ISR(){
  VAL_ENC_1A = digitalRead(ENCODER1A);
  VAL_ENC_1B = digitalRead(ENCODER1B);
  if ((VAL_ENC_1A == HIGH) != (VAL_ENC_1B == LOW)){encoder_cnt[0]++;}
  else{encoder_cnt[0]--;}
}

void encoder2_ISR(){
  VAL_ENC_2A = digitalRead(ENCODER2A);
  VAL_ENC_2B = digitalRead(ENCODER2B);
  if ((VAL_ENC_2A == HIGH) != (VAL_ENC_2B == LOW)){encoder_cnt[1]++;}
  else{encoder_cnt[1]--;}
}

void encoder1_RPM(){
  currentTime = millis();
  if (currentTime - previousTime >= interval){
    previousTime = currentTime;
    encoder_velocity[0] = ((encoder_cnt[0] - encoder_prev_cnt[0]) * 60) / 11;
    encoder_prev_cnt[0] = encoder_cnt[0];
  }
}

void encoder2_RPM(){
  currentTime = millis();
  if (currentTime - previousTime >= interval){
    previousTime = currentTime;
    encoder_velocity[1] = ((encoder_cnt[1] - encoder_prev_cnt[1]) * 60) / 11;
  }
}

void encoderAll_RPM(){
  currentTime = millis();
  if (currentTime - previousTime >= interval){
    previousTime = currentTime;
    for(int i = 0; i < NUM_OF_MOTORS; i++){
      encoder_velocity[i] = ((encoder_cnt[i] - encoder_prev_cnt[i]) * 60) / 11;
      encoder_prev_cnt[i] = encoder_cnt[i];
    }
  }
}

void robotMotorEncoder_init(){
  ledcSetup(pwmChannel1, frequency, resolution);
  ledcAttachPin(PWM_PIN_1A, pwmChannel1); pinMode(PWM_PIN_1B, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER1A), encoder1_ISR, CHANGE); pinMode(ENCODER1B, INPUT);
  
  ledcSetup(pwmChannel2, frequency, resolution);
  ledcAttachPin(PWM_PIN_2A, pwmChannel2); pinMode(PWM_PIN_2B, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER2A), encoder2_ISR, CHANGE); pinMode(ENCODER2B, INPUT);
}

void robotDisplayEncoderSlave(){
  int speed = 0;
  FlagMode = menu;
  dataPackage2 = (String) startDataIdentifier + FlagMode + 
                          dataSeparator + speed +
                          dataSeparator + speed +
                          dataSeparator + speed +
                          dataSeparator + speed +
                          stopDataIdentifier;

  MasterSerial2.println(String(dataPackage2));

  display.clearDisplay();  display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);  display.print("4 Encoder Slave");
  display.setCursor(0,10); display.print("ENC1 : "); display.setCursor(40,10); display.print(int(SerialData2[0]));
  display.setCursor(0,20); display.print("ENC2 : "); display.setCursor(40,20); display.print(int(SerialData2[1]));
  display.setCursor(0,30); display.print("ENC3 : "); display.setCursor(40,30); display.print(int(SerialData2[2]));
  display.setCursor(0,40); display.print("ENC4 : "); display.setCursor(40,40); display.print(int(SerialData2[3]));

  display.display();
  while (PUSH_BUTTON_OK_IS_PRESSED){
    FlagMode = 0;
    dataPackage2 = (String) startDataIdentifier + FlagMode + 
                          dataSeparator + speed +
                          dataSeparator + speed +
                          dataSeparator + speed +
                          dataSeparator + speed +
                          stopDataIdentifier;

    MasterSerial2.println(String(dataPackage2));
    delay(100); menu = 3; break;
  }
}