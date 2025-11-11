#include <Arduino.h>
#include "robot_serial.h"

HardwareSerial MasterSerial1(1);
HardwareSerial MasterSerial2(2);

int FlagMode = 0;
int counter = 0;

int data1;
int data2;
int data3;
int data4;
int data5;
int data6;
int data7;
int data8;
int DataEncoderSerial[4];

float SerialData1[NUM_OF_DATA];
float SerialData2[NUM_OF_DATA];

char receivedMessage;
char dataReceived1;
char dataReceived2;

String dataPackage1;
String dataPackage2;
String bufferDataIn1;
String bufferDataIn2;
String bufferDataParsing1[ARRAY_SIZE];
String bufferDataParsing2[ARRAY_SIZE];

bool dataIsComplete1;
bool dataIsComplete2;

byte indexOfData1;
byte indexOfData2;

const char startDataIdentifier = '*';
const char dataSeparator = ',';
const char stopDataIdentifier = '#';

void robotSerial_init(){
  Serial.begin(115200);
  MasterSerial1.begin(MASTER_SERIAL_BAUDRATE, SERIAL_8N1, RX1, TX1);
  MasterSerial2.begin(MASTER_SERIAL_BAUDRATE, SERIAL_8N1, RX2, TX2);
}

void Serial1DataReceived(){
  while (MasterSerial1.available() > 0){                      
    dataReceived1 = MasterSerial1.read();                      
    if (dataReceived1 == startDataIdentifier){                
      bufferDataIn1 = startDataIdentifier;                    
      bufferDataIn1 += MasterSerial1.readStringUntil('#');     
      dataIsComplete1 = true;                                 
      bufferDataIn1 += stopDataIdentifier;                    
      break;                                                 
    }
  }
}

void Serial2DataReceived(){
  while (MasterSerial2.available() > 0){                      
    dataReceived2 = MasterSerial2.read();                      
    if (dataReceived2 == startDataIdentifier){                
      bufferDataIn2 = startDataIdentifier;                    
      bufferDataIn2 += MasterSerial2.readStringUntil('#');     
      dataIsComplete2 = true;                                 
      bufferDataIn2 += stopDataIdentifier;                    
      break;                                                 
    }
  }
}

void Serial1DataParsing(){
  for (int i = 0; i < bufferDataIn1.length(); i++){
    if (bufferDataIn1[i] == startDataIdentifier){bufferDataParsing1[indexOfData1] = "";}
    else if (bufferDataIn1[i] != dataSeparator){bufferDataParsing1[indexOfData1] += bufferDataIn1[i];}
    else{indexOfData1++; bufferDataParsing1[indexOfData1] = "";}
  }
}

void Serial2DataParsing(){
  for (int i = 0; i < bufferDataIn2.length(); i++){
    if (bufferDataIn2[i] == startDataIdentifier){bufferDataParsing2[indexOfData2] = "";}
    else if (bufferDataIn2[i] != dataSeparator){bufferDataParsing2[indexOfData2] += bufferDataIn2[i];}
    else{indexOfData2++; bufferDataParsing2[indexOfData2] = "";}
  }
}

void Serial1DataConversion(){
  for (int i = 0; i < 10; i++){
    if (i==0){
      SerialData1[i] = bufferDataParsing1[i].toInt();
    }
    else{
      SerialData1[i] = bufferDataParsing1[i].toFloat();
    }
  }
}

void Serial2DataConversion(){
  for (int i = 0; i < 10; i++){
    if (i==0){
      SerialData2[i] = bufferDataParsing2[i].toInt();
    }
    else{
      SerialData2[i] = bufferDataParsing2[i].toFloat();
    }
  }
}

void Serial1DataReset(){
  dataReceived1 = 0; bufferDataIn1 = ""; dataIsComplete1 = false; indexOfData1 = 0;
}

void Serial2DataReset(){
  dataReceived2 = 0; bufferDataIn2 = ""; dataIsComplete2 = false; indexOfData2 = 0;
}