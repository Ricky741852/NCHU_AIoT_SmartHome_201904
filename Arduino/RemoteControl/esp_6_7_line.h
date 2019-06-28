
#include "WiFiEsp.h"
#include "SoftwareSerial.h"

//引入Wire與LiquidCrystal_I2C函式庫
#include <Wire.h>  // Arduino IDE 內建
#include <LiquidCrystal_I2C.h>

// 設定 LCD I2C 位址
// Set the pins on the I2C chip used for LCD connections:
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
bool esp01_9600(const char *,const char *);
bool send_ir(const char *, String ,String ,String ,unsigned long ,String ,int );

String ipToString(IPAddress ip);
void init_LCD(String);

SoftwareSerial ESP01(6, 7);
WiFiEspServer server(80);
RingBuffer buf(8);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

bool esp01_9600(const char *my_id,const char *my_pw)
{
 int wifi_flag=0;
 int status = WL_IDLE_STATUS;
 Serial.begin(9600);
 ESP01.begin(9600);
 WiFi.init(&ESP01);
 if (WiFi.status() == WL_NO_SHIELD)
 {
    wifi_flag=1;    
 }

 if (wifi_flag==0)
 {
  // attempt to connect to WiFi network
  while (status != WL_CONNECTED)
  {
   status = WiFi.begin(my_id, my_pw);
   if (status ==WL_CONNECTED)
   {
    // Connect to WPA/WPA2 network
    //LOGINFO1(F("SSID: "), WiFi.SSID());
    //LOGINFO1(F("IP Address: "), WiFi.localIP());
    // start the web server on port 80
    server.begin();
    return true;
   }
  }   
 }
 return false;
}

bool send_ir(const char *D_host, String item1,String str1,String item2,unsigned long val2,String item3,int val3)
{
 bool connect_flag=false;
 byte i=0;  
  WiFiEspClient client;
  const int httpPort = 80;
  connect_flag=client.connect(D_host, httpPort); 
  while (!connect_flag)
  {

   delay(200);
   connect_flag=client.connect(D_host, httpPort);
   if (i>5) return false;
   i++;
  }
  
  // Create a URI for the request
  String data = "/aiot/AddData.php?"+ item1 + "=" + str1 + "&" + item2 + "=" + String(val2)+ "&" + item3 + "=" + String(val3);
  
  // This will send the request to the server
  client.print(String("GET ") + data + " HTTP/1.1\r\n" +
               "Host: " + D_host + "\r\n" + 
               "Connection: close\r\n\r\n");
  client.stop();
  return true;
}  

String ipToString(IPAddress ip){ 
String s=""; 
for (int i=0; i<4; i++) 
s += i ? "." + String(ip[i]) : String(ip[i]); 
return s; 
}

void init_LCD(String IP)
{
 // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
 lcd.begin(16, 2);
 if (IP=="")
 {
  lcd.clear(); //顯示清除
  return;
 }
 // 閃爍三次
 for(int i = 0; i < 3; i++) {
 lcd.backlight(); // 開啟背光
 delay(250);
 lcd.noBacklight(); // 關閉背光
 delay(250);
 }
 lcd.backlight();

 // 輸出初始化文字
 lcd.setCursor(0, 0); // 設定游標位置在第一行行首
 lcd.print(IP);
 delay(1000);
 lcd.setCursor(0, 1); // 設定游標位置在第二行行首
 lcd.print("Stand by .....");
 delay(500);
 //lcd.clear(); //顯示清除  
}
