#include <esp_2_3_line.h>
#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

byte gasPin = A0;
byte buzzerPin = 6;
byte ledRed = 10;
byte ledYel = 11;
byte ledWhi = 12;
byte ledGre = 13;
byte relayPin = 8;

int gasWarning=150;
byte tempWarning=30;
bool warning =false;

char *SID="Steven Mate 8";
char *PWD="23367203";

void setup()
{
 Serial.begin(9600);
 pinMode(buzzerPin, OUTPUT);
 pinMode(ledRed,OUTPUT);
 pinMode(ledYel,OUTPUT);
 pinMode(ledWhi,OUTPUT);
 pinMode(ledGre,OUTPUT);
 pinMode(relayPin,OUTPUT);
 digitalWrite(relayPin,LOW);
 

 bool esp01;
 esp01=esp01_9600(SID,PWD); 
 if (esp01)  
 {
   //Serial.println("Connecting OK !!");
    for(int i=0; i<3; i++){
    digitalWrite(ledGre, HIGH);
    delay(500);
    digitalWrite(ledGre, LOW);
    delay(500);
    }

 dht.begin();
 
 delay (1000);
 }
}

void loop()
{
 int gasState = analogRead(gasPin);
 float t = dht.readTemperature();

 Serial.println(gasState);
 delay(1000);

 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print((char)0xDF);
 Serial.print(" *C ");

 bool send_flag=false;
 if (gasState>gasWarning)
  {
    warning=true;
  }
  
 if(warning==true)
 {
  digitalWrite(ledGre, HIGH);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(relayPin, HIGH);
  //Serial.println("Gas Concentration HIGH!!!");
  //Serial.println("Turn on the Fan!");
  
  send_flag=send_open("taso2309.ygto.com","KTemp","","KWet",gasState);
  if (send_flag) 
  {
    for(int i=0; i<3; i++)
    {
      digitalWrite(ledRed, HIGH);
      delay(500);
      digitalWrite(ledRed, LOW);
      delay(500);
  
    }//for end
    
    Serial.println("Send Data OK !!");
    
  }//if end

  delay (3000);
  
  send_flag=Send_Web_Line("taso2309.ygto.com","Gas",String(gasState));
  if (send_flag) 
  {
    for(int i=0; i<3; i++)
    {
      digitalWrite(ledYel, HIGH);
      delay(500);
      digitalWrite(ledYel, LOW);
      delay(500);
    }//for end
    Serial.println("Send Line OK!!");
  }//if end

  warning=false;

 }//if end
 else
  {
    digitalWrite(ledGre, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    //Serial.println("Gas Concentration Normal");
  }





  if(t>tempWarning)
  {
    digitalWrite(ledWhi, HIGH);
    digitalWrite(buzzerPin, HIGH);
   // Serial.println("Temperature too HIGH!!!");

    send_flag=Send_Web_Line("taso2309.ygto.com","Fire",String(t));
    if (send_flag) 
    {
        for(int i=0; i<3; i++)
        {
          digitalWrite(ledYel, HIGH);
          delay(500);
          digitalWrite(ledYel, LOW);
          delay(500);
        }//for end
    Serial.println("Send Line OK !!");
    }//if end

    delay (3000);
  
    send_flag=send_open("taso2309.ygto.com","KTemp",t,"KWet","");
    if (send_flag) 
    {

      for(int i=0; i<3; i++)
      {
        digitalWrite(ledRed, HIGH);
        delay(500);
        digitalWrite(ledRed, LOW);
        delay(500);
      }//for end

     Serial.println("Send Data OK !!");
      delay(2000);
      
    }//if end

   }
  else
  {
      digitalWrite(ledWhi, LOW);
      digitalWrite(buzzerPin, LOW);
     // Serial.println("Temperature Normal");  
  }//else end

 //if end
}//end loop
