#include <Arduino.h>
#include "robot_gpio.h"
#include "robot_motor_encoder.h"

void robotGPIO_init(){
  pinMode(PB_UP,       INPUT_PULLUP);
  pinMode(PB_DOWN,     INPUT_PULLUP);
  pinMode(PB_OK,       INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

