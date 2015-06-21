#include "ESP8266WiFi.h"
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;
volatile unsigned long IR_KEY;   //код кнопки на пульте
//int luxold=0; //переменная для уменьшения чуствительности датчика света
int luxold1=0;
int luxold2=0;
int a=0; // переменная переключения режима, при нажатии кнопки она принимает значение +1
int b=0; //
int c=0; //
int d=0; //
int e=0; //
int f=0; //
int g=0; //
int ir_sens=0; //ПЕРЕМЕННАЯ ДЛЯ СЧИТЫВАНИЯ ПОКАЗАНИЙ ик-дАТЧИКА
unsigned int pwm1=0;
unsigned int pwm2=0;
unsigned int pwm3=0;
unsigned int pwm=0;
unsigned int pwm_on_1=0;
unsigned int pwm_on_2=0;
unsigned int pwm_on_3=0;
unsigned int pwm_max_1=0;
unsigned int pwm_max_2=0;
unsigned int pwm1Off=0;
unsigned int pwm2Off=0;
unsigned int pwm3Off=0;
// the setup function runs once when you press reset or power the board

/////////////////////////
MDNSResponder mdns;
WiFiServer server(80);
const char* ssid = "BUBBLES";
String st;
////////////////////////

void setup() {
Wire.pins(2, 13);
Wire.begin();
Serial.begin(9600);
IR_KEY = 0; //переменная для получения кода кнопки с ИК-пульта
pinMode(14,INPUT_PULLUP); // Вход ИК приёмника
pinMode(12,INPUT_PULLDOWN); // Вход с ИК датчика
attachInterrupt(14, IRinterrupt, FALLING); // назначим прерывание на появление импульсов с ИК-приёмника
attachInterrupt(12, ir_sensor, CHANGE); // Прерывания для распознавания сигнала с ИК Датчика
lightMeter.begin();
///SwitchPwmOn(); //вызов функции плавного включения света
 Serial.println("Running...");
 //////////////////////////////////////////////////////////////////////////
 ///Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
  // read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  String esid;
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  String epass = "";
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  Serial.print("PASS: ");
  Serial.println(epass);  
  if ( esid.length() > 1 ) {
      // test esid 
      WiFi.begin(esid.c_str(), epass.c_str());
      if ( testWifi() == 20 ) { 
          launchWeb(0);
          return;
      }
  }
  setupAP(); 
 ////////////////////////////////////////////////////////////////////////////////
 }
//}

// the loop function runs over and over again forever
void loop() {
uint16_t lux = lightMeter.readLightLevel(); // Чтение датчика освещённости
  if (lux>2) {
  if (lux>luxold1 || lux<luxold2) {Serial.print("Light: "); Serial.print(lux); Serial.println(" lx");}
     luxold1=lux+1; //переменные для снижения чуствительности
     luxold2=lux-1; //переменные для снижения чуствительности
   if(IR_KEY) {Serial.println(IR_KEY,HEX); IR_KEY = 0;}//выводим код в терминал.
  
}
}
void IRinterrupt(){ //прерывание для обработки импульсов с ик ПРИЁМНИКА
  static unsigned long key, prevTime;
  unsigned long currTime, d_ir;
  currTime = micros();
  d_ir = currTime - prevTime;
 // if(d_ir < 10) return;        // "дребезг"
  if(d_ir < 1400){               // "0"
    key = key << 1;
    prevTime = currTime;
    return; }
  if(d_ir < 2400){               // "1"
    key = key << 1;
    key++;
    prevTime = currTime;
    return;}
  if(d_ir < 14000)   IR_KEY = key; // код кнопки получен
  prevTime = currTime;
////Serial.println(IR_KEY,HEX);
////if (IR_KEY == 0xC000305) {if (pwm1<=247) {pwm1=pwm1+7;analogWrite(10, pwm1);}}// увеличение значения pwm1 на 7
////if (IR_KEY == 0xC003105) {if (pwm1>=7) {pwm1=pwm1-7;analogWrite(10, pwm1);} else {pwm1=0;analogWrite(10, pwm1);}}// уменьшение значения pwm1 на 7
////if (IR_KEY == 0xC000D05) {if (pwm2<=247) {pwm2=pwm2+7;analogWrite(11, pwm2);}}// увеличение значения pwm2 на 7
////if (IR_KEY == 0x3000F05) {if (pwm2>=7) {pwm2=pwm2-7;analogWrite(11, pwm2);} else {pwm2=0;analogWrite(11, pwm2);}}// уменьшение значения pwm2 на 7
////if (IR_KEY == 0xC000905) {if (pwm3<=247) {pwm3=pwm3+7;analogWrite(5, pwm3);}}// увеличение значения pwm3 на 7
////if (IR_KEY == 0xC002505) {if (pwm3>=7) {pwm3=pwm3-7;analogWrite(5, pwm3);} else {pwm3=0;analogWrite(5, pwm3);}}
///if (IR_KEY == 0x3030D05) {SwitchPwmOn_if_On();}
}
void ir_sensor(){ //Функция прерывания для считывания показаний с ИК Датчика
ir_sens=digitalRead(12);
Serial.println(ir_sens);
if (ir_sens==1) digitalWrite(4, HIGH); //Включение светодиоад
if (ir_sens==0) digitalWrite(4, LOW); //Отключение светодиода
}
/////////////////////////////////////////////////////////////////////
int testWifi(void) {
  int c = 0;
  Serial.println("Waiting for Wifi to connect");  
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { return(20); } 
    delay(500);
    Serial.print(WiFi.status());    
    c++;
  }
  Serial.println("Connect timed out, opening AP");
  return(10);
} 

void launchWeb(int webtype) {
          Serial.println("");
          Serial.println("WiFi connected");
          Serial.println(WiFi.localIP());
          Serial.println(WiFi.softAPIP());
          if (!mdns.begin("esp8266", WiFi.localIP())) {
            Serial.println("Error setting up MDNS responder!");
            while(1) { 
              delay(1000);
            }
          }
          Serial.println("mDNS responder started");
          // Start the server
          server.begin();
          Serial.println("Server started");   
          int b = 20;
          int c = 0;
          while(b == 20) { 
             b = mdns1(webtype);
           }
}

void setupAP(void) {
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
     {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
     }
  }
  Serial.println(""); 
  st = "<ul>";
  for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      st += "<li>";
      st +=i + 1;
      st += ": ";
      st += WiFi.SSID(i);
      st += " (";
      st += WiFi.RSSI(i);
      st += ")";
      st += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
      st += "</li>";
    }
  st += "</ul>";
  delay(100);
  WiFi.softAP(ssid);
  Serial.println("softap");
  Serial.println("");
  launchWeb(1);
  Serial.println("over");
}

int mdns1(int webtype)
{
  // Check for any mDNS queries and send responses
  mdns.update();
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return(20);
  }
  Serial.println("");
  Serial.println("New client");

  // Wait for data from client to become available
  while(client.connected() && !client.available()){
    delay(1);
   }
  
  // Read the first line of HTTP request
  String req = client.readStringUntil('\r');
  
  // First line of HTTP request looks like "GET /path HTTP/1.1"
  // Retrieve the "/path" part by finding the spaces
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    Serial.print("Invalid request: ");
    Serial.println(req);
    return(20);
   }
  req = req.substring(addr_start + 1, addr_end);
  Serial.print("Request: ");
  Serial.println(req);
  client.flush(); 
  String s;
  if ( webtype == 1 ) {
      if (req == "/")
      {
        IPAddress ip = WiFi.softAPIP();
        String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
        s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
        s += ipStr;
        s += "<p>";
        s += st;
        s += "<form method='get' action='a'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
        s += "</html>\r\n\r\n";
        Serial.println("Sending 200");
      }
      else if ( req.startsWith("/a?ssid=") ) {
        // /a?ssid=blahhhh&pass=poooo
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
        String qsid; 
        qsid = req.substring(8,req.indexOf('&'));
        Serial.println(qsid);
        Serial.println("");
        String qpass;
        qpass = req.substring(req.lastIndexOf('=')+1);
        Serial.println(qpass);
        Serial.println("");
        
        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
          {
            EEPROM.write(i, qsid[i]);
            Serial.print("Wrote: ");
            Serial.println(qsid[i]); 
          }
        Serial.println("writing eeprom pass:"); 
        for (int i = 0; i < qpass.length(); ++i)
          {
            EEPROM.write(32+i, qpass[i]);
            Serial.print("Wrote: ");
            Serial.println(qpass[i]); 
          }    
        EEPROM.commit();
        s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 ";
        s += "Found ";
        s += req;
        s += "<p> saved to eeprom... reset to boot into new wifi</html>\r\n\r\n";
      }
      else
      {
        s = "HTTP/1.1 404 Not Found\r\n\r\n";
        Serial.println("Sending 404");
      }
  } 
  else
  {
      if (req == "/")
      {
        s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266";
        s += "<p>";
        s += "</html>\r\n\r\n";
        Serial.println("Sending 200");
      }
      else if ( req.startsWith("/cleareeprom") ) {
        s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266";
        s += "<p>Clearing the EEPROM<p>";
        s += "</html>\r\n\r\n";
        Serial.println("Sending 200");  
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
        EEPROM.commit();
      }
      else
      {
        s = "HTTP/1.1 404 Not Found\r\n\r\n";
        Serial.println("Sending 404");
      }       
  }
  client.print(s);
  Serial.println("Done with client");
  return(20);
}

////////////////////////////////////////////
