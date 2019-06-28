#include <DHT.h>
#include <UseStepMoto.h>
#include <esp_2_3_line.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS A0
#define MQ2PIN A1
#define DHTPIN 13  
#define DHTTYPE DHT11

const char *SID = "Steven Mate 8";
const char *PWD = "23367203";

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int relayPin = 12;
int buttonPin1 = 7;
int buttonPin2 = 6;
int buttonPin3 = 5;
int buttonPin4 = 4;
int buttonPin_ppl = A2;
int buttonPin = A3;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState_ppl = 0;
int buttonState = 0;
int maxGas = 0;
int maxLiquid = 0;
bool data_flag = false;
bool send_flag = false;

void setup() 
{
  Serial.begin(9600);
  Serial.println(F("Start"));

  bool esp01;
  esp01=esp01_9600(SID,PWD);
  if(esp01)
    Serial.println(F("Connecting OK!"));
  pinMode(buttonPin,INPUT);
  pinMode(relayPin, OUTPUT);  
  
  dht.begin();
  sensors.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print(F("Start"));
  delay(1000);
  lcd.clear(); //顯示清除
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int sensor_volt;
  float sensorValue;

  //  DHT
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F(" %\t"));
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F(" *C\t "));

  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print(F("Humi: "));
  lcd.print(h);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print(F("Temp: "));
  lcd.print(t);
  delay(2000);
  lcd.clear(); //顯示清除

  if(h>70)
  {
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }

  //  MQ2
  sensorValue = analogRead(MQ2PIN);
  sensor_volt = sensorValue*1000/1024*5.0;
  Serial.print(F("Sensor_volt = "));
  Serial.print(sensor_volt);
  Serial.print(F("V\t"));

  //  DallasTemperature
  sensors.requestTemperatures();
  Serial.print(F("Protein = "));
  Serial.println(sensors.getTempCByIndex(0));

  /*
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print(F("Gas: "));
  lcd.print(sensor_volt);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print(F("Liquid : "));
  lcd.print(sensors.getTempCByIndex(0));
  delay(2000);
  lcd.clear(); //顯示清除
  */

  buttonState_ppl = digitalRead(buttonPin_ppl);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  if(buttonState_ppl == HIGH)
  {
    if(maxGas<sensor_volt)
    {
      maxGas = sensor_volt;
    }
    if(maxLiquid<sensors.getTempCByIndex(0))
    {
      maxLiquid = sensors.getTempCByIndex(0);
    }
    if(buttonState1 == HIGH)
      check_ppl(maxGas, maxLiquid, 1);
    if(buttonState2 == HIGH)
      check_ppl(maxGas, maxLiquid, 2);
    if(buttonState3 == HIGH)
      check_ppl(maxGas, maxLiquid, 3);
    if(buttonState4 == HIGH)
      check_ppl(maxGas, maxLiquid, 4);
  }


  
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH)
  {
    Serial.print(F("Tissue Empty!"));
    StepMoto_THH('B', 8, 9, 10, 11, 1);

    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print(F("Tissue Empty!"));
    delay(2000);
    lcd.clear(); //顯示清除

    send_flag=send_open("taso2309.ygto.com","Paper",1,"Paper1",1,"Paper2",1);
    send_flag=Send_Web_Line("taso2309.ygto.com","Paper","沒衛生紙了！");
    if (send_flag) Serial.println(F("Send Data Complete !!"));    
  } 
}

bool check_ppl(int gas, int liquid, int num)
{
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print(F("Gas: "));
    lcd.print(gas);
    lcd.setCursor(0, 1); // 設定游標位置在第二行行首
    lcd.print(F("Liquid : "));
    lcd.print(liquid);
    delay(2000);
    lcd.clear(); //顯示清除
    send_flag=send_open("taso2309.ygto.com","People",num,"Liquid",maxLiquid,"Gas",maxGas);
    Serial.println(F("Data Send"));
    maxGas = 0;
    maxLiquid = 0;
}
