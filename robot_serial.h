#ifndef __ROBOT_SERIAL_H__
#define __ROBOT_SERIAL_H__

#include <Arduino.h>
#include <stdint.h>

//Serial Connection Raspberry Pi 5 <=> Master Board
extern HardwareSerial MasterSerial1;
#define RX1 13    // UART1 RX Pin 
#define TX1 5     // UART1 TX Pin

//Serial Connection Master Board <=> Slave Board
extern HardwareSerial MasterSerial2;
#define RX2 17    // UART2 RX Pin
#define TX2 16    // UART2 TX Pin

#define MASTER_SERIAL_BAUDRATE 115200
#define EEPROM_SIZE 64

#define ARRAY_SIZE 21
#define NUM_OF_DATA 10

extern int FlagMode;
extern int counter;

extern int data1;
extern int data2;
extern int data3;
extern int data4;
extern int data5;
extern int data6;
extern int data7;
extern int data8;
extern int DataEncoderSerial[4];

extern float SerialData1[NUM_OF_DATA];
extern float SerialData2[NUM_OF_DATA];

extern char receivedMessage;
extern char dataReceived1;
extern char dataReceived2;

extern String dataPackage1;
extern String dataPackage2;
extern String bufferDataIn1;
extern String bufferDataIn2;
extern String bufferDataParsing1[ARRAY_SIZE];
extern String bufferDataParsing2[ARRAY_SIZE];  

extern bool dataIsComplete1;
extern bool dataIsComplete2;

extern byte indexOfData1;
extern byte indexOfData2;

extern const char startDataIdentifier;
extern const char dataSeparator;
extern const char stopDataIdentifier;

void robotSerial_init(void);

void Serial1DataReceived(void);
void Serial2DataReceived(void);

void Serial1DataParsing(void);
void Serial2DataParsing(void);

void Serial1DataConversion(void);
void Serial2DataConversion(void);

void Serial1DataReset(void);
void Serial2DataReset(void);

#endif