#include "myWebserver.h"



void Mywebserver::setup()
{
  WiFi.mode(WIFI_AP);
  //启动接入点模式，并设置账号和密码
  Serial.print("设置接入点中 ... ");
  //启动校验式网络（需要输入账号密码的网络）,通道为3，wifi不隐藏，最大连接数=4
  flag = WiFi.softAP(ssid, password, 3, 0);
  if (flag)
  {
    Serial.println("");            // 通过串口监视器输出信息
    Serial.print("当前工作模式:"); // 告知用户设备当前工作模式
    Serial.println(WiFi.getMode());
    Serial.print("接入点名字:");
    Serial.println(ssid); // 告知用户建立的接入点WiFi名
    Serial.print("接入点密码:");
    Serial.println(password);        // 告知用户建立的接入点WiFi密码
    Serial.print("IP address: ");    // 以及NodeMCU的IP地址
    Serial.println(WiFi.softAPIP()); // 通过调用WiFi.softAPIP()可以得到NodeMCU的IP地址
  }
  else
    Serial.println("AP开启失败");
}
void Mywebserver::Sbegin()
{
  if (SPIFFS.begin())
  { // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  }
  else
  {
    Serial.println("SPIFFS Failed to Start.");
  }
}
void Mywebserver::serverOn()
{
  esp8266_server.on("/pulsesensor/readADC", std::bind(&Mywebserver::handleADC, this)); //html文件里发送的请求是“pulsesensor/readADC”
  esp8266_server.onNotFound(std::bind(&Mywebserver::handleUserRequest,this));         // 处理其它网络请求
}
void Mywebserver::begin()

{
  esp8266_server.begin();
  Serial.println("HTTP server started!");
}
void Mywebserver::handleClient()
{
  esp8266_server.handleClient();
}

void Mywebserver::handleADC()
{
  int a = signalIn;      //TODO数据位置
  String adcValue = String(a); //转为string类型

  esp8266_server.send(200, "text/plain", adcValue); //发送模拟输入引脚到客户端ajax请求
}

// 处理用户浏览器的HTTP访问
void Mywebserver::handleUserRequest()
{

  // 获取用户请求资源(Request Resource）
  String reqResource = esp8266_server.uri();
  Serial.print("reqResource: ");
  Serial.println(reqResource);

  // 通过handleFileRead函数处处理用户请求资源
  bool fileReadOK = handleFileRead(reqResource);

  // 如果在SPIFFS无法找到用户访问的资源，则回复404 (Not Found)
  if (!fileReadOK)
  {
    esp8266_server.send(404, "text/plain", "404 Not Found");
  }
}

bool Mywebserver::handleFileRead(String resource)
{ //处理浏览器HTTP访问

  if (resource.endsWith("/"))
  {                           // 如果访问地址以"/"为结尾
    resource = "/index.html"; // 则将访问地址修改为/index.html便于SPIFFS访问
  }

  String contentType = getContentType(resource); // 获取文件类型

  if (SPIFFS.exists(resource))
  {                                               // 如果访问的文件可以在SPIFFS中找到
    File file = SPIFFS.open(resource, "r");       // 则尝试打开该文件
    esp8266_server.streamFile(file, contentType); // 并且将该文件返回给浏览器
    file.close();                                 // 并且关闭文件
    return true;                                  // 返回true
  }
  return false; // 如果文件未找到，则返回false
}

// 获取文件类型
String Mywebserver::getContentType(String filename)
{
  if (filename.endsWith(".htm"))
    return "text/html";
  else if (filename.endsWith(".html"))
    return "text/html";
  else if (filename.endsWith(".css"))
    return "text/css";
  else if (filename.endsWith(".js"))
    return "application/javascript";
  else if (filename.endsWith(".png"))
    return "image/png";
  else if (filename.endsWith(".gif"))
    return "image/gif";
  else if (filename.endsWith(".jpg"))
    return "image/jpeg";
  else if (filename.endsWith(".ico"))
    return "image/x-icon";
  else if (filename.endsWith(".xml"))
    return "text/xml";
  else if (filename.endsWith(".pdf"))
    return "application/x-pdf";
  else if (filename.endsWith(".zip"))
    return "application/x-zip";
  else if (filename.endsWith(".gz"))
    return "application/x-gzip";
  return "text/plain";
}
Mywebserver myWebServer;
