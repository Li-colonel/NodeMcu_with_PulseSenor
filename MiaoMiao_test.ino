#include "myWebserver.h"
#include "Pulsesensor.h"


Pulsesensor pulseSensor;
void setup()
{
  Serial.begin(9600); // 启动串口通讯
  Serial.println("");

  
  myWebServer.setup();
  myWebServer.Sbegin(); 
  myWebServer.serverOn();
  myWebServer.begin();

  pulseSensor.begin();
  // 启动网站服务
}

void loop(void)
{
  myWebServer.handleClient();
  myWebServer.signalIn = pulseSensor.readBPM();
}
