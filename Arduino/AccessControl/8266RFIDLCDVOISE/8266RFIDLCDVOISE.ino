//#include "Timer.h"
#include "esp_2_3_rfid.h"  //by TSH 
//Timer myTimer;          //建立定時執行物件
#define ledPin  4
byte state = 0;
boolean peoplein = true;
////////////////////////////////////////////////////////////////
//蜂鳴器
void bee();
void start();
byte buzzer = 5;//腳位D5
const int toneTable[7][2] = {
  { 262, 523},  // C Do
  { 294, 587},  // D Re
  { 330, 659},  // E Mi
  { 349, 698},  // F Fa
  { 392, 784},  // G So
  { 440, 880},  // A La
  { 494, 988}   // B Si
};

char toneName[] = "CDEFGAB";
char beeTone[] = "EEGGCCBBAEAAABBEEBBGEG";
int beeBeat[] = { 1,1,1,1,1,1,1,1,1,1,3, 1,1,1,1,1,1,1,1,1,1,1 };
int beeKey[] = { 1,1,1,1,2,2,1,1,1,1,1, 1,1,1,1,2,2,1,1,1,1,1 };
char startTone[] = "CDEFGABC";
int startBeat[] = { 1,1,1,1,1,1,1,1 };
int startKey[] = { 1,1,1,1,1,1,1,2 };
////////////////////////////////////////////////////////////////
//ESP01
const char* SID = "And";
const char* PWD = "123456789";
////////////////////////////////////////////////////////////////
//RFID
void rfidread();
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>
/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 10
#define RESET_DIO 9
int productname[5] = { 193,112,34,96,53 };
int product[5] = { 1,2,3,4,5 };
String homemember[5] = { "Father","Mother","Sister","Brother","Dog" };
byte i = 0;
int ID;
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO);
///////////////////////////////////////////////////////////////
//LCD
//引入Wire與LiquidCrystal_I2C函式庫
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// 設定 LCD I2C 位址
// Set the pins on the I2C chip used for LCD connections:
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
////////////////////////////////////////////////////////////////
//人體紅外線HC-SR501
int trigPin = 6;                  //Trig Pin
int echoPin = 7;                  //Echo Pin
long duration, cm, inches;
void pir();
////////////////////////////////////////////////////////////////

void setup()
{
  bool esp01;
  Serial.begin(9600);


  ///////////////////////////////////////////////////////////////
  //LCD
  // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("Connecting......");
  esp01 = esp01_9600(SID, PWD);

  pinMode(ledPin, OUTPUT);//led
  pinMode(trigPin, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin, INPUT);

  if (esp01)
  {
    //Serial.println(F("Connecting OK !!"));
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("Connecting OK !!");
    delay(2000);
  }
  ///////////////////////////////////////////////////////////////
  //RFID
  /* Enable the SPI interface */
  SPI.begin();
  /* Initialise the RFID reader */
  RC522.init();
  ///////////////////////////////////////////////////////////////
  pinMode(buzzer, OUTPUT);//蜂鳴器

  noTone(buzzer);
  //////////////////////////////////////////////////////////////
   //myTimer.every(1000, Rfid_seek); //每1秒執行一次
  delay(1000);
}

void loop()
{
  state = 0;
  lcd.clear();
  while (state == 0)
  {
    pir();
    delay(1000);
    lcd.clear();

    while (state == 1)
    {
      digitalWrite(ledPin, HIGH);
      start();
      lcd.clear();
      ////////////////////////////////////////////////////
      lcd.setCursor(0, 0); // 設定游標位置在第一行行首
      lcd.print("Swipe Card!!");
      /* Has a card been detected? */
      if (RC522.isCard())
      {
        rfidread(); 
      }
      ////////////////////////////////////////////////////
      else { state = 1;   delay(200); }
    }
  }
  delay(5000);
  //digitalWrite(ledPin, LOW);
}


void pir()
{
  lcd.clear();
  lcd.setCursor(0, 1); // 設定游標位置在第一行行首
  lcd.print(F(" No Motion!!"));
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間

  cm = (duration / 2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  inches = (duration / 2) / 74;


  //Serial.print(F("Distance : "));  
  //Serial.print(inches);
  //Serial.print(F("in,   "));
  Serial.print(cm);
  //Serial.print(F("cm"));
  //Serial.println();

  if (cm < 5) {
    lcd.clear();
    lcd.setCursor(0, 1); // 設定游標位置在第一行行首
    lcd.print(F("Motion!!"));
    state = 1;
  }

  delay(250);
}

void rfidread()
{
  int warning = 0;
  bool send_flag = false;
  /* If so then get its serial number */
  RC522.readCardSerial();
  //Serial.print(RC522.serNum[i],DEC);

  //Serial.println("Card detected:");

  /* Output the serial number to the UART */
  ID = RC522.serNum[0];
  //Serial.print(ID);
   // Serial.println(" ");
  for (i = 0; i < 5; i++)
  {
    if (productname[i] == ID)
    {
      bool send_flag = false;
      if (warning == 0)
      {
        // Serial.println("Welcome "+homemember[i]);
        bee();
        lcd.clear();
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Card CORRECT !!!");
        lcd.setCursor(0, 1); // 設定游標位置在第二行行首
        lcd.print("HELLO " + homemember[i] + " !!");
        send_flag = send_opendoor("192.168.43.36");
        if (send_flag) //Serial.println(F("Send WIFI OK !!"));
          send_flag = Send_Web_Line("taso2309.ygto.com", "Open", homemember[i]);
        if (send_flag) //Serial.println(F("Send Data Complete !!")); 
          send_flag = send_open("taso2309.ygto.com", "Open", product[i], "Open_Temp", 1);
        if (send_flag) //Serial.println(F("Send Data OK !!"));

          delay(1000);
        warning = 1;
        state = 2;
        digitalWrite(ledPin, LOW);////////////測試用
        break;
      }
    }
    else if (i == 5)
    {
      //Serial.println(F("Access Denied")); 
      state = 1;
      break;
    }
  }
  //Serial.println();
  //Serial.println();
}


int getTone(char symbol) { ////////////////////////////蜂鳴器
  int toneNo = 0;
  for (int ii = 0; ii < 7; ii++) {
    if (toneName[ii] == symbol) {
      toneNo = ii;
      break;
    }
  }
  return toneNo;
}


void bee()
{
  int ii, length, toneNo;
  int duration;
  int toneNo2 = 0;
  // bee
  length = sizeof(beeTone) - 1;
  for (ii = 0; ii < length; ii++) {
    toneNo = getTone(beeTone[ii]);
    toneNo2 = beeKey[ii];
    duration = beeBeat[ii] * 790;
    tone(buzzer, toneTable[toneNo][toneNo2]);
    delay(duration);
    noTone(buzzer);
  }

  delay(2000);

  noTone(buzzer);

  delay(2000);
}



void start()
{
  int ii, length, toneNo;
  int duration;
  int toneNo2 = 0;
  // start
  length = sizeof(startTone) - 1;
  for (ii = 0; ii < length; ii++) {
    toneNo = getTone(startTone[ii]);
    toneNo2 = startKey[ii];
    duration = startBeat[ii] * 100;
    tone(buzzer, toneTable[toneNo][toneNo2]);
    delay(duration);
    noTone(buzzer);
  }
  noTone(buzzer);
  delay(2000);
}
