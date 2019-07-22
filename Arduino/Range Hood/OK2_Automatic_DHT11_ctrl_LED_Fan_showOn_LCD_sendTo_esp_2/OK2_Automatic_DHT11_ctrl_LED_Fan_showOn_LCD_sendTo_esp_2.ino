////大哥的library////////// 
//#include "Timer.h"
#include "esp_2_3_line.h"  //by TSH 
//Timer myTimer;          //建立定時執行物件
//......................................

//關於DHT的library////////////////////////////////////////////////////////
#include "DHT.h"    ///溫溼度感測//要先匯入下載的dht的程式庫:"DHT-sensor-library-master.zip"到library
//********************************************************

//關於LCD的library////////////////////////////////////
#include <Wire.h>  // Arduino IDE 內建
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>
//********************************************************

////大哥的declare////////// 
const char *SID="Steven Mate 8";     //輸入wifi ID
const char *PWD="23367203";  //輸入wifi passward

byte warning=0; //只要不會超過255，可以用byte取代int
byte varKTemp=0;
byte varWet=0;
//********************************************************

//關於DHT的declare///////////////////////////////
byte pinDHT = 4; // 溫溼度Sensor腳位=4!!!!!!!!!!!!!!!!!!!!!腳位的變數由課堂的dataPin改成pinDHT
byte val = 0;   // 溫溼度數值

int Humidity   = 0; // 濕度
int Celsius    = 0; // 攝氏溫度
int Fahrenheit = 0; // 華氏溫度

DHT dht(pinDHT, DHT11);  // 設定Sensor的腳位和型號 //大哥的是用dht去接DHT的資料，課堂上用DHT11去接dht11的資料
//********************************************************

//Declare DHT讀取的溫度的值///////////
int valueCelciusDetect; 
//............................................

//LED的declare////////////////////////////////
int pinLightDetect =A2; //類比輸入的接腳
int valueLightDetect;
int pinLED = 13;
int threshold = 700;
//**********************************************

//關於Fan的declare////////////////////////////////////////////////////////
byte pinFan = 5;
//********************************************************


//關於LCD的declare////////////////////////////////////////////////////////
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址
//********************************************************

//關於threshold的declare
int roomTemp = 28;
//.........................

void setup()
{
      //關於LCD的setup////////////////////////////////////////////////////////
   lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光

    // 閃爍三次
    for(int i = 0; i < 3; i++) {
      lcd.backlight(); // 開啟背光
      delay(250);
      lcd.noBacklight(); // 關閉背光
      delay(250);
    }
    lcd.backlight();
   
  //輸出初始化文字
//    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
//    lcd.print("Hello World!");
//    delay(1000);
  //  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  //  lcd.print("GTWang.org");
  //  delay(8000);
  //  lcd.clear();
  
  // 告知使用者可以開始手動輸入訊息
  //  lcd.setCursor(0, 0);
  //  lcd.print("Use Serial Mon");
  //  lcd.setCursor(0, 1);
  //  lcd.print("Type to display");
  //  delay(5000);
  //  lcd.clear();
  //********************************************************
   
    lcd.clear();
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print(F("1.Connecting"));
    lcd.setCursor(0, 1); // 設定游標位置在第二行行首
    lcd.print("WiFi with esp.");
    delay(10000);
    lcd.clear();
 
   //大哥的esp setup/////////////////////////////////////// 
   bool esp01;
   Serial.begin(9600);     // 用於手動輸入文字
   esp01=esp01_9600(SID,PWD); 
   if (esp01)  Serial.println(F("Connecting OK !!"));
   
   //myTimer.every(1000, Rfid_seek); //每1秒執行一次
   delay (1000);
   //********************************************************

   //關於LED的setup////////////////////////////////////////////////////////
   pinMode(pinLightDetect, INPUT);
   //pinMode(pinLED, OUTPUT);
   //********************************************************

   //關於Fan的setup////////////////////////////////////////////////////////
   pinMode(pinFan, OUTPUT);
   //********************************************************

   lcd.setCursor(0, 0); // 設定游標位置在第一行行首
   lcd.print(F("2.Detecting temperature"));
   lcd.setCursor(0, 1);
   lcd.print(F("and humidity."));
   delay(5000);
   lcd.clear();

   lcd.setCursor(0, 0); // 設定游標位置在第一行行首
   lcd.print(F("3.Send data."));
   lcd.setCursor(0, 1);
   lcd.print(F(""));
   delay(5000);
   lcd.clear();
   
   lcd.setCursor(0, 0); // 設定游標位置在第一行行首
   lcd.print(F("4.If temperature"));
   lcd.setCursor(0, 1);
   lcd.print(F(">33C,light is on."));
   delay(10000);
   lcd.clear();

   lcd.setCursor(0, 0); // 設定游標位置在第一行行首
   lcd.print(F("5.If temperature"));
   lcd.setCursor(0, 1);
   lcd.print(F(">33C,fan is on."));
   delay(10000);
   lcd.clear();

   lcd.setCursor(4, 0);
   lcd.print(F("Temp"));
   lcd.setCursor(0, 1);
   lcd.print(F("Humidity"));

}

void loop()
{
  ////大哥的DHT loop 設定//////////  

  Humidity   = dht.readHumidity();  // 讀取濕度
  Celsius    = dht.readTemperature(); // 讀取攝氏溫度
  Fahrenheit = dht.readTemperature(true); // 讀取華氏溫度

  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%\t"));  // \t相當於按一下Tab
  
  Serial.print(F("Celsius: "));
  Serial.print(Celsius);
  Serial.print(F(" C\t"));

  Serial.print(F("Fahrenheit: "));
  Serial.print(Fahrenheit);
  Serial.print(F("F\n"));  // \n 表示換行

  delay(500);
  //********************************************************


  //關於LCD顯示的loop////////////////////////////////////////////////
  //  // 當使用者手動輸入訊息
  //   if (Serial.available()) {
  //     // 等待一小段時間，確認資料都接收下來了
  //     delay(100);
  //     // 清除舊訊息
  //     lcd.clear();
  //     // 讀取新訊息
  //     while (Serial.available() > 0) {
  //       // 將訊息顯示在 LCD 上
  //       lcd.write(Serial.read());
  //     }
  //   }

  int chk = dht.read(pinDHT); //課堂的DHT11，改成大哥的dht。腳位的變數由dataPin改成pinDHT
  if (chk == 0) {
    lcd.setCursor(9, 0);   // 顯示溫度
    lcd.print((float) Celsius, 4); //課堂的DHT11.temperature，改成大哥的dht.readTemperature()。腳位由2號改成4號
    lcd.print((char) 0xDF);
    lcd.print("C");
 
    lcd.setCursor(9, 1);   // 顯示濕度
    lcd.print((float) Humidity, 4);  //課堂的DHT11.humidity，改成大哥的dht.readHumidity()。腳位由2號改成4號
    lcd.print("%");
  }
  delay(500);
  
  //********************************************************
  //關於LED與fan的loop設定////////////////////////////////////////////////////////  
  //valueLightDetect=analogRead(pinLightDetect);  //用光敏電阻的值valueLightDetect 來手動控制LEDlight 與 fan
  //  valueLightDetect=analogRead(pinLightDetect);
  // Serial.println(valueLightDetect);
  //  delay (1000);
  //  
  // if (valueLightDetect > threshold) {
  //  digitalWrite(pinLED, LOW);
  //  Serial.println("LED is OFF!!!");
  // } else {
  //  digitalWrite(pinLED, HIGH);
  //  Serial.println("LED is ON");
  // }

   valueCelciusDetect = Celsius;  //用DHT讀取的溫度的值valueCelsiusDetect 來自動控制LEDlight 與 fan
   Serial.println(F("Temperature is: "));
   Serial.println(valueCelciusDetect);
   delay (1000);
   
   if (valueCelciusDetect < 27) {  //33改成室溫
    digitalWrite(pinLED, LOW);
    Serial.println(F("LED is OFF!!!"));
   } else {
    digitalWrite(pinLED, HIGH);
    Serial.println(F("LED is ON"));
   }
 
  delay (1000);

  if (valueCelciusDetect < 27) {  //33改成室溫
  digitalWrite(pinFan, HIGH);
  //Serial.println("HIGH");
  delay(2000);
  Serial.println(F("Fan is OFF!"));
  } else {
  digitalWrite(pinFan, LOW);
  //Serial.println("LOW");
  delay(2000);
  Serial.println(F("Fan is ON!"));
  }
  //********************************************************
  
    ////大哥的顯示設定/////////////
// bool send_flag=false;
// if (warning == 0) 
// {
 // send_flag=Send_Web_Line("taso2309.ygto.com","Open","女主人");
 // if (send_flag) Serial.println("Send Data Complete !!"); 
   
//  send_flag=Send_Web_Line("taso2309.ygto.com","Fire",String(Celsius)); //最後一欄一定要是文字，所以用String()把數字改成文字
//  if (send_flag) Serial.println("test !!");
  
  //send_flag=Send_Web_Line("taso2309.ygto.com","Gas","100");
  //if (send_flag) Serial.println("Send Data Complete !!");
  
//  delay (1000);
  
//  send_flag=send_open("taso2309.ygto.com","Open",99,"Open_Temp",100);
//  if (send_flag) Serial.println("Send Data OK !!");

//  send_flag=send_open("taso2309.ygto.com","KTemp",11,"KWet",50);
//  if (send_flag) Serial.println("Send Data OK !!");

//  send_flag=send_open("taso2309.ygto.com","LTemp",30,"LWet",60);
//  if (send_flag) Serial.println("Send Data OK !!");

//  warning=1;
// }

   //********************************************************
}




















//   Serial.println("Step 1. Connecting WiFi with esp.");
//   Serial.println("Step 2. Set up LCD.");
//   Serial.println("Step 3. Detecting humidity and temperature in celsius and fahrenheit.");
//   Serial.println("Step 4. Values of humidity and temperature shown on LCD.");
//   Serial.println("Step 5. If temperature > 33, LED light and fan are switched off.");
//   Serial.println("        If temperature < 33, LED light and fan are switched on");
//   Serial.println("Step 6. Data is sent to database.");
//   delay (20000);

//   Serial.println(F("---"));
//   Serial.println(F("Step 1.Set up LCD."));
//   Serial.println(F("---"));

//   Serial.println(F("---"));
//   Serial.println(F("Step 2.Connecting WiFi with esp."));
//   Serial.println(F("---"));

//  Serial.println(F("---"));
//  Serial.println(F("Step 3. Detecting humidity and temperature in celsius and fahrenheit."));
//  Serial.println(F("---"));

// Serial.println(F("---"));
// Serial.println(F("4.Values of humidity and temperature shown on LCD."));
// Serial.println(F("---"));
// delay(500);

//     Serial.println(F("---"));
//     Serial.println(F("Step 5. If temperature < 33, LED light and fan are switched off."));
//     Serial.println(F("        If temperature >= 33, LED light and fan are switched on."));
//     Serial.println(F("---"));
//        delay(500);

// Serial.println(F("---"));
// Serial.println(F("Step 6. Data is sent to database."));
// Serial.println(F("---"));
 
