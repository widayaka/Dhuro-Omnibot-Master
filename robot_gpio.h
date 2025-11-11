#ifndef __ROBOT_GIO_H__
#define __ROBOT_GPIO_H__

#include <Arduino.h>

#define PB_UP   12
#define PB_DOWN 15
#define PB_OK   27

#define PUSH_BUTTON_DOWN_IS_PRESSED digitalRead(PB_DOWN)  == LOW
#define PUSH_BUTTON_UP_IS_PRESSED   digitalRead(PB_UP)    == LOW
#define PUSH_BUTTON_OK_IS_PRESSED   digitalRead(PB_OK)    == LOW

void robotGPIO_init(void);

#endif