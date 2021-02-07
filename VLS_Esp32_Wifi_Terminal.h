#pragma once
#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

class WifiTerminal {   

public: 

void begin(int port);
void begin();



byte read();
byte peek();

void end();
byte readAdress(int adress);

void print(String data);
void print(int data);
void print(char data);
void print(float data);

void Process();

void readBytes(byte *buf, int size);
 
void println(String data);
void println(int data);
void println(char data);
void println(float data);


void flush();
void write(byte dta);
void write(byte dta[],int size);

int available();
String readString();
IPAddress getRemoteIP();

bool Connected=false;
 
private:


WiFiServer server;
bool _WorkAlloved=false;
byte IncommingBuffer[1024]; 
int  _IncomingBufferCurrentPosition=0;
byte nonProctedRead();
WiFiClient client;
void ClearBuffer();
bool _TransmitteInProgress=false;
};
