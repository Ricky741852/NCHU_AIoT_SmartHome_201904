
#include "esp_6_7_line.h"  //by TSH 
#include <IRremote.h>

IRsend irsend; // IRRemote限定使用數位腳位3

int warning=0;

const char *SID="*********";
const char *PWD="********";

const int LED=13;     
int value=LOW;
      unsigned long Val;
      int bits;
      char sid;


void decline(String);

void setup()
{
 pinMode(5, OUTPUT);
 pinMode(13,OUTPUT);
 digitalWrite(13,LOW);
 init_LCD(""); 
 esp01_9600(SID,PWD); 
 delay (500);
 init_LCD(ipToString(WiFi.localIP()));
}

void loop()
{
 LED13();
}

void LED13()
{

    WiFiEspClient client=server.available();
    if (!client) {return;}
    while (!client.available()) {delay(2);}
    String request=client.readStringUntil('\r');
    if (request[5]!='?')
    {
      client.flush();
      client.stop();
      lcd.setCursor(0, 1); // 設定游標位置在第二行行首
      lcd.print("Stand by .....");
      return;
    }
    
    decline(request); 
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<script language=javascript>");
    client.println("function exit\(\)");
    client.println("\{");
    client.println("window.close\(\)\;");
    client.println("\}");
    client.println("</script>"); 
    client.println("<BODY onLoad=\"setTimeout('exit()', 3000)\">"); 
    client.println("</BODY>");
    client.println("</HTML>");
    delay(1);
    
    lcd.setCursor(0, 1); // 設定游標位置在第二行行首
    lcd.print("OKokok .....");

    if (sid=='1')
    {
      irsend.sendSony(Val, bits);
      lcd.setCursor(0, 1); // 設定游標位置在第二行行首
      lcd.print("Sucess !!");
      delay(500);
    }
    client.stop();
    
} 

void decline(String x)
{
 //Serial.println(x); 
 int i;
 char valtemp[10],bitstemp[3];  
 char* str; 
 for (i=0;i<=50;i++)
 {
  if (x[10+i]=='&')
  {
   valtemp[i]='\0';
   break;
  }
  valtemp[i]=x[10+i];
 }
 bitstemp[0]=x[11+i];
 bitstemp[1]=x[12+i];
 bitstemp[2]='\0';

 Val=atol(valtemp); 
 bits=atoi(bitstemp);
 sid=x[13+i];

}
