#include <ESP8266WiFi.h>
#include <Wire.h>
#include <BH1750.h>
#include <WiFiUdp.h>
#include <Ticker.h>
BH1750 lightMeter;
/////////////////Тикер для часов
Ticker NTPClock;
//////////////////////////////
volatile unsigned long IR_KEY;   //код кнопки на пульте
//int luxold=0; //переменная для уменьшения чуствительности датчика света
int luxold1=0;
int luxold2=0;
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

const char* ssid     = "RT50";
const char* password = "zyxel2011";

unsigned int localPort = 2390;      // local port to listen for UDP packets

/////////NTP Time - inital
/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
///////////////////////////////////////////

WiFiServer server(80);  //Запускаем ВебСервер

void setup() {
       // prepare GPIO2
  pinMode(4, OUTPUT);
 /// digitalWrite(0, 0);

Wire.pins(2, 13);
Wire.begin();
Serial.begin(115200);
////Serial.setDebugOutput(true);
IR_KEY = 0; //переменная для получения кода кнопки с ИК-пульта
pinMode(14,INPUT_PULLUP); // Вход ИК приёмника
pinMode(12,INPUT_PULLDOWN); // Вход с ИК датчика
attachInterrupt(14, IRinterrupt, FALLING); // назначим прерывание на появление импульсов с ИК-приёмника
attachInterrupt(12, ir_sensor, CHANGE); // Прерывания для распознавания сигнала с ИК Датчика
lightMeter.begin();
///SwitchPwmOn(); //вызов функции плавного включения света
  // We start by connecting to a WiFi network
  ///Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(70);
    Serial.print(".");
  }
 /// Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 /// while (WiFi.status() != WL_CONNECTED) {
 ///   delay(500);
 ///   Serial.print(".");
 /// }
 /// Serial.println("");
 /// Serial.println("WiFi connected");
///////////////////////////////////////////UDP
 Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
  ///////////////////////////////////////////////End UDP
  // Start the server
  server.begin();
  Serial.println("Server started");
  Clock();
}
// the loop function runs over and over again forever
void loop() {
uint16_t lux = lightMeter.readLightLevel(); // Чтение датчика освещённости
  if (lux>2) {
  if (lux>luxold1 || lux<luxold2) {Serial.print("Light: "); Serial.print(lux); Serial.println(" lx");}
     luxold1=lux+1; //переменные для снижения чуствительности
     luxold2=lux-1; //переменные для снижения чуствительности
   if(IR_KEY) {Serial.println(IR_KEY,HEX); IR_KEY = 0;}//выводим код в терминал.

}
//////////////////////////////////////////////////////////////////////////////////////////
//Обработка Веб Запроса................................
// Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 // if req=
  // Match the request
  ////int val;
  /////if (req.indexOf("/gpio/0") != -1)
 /////  digitalWrite(0, 0);
/////  else if (req.indexOf("/gpio/1") != -1)
   /////// val = 1;
  ///// IncrementPWM();
 ///// else {
  /////  Serial.println("invalid request");
  /////  client.stop();
  ////  return;
///  }

  // Set GPIO2 according to the request
    client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
//  s += (val)?"high":"low";
//  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected

 // when the function returns and 'client' object is detroyed
///////////////////////////////////////////////////////////////////
}
void Clock(){
///////////////////////////////////
//get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
  ///  Serial.print("Seconds since Jan 1 1900 = " );
  ///  Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
  ///  Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
 ///   Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600+3); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  }
   }
//////////////////////////////////////////////////////////////////////////

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
void IncrementPWM(){ // Функция плавного включения света
 do {
  analogWrite(0, pwm);
 // analogWrite(11, pwm);
 // analogWrite(5, pwm);
  delay(10);
  pwm=pwm+1;
  pwm1=pwm1+1;
  pwm2=pwm2+1;
  pwm3=pwm3+1;
  } while(pwm<=1023);
}
//////////////////////////////////////////////////////////////////
// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}