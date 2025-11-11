#include <Arduino.h>
#include "robot_rtos_handler.h"
#include "robot_serial.h"
#include "freertos/portmacro.h"

TaskHandle_t Task_Serial1 = NULL;
TaskHandle_t Task_Serial2 = NULL;

void rtosTaskSerial1(void *parameter){
  for(;;){
    // read serial 1 data received by master
    Serial1DataReceived();
    // parse serial 1 data received by master
    Serial1DataParsing();
    // convert serial 1 data
    Serial1DataConversion();
    // serial 1 reset data
    Serial1DataReset();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void rtosCreateTaskSerial1(){
  xTaskCreatePinnedToCore(
    rtosTaskSerial1, 
    "rtosTaskSerial1", 
    4096, 
    NULL, 
    1, 
    &Task_Serial1, 
    0);
}

void rtosTaskSerial2(void *parameter){
  for(;;){
    // read serial 2 data received by master
    Serial2DataReceived();
    // parse serial 2 data received by master
    Serial2DataParsing();
    // convert serial 2 data
    Serial2DataConversion();
    // serial 2 reset data
    Serial2DataReset();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void rtosCreateTaskSerial2(){
  xTaskCreatePinnedToCore(
    rtosTaskSerial2, 
    "rtosTaskSerial2", 
    4096, 
    NULL, 
    1, 
    &Task_Serial2, 
    0);
}