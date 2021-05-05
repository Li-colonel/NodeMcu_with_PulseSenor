#ifndef _myWebserver_H_
#define _myWebserver_H_

#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>


class Mywebserver
{

private:  
  ESP8266WebServer esp8266_server; 
  bool flag = 0;
  void handleADC();
  void handleUserRequest();
  bool handleFileRead(String resource);
  String getContentType(String filename);

public:
  Mywebserver():esp8266_server(80){};
  void setup();
  void Sbegin();
  void serverOn();
  void begin();
  void handleClient();
  int signalIn = 0;
};

extern Mywebserver myWebServer;

#endif
