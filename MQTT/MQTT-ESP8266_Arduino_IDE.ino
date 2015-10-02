
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>

byte sensor[8];
byte sensor1[8]={0x28, 0xB0, 0xE7, 0x20, 0x2, 0x0, 0x0, 0xAD};
byte sensor2[8]={0x28, 0x3C, 0x37, 0xF8, 0x8, 0x0, 0x0, 0x3};
byte sensor3[8]={0x28, 0x7A, 0x55, 0xA9, 0x5, 0x0, 0x0, 0xf9};
byte sensor4[8]={0x28, 0x96, 0x93, 0xF9, 0x5, 0x0, 0x1, 0x33};
byte sensor5[8]={0x28, 0x3E, 0x54, 0xF9, 0x5, 0x0, 0x0, 0xBD};
byte sensor6[8]={0x28, 0x21, 0x6B, 0xF8, 0x8, 0x0, 0x0, 0xA6};
byte sensor7[8]={0x28, 0x71, 0x2D, 0x47, 0x5, 0x0, 0x0, 0xF6};
byte sensor8[8]={0x28, 0x85, 0x52, 0xF9, 0x5, 0x0, 0x0, 0xDE};
byte sensor9[8]={0x28, 0x55, 0xB9, 0xA7, 0x5, 0x0, 0x0, 0x44};
byte sensor10[8]={0x28, 0xED, 0x43, 0xF8, 0x5, 0x0, 0x0, 0x82};
byte sensor11[8]={0x28, 0x7B, 0x54, 0xA8, 0x5, 0x0, 0x0, 0xAC};
byte sensor12[8]={0x28, 0x7, 0x6E, 0x47, 0x4, 0x0, 0x0, 0x7B};
byte sensor13[8]={0x28, 0x77, 0x55, 0xA9, 0x4, 0x0, 0x0, 0x93};
byte sensor14[8]={0x28, 0xF7, 0xCF, 0xD9, 0x4, 0x0, 0x0, 0x9D};
byte sensor15[8]={0x28, 0x8F, 0x9C, 0x47, 0x4, 0x0, 0x0, 0x15};
//Define the pin number on which the onewire bus is connected
OneWire  ds(14);  // on pin 14 (a 4.7K resistor is necessary)

const char *ssid =  "you SSID";   // cannot be longer than 32 characters!
const char *pass =  "password";   //

IPAddress server(54, 75, 170, 40); /ip adress of MQTT broker

//Add your topics to publish to here
char topicTemperature[] = "             ";
char topic1[] = "Temperature01";
char topic2[] = "Temperature02";
char topic3[] = "Temperature03";
char topic4[] = "Temperature04";
char topic5[] = "Temperature05";
char topic6[] = "Temperature06";
char topic7[] = "Temperature07";
char topic8[] = "Temperature08";
char topic9[] = "Temperature09";
char topic10[] = "Temperature10";
char topic11[] = "Temperature11";
char topic12[] = "Temperature12";
char topic13[] = "Temperature13";
char topic14[] = "Temperature14";
char topic15[] = "Temperature15";
//Topic handler

char topicRcv[] = "/0000";

//Payload handler
char payloadRcv[5];

//Change the clientname to your liking
String clientName = "Node1";
unsigned long PreviousMillis = 0;
int mqt=0;

///////////////////////////////////////////////////////////
void callback(const MQTT::Publish& pub) {
  // handle message arrived
}

WiFiClient wclient;
PubSubClient client(wclient, server, 11093); //connect 

void setup()
{
  // Setup console
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(10);
  Serial.println();
 // Serial.println();
 ds.reset();
  client.set_callback(callback);
  WiFi.begin(ssid, pass);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
  }
//delay(400);
if (client.connect(MQTT::Connect("Your name") 
.set_auth("qwertty", "dgfdfgdf"))) ///авторизация на сервере
}

void temperature()
{
  byte array;
  byte topicname=0;
  int circle=1;
 
  for ( circle = 1; circle <16; circle++) {           // we need 9 bytes
  
 
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
   char charVal[10];
  String payload = "";
  ds.reset();
  switch (circle){
    case 1:
      for (array=0; array<=7; array++) {sensor[array]=sensor1[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic1[topicname];};
      break;
    case 2:
      for (array=0; array<=7; array++) {sensor[array]=sensor2[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic2[topicname];};
       break;
    case 3:
      for (array=0; array<=7; array++) {sensor[array]=sensor3[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic3[topicname];};
      break;
    case 4:
      for (array=0; array<=7; array++) {sensor[array]=sensor4[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic4[topicname];};
      break;
    case 5:
      for (array=0; array<=7; array++) {sensor[array]=sensor5[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic5[topicname];};
      break;
    case 6:
      for (array=0; array<=7; array++) {sensor[array]=sensor6[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic6[topicname];};
      break;
    case 7:
      for (array=0; array<=7; array++) {sensor[array]=sensor7[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic7[topicname];};
      break;
     case 8:
      for (array=0; array<=7; array++) {sensor[array]=sensor8[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic8[topicname];};
      break;
     case 9:
      for (array=0; array<=7; array++) {sensor[array]=sensor9[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic9[topicname];};
      break;
     case 10:
      for (array=0; array<=7; array++) {sensor[array]=sensor10[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic10[topicname];};
      break;
     case 11:
      for (array=0; array<=7; array++) {sensor[array]=sensor11[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic11[topicname];};
      break;
     case 12:
      for (array=0; array<=7; array++) {sensor[array]=sensor12[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic12[topicname];};
      break;
     case 13:
      for (array=0; array<=7; array++) {sensor[array]=sensor13[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic13[topicname];};
      break;
     case 14:
      for (array=0; array<=7; array++) {sensor[array]=sensor14[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic14[topicname];};
      break;
     case 15:
      for (array=0; array<=7; array++) {sensor[array]=sensor15[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic15[topicname];};
      //circle=0;
      break;
  }
  ds.select(sensor);
 
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  delay(370);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
 //ds.depower();
  present = ds.reset();
  ds.select(sensor);
  ds.write(0xBE);         // Read Scratchpad
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
   }
   int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
     if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
     }
  celsius = (float)raw/16.0;
dtostrf(celsius, 4, 1, charVal);
for(int i=0;i<5;i++)
     {
        payload+=charVal[i];
     }
      //charVal[5]='\0';
     client.publish(topicTemperature, (char*) payload.c_str());
Serial.println(celsius);

 }
 }
 void loop()
{
   client.loop();

  if(WiFi.status() == WL_CONNECTED){
    unsigned long CurrentMillis=millis();
     client.loop();//This keeps the connection to the broker alive

    //Get and publish the DS18b20 temp every 30 seconds
    if(CurrentMillis-PreviousMillis>30000){
      PreviousMillis=CurrentMillis;
    temperature();
            }
  }
}
