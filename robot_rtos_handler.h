#ifndef __RTOS_HANDLER__
#define __RTOS_HANDLER__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern TaskHandle_t Task_Serial1;
extern TaskHandle_t Task_Serial2;

void rtosTaskSerial1(void *parameter);
void rtosCreateTaskSerial1();

void rtosTaskSerial2(void *parameter);
void rtosCreateTaskSerial2();

#endif