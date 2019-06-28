/*
 Name:    door.ino
 Created: 2019/6/7 下午 03:20:48
 Author:  KP CHEN
*/


#include <WiFiEspServer.h>
#include <WiFiEspClient.h>
#include <WiFiEsp.h>
#include "esp_2_3_line.h"  //by TSH 
#include <Servo.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
int trigPin = 6;                  //Trig Pin
int echoPin = 7;                  //Echo Pin
long duration, cm, inches;
byte state = 0;
#define LEDR A3
#define LEDG A4
#define LEDB A5

Servo myservo;

int warning = 0;

const char* SID = "And";
const char* PWD = "123456789";

void setup()
{
  bool esp01;

  Serial.begin(9600);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  turnoff();
  digitalWrite(LEDR, HIGH);
  esp01 = esp01_9600(SID, PWD);
  if (esp01) {
    Serial.println("Connecting OK !!");
    turnoff();
    digitalWrite(LEDG, HIGH);
  }
  delay(1000);
  myservo.attach(9, 500, 2400); // 修正脈衝寬度範圍
  myservo.write(90); // 一開始先置中90度
  delay(1000);
  pinMode(trigPin, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin, INPUT);


}

void loop()
{
  //Serial.println("0:");
  //Serial.println(state);
  while (state == 0)
  {
    //Serial.println("1");
    //Serial.println(state);
    wifi_open();
  }

  while (state == 1)
  {
    //Serial.println("4");
    //Serial.println(state);
    open_door();
  }

  while (state == 2)
  {
    //Serial.println("6");
    //Serial.println(state);
    close_door();
  }
  //Serial.println("7");
  //Serial.println(state);
}

void turnoff() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}

void wifi_open() {
  WiFiEspClient client = server.available();  // listen for incoming clients
  if (client)
  {                               // if you get a client,
    //Serial.println("2");
    //Serial.println(state);
    Serial.println("New client");             // print a message out the serial port
    buf.init();                               // initialize the circular buffer
    while (client.connected())
    {              // loop while the client's connected
      if (client.available())
      {               // if there's bytes to read from the client,
        char c = client.read();               // read a byte, then
        buf.push(c);
        Serial.println(c);
        if (buf.endsWith("GET /?"))
        {
          delay(1000);
          //Serial.println("Turn led ON");
          turnoff();
          digitalWrite(LEDB, HIGH);    // turn the LED on (HIGH is the voltage level)
          state = 1;
          //Serial.println("3");
          //Serial.println(state);
          client.stop();
          //Serial.println("----------");
        }
      }
    }
  }
}

void open_door()
{
  turnoff();
  digitalWrite(LEDR, HIGH);
  for (int i = 600; i <= 2400; i += 100)
  {
    myservo.writeMicroseconds(i); // 直接以脈衝寬度控制
    delay(300);
    //Serial.println(i);
  }//開門   
  turnoff();
  digitalWrite(LEDB, HIGH);

  state = 2;
  //Serial.println("5");
  //Serial.println(state);
}

void close_door()
{  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);             // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間

  cm = (duration / 2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  inches = (duration / 2) / 74;

  Serial.print("Distance : ");
  Serial.print(inches);
  Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm < 5 && cm>1)
  {
    turnoff();
    digitalWrite(LEDR, HIGH);
    for (int i = 2400; i >= 600; i -= 100)
    {
      myservo.writeMicroseconds(i); delay(300);
    }
    turnoff();
    digitalWrite(LEDG, HIGH);
    state = 0;
    //Serial.println("7");
    //Serial.println(state);
  }
  delay(300);
}
