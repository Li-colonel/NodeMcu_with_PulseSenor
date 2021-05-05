#include "myWebserver.h"
#include "Pulsesensor.h"

#define ssid "miaomiao"     //这里改成你的设备当前环境下接入点名字
#define password "12345678" //这里改成你的设备当前环境下接入点密码

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
