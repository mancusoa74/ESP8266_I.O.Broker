#include <ESP8266WiFi.h>
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

const char* ssid     = "RT50";
const char* password = "zyxel2011";

WiFiServer server(80);  //Запускаем ВебСервер

void setup() {
// prepare GPIO2
  pinMode(0, OUTPUT);
  digitalWrite(0, 0);
  
Wire.pins(2, 13);
Wire.begin();
Serial.begin(115200);
IR_KEY = 0; //переменная для получения кода кнопки с ИК-пульта
pinMode(14,INPUT_PULLUP); // Вход ИК приёмника
pinMode(12,INPUT_PULLDOWN); // Вход с ИК датчика
attachInterrupt(14, IRinterrupt, FALLING); // назначим прерывание на появление импульсов с ИК-приёмника
attachInterrupt(12, ir_sensor, CHANGE); // Прерывания для распознавания сигнала с ИК Датчика
lightMeter.begin();
///SwitchPwmOn(); //вызов функции плавного включения света
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
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
  if req=
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
