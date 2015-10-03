///#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
//#include <DNSServer.h>
#include <ESP8266WiFiMulti.h>
#include <FS.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <Wire.h>
#include <BH1750.h>
//#include <SendAnEmail.ino>
//#include <FBrowser.ino>
BH1750 lightMeter;

#include <pgmspace.h>
#include <RtcDS1307.h>
RtcDS1307 Rtc;


#define DBG_OUTPUT_PORT Serial

//////////////////////////////////////////////////////////////////////////////////
//Blync call
///////////////////////////////////////////////////////////////////////////////////
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
///#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
////////////////////////////////////////////////////////////////////////////////////////
const byte DNS_PORT = 53;
//IPAddress apIP(192, 168, 0, 1);
//DNSServer dnsServer;
///////ESP8266WebServer webServer(80);

// Include API-Headers
extern "C" {
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
///#include "mem.h"
#include "user_interface.h"
#include "cont.h"
}

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char memory;
char auth[] = "fghgfhgfh194132f17";
bool result;
int CircleTemp=0;
int VirtTemp1=0;
int VirtTemp2=0;
int TempCounter=0;
long wiFiConnTime = 0; // measure time till wifi connect success
byte sensor[8];
byte sensor1[8]={0x28, 0xB0, 0xE7, 0x20, 0x2, 0x0, 0x0, 0xAD};
byte sensor2[8]={0x28, 0x3C, 0x37, 0xF8, 0x5, 0x0, 0x0, 0x3};
byte sensor3[8]={0x28, 0x7A, 0x55, 0xF9, 0x5, 0x0, 0x0, 0xD9};
byte sensor4[8]={0x28, 0x96, 0x93, 0xF9, 0x5, 0x0, 0x0, 0x33};
byte sensor5[8]={0x28, 0x3E, 0x54, 0xF9, 0x5, 0x0, 0x0, 0xBD};
byte sensor6[8]={0x28, 0x21, 0x6B, 0xF8, 0x5, 0x0, 0x0, 0xA6};
byte sensor7[8]={0x28, 0x71, 0x2D, 0x47, 0x5, 0x0, 0x0, 0xF6};
byte sensor8[8]={0x28, 0x85, 0x52, 0xF9, 0x5, 0x0, 0x0, 0xDE};
byte sensor9[8]={0x28, 0x55, 0xB9, 0x47, 0x5, 0x0, 0x0, 0x34};
byte sensor10[8]={0x28, 0xED, 0x43, 0xF8, 0x5, 0x0, 0x0, 0x82};
byte sensor11[8]={0x28, 0x7B, 0x54, 0xF8, 0x5, 0x0, 0x0, 0xAC};
byte sensor12[8]={0x28, 0x7, 0x6E, 0x47, 0x5, 0x0, 0x0, 0x7B};
byte sensor13[8]={0x28, 0x77, 0x55, 0xF9, 0x5, 0x0, 0x0, 0x93};
byte sensor14[8]={0x28, 0xF7, 0xCF, 0xD9, 0x1, 0x0, 0x0, 0x9D};
byte sensor15[8]={0x28, 0x8F, 0x9C, 0x47, 0x5, 0x0, 0x0, 0x15};
//Define the pin number on which the onewire bus is connected
OneWire  ds(14);  // on pin 14 (a 4.7K resistor is necessary)'

int luxold1=0;
int luxold2=0;

const char* hostThingSpeak = "api.thingspeak.com";
const char* channelId1   = "29316";  // number, 6 digits
const char* writeKey1 = "fghgfh";  // your write key for this channel
const char* writeKey2 = "8fghgfh";  // your write key for this channel 2
//const char* channelARIkey;
const char* field;
int temp=1; //var for ThingSpeak
int PWM=0; //var for PWM from Blynk.cc
String temp01 ="0"; //var for temp to the ThingSpeak
String temp02 ="0"; //var for temp to the ThingSpeak
String temp03 ="0"; //var for temp to the ThingSpeak
String temp04 ="0"; //var for temp to the ThingSpeak
String temp05 ="0"; //var for temp to the ThingSpeak
String temp06 ="0"; //var for temp to the ThingSpeak
String temp07 ="0"; //var for temp to the ThingSpeak
String temp08 ="0"; //var for temp to the ThingSpeak
String temp09 ="0"; //var for temp to the ThingSpeak
String temp10 ="0"; //var for temp to the ThingSpeak
String temp11 ="0"; //var for temp to the ThingSpeak
String temp12 ="0"; //var for temp to the ThingSpeak
String temp13 ="0"; //var for temp to the ThingSpeak
String temp14 ="0"; //var for temp to the ThingSpeak
String temp15 ="0"; //var for temp to the ThingSpeak

#define REPEAT_INTERVAL 240
/////const int GPIO_BattTester_enable = 0;

const char *ssid = "hggfg";   // cannot be longer than 32 characters!
const char *pass = "fgh";   //
const char *host = "hhhhh";

// Update these with values suitable for your network.
///IPAddress server(198, 41, 30, 241);
//IPAddress server(192, 168, 137, 1);
IPAddress MQTTserver(85, 119, 83, 194);
///void callback(const MQTT::Publish& pub) {
  // handle message arrived
///}

/////////////////////////////////////////////////////////////
//Add your topics to publish to here
char topicTemperature[] = "             ";

String topicName1="XXXYYYXXXYY01";
String topicName2="XXXYYYXXXYY02";
String topicName3="XXXYYYXXXYY03";
String topicName4="XXXYYYXXXYY04";
String topicName5="XXXYYYXXXYY05";
String topicName6="XXXYYYXXXYY06";
String topicName7="XXXYYYXXXYY07";
String topicName8="XXXYYYXXXYY08";
String topicName9="XXXYYYXXXYY09";
String topicName10="XXXYYYXXXYY10";
String topicName11="XXXYYYXXXYY11";
String topicName12="XXXYYYXXXYY12";
String topicName13="XXXYYYXXXYY13";
String topicName14="XXXYYYXXXYY14";
String topicName15="XXXYYYXXXYY15";

char topic1[] = "XXXYYYXXXYY01";
char topic2[] = "XXXYYYXXXYY02";
char topic3[] = "XXXYYYXXXYY03";
char topic4[] = "XXXYYYXXXYY04";
char topic5[] = "XXXYYYXXXYY05";
char topic6[] = "XXXYYYXXXYY06";
char topic7[] = "XXXYYYXXXYY07";
char topic8[] = "XXXYYYXXXYY08";
char topic9[] = "XXXYYYXXXYY09";
char topic10[] = "XXXYYYXXXYY10";
char topic11[] = "XXXYYYXXXYY11";
char topic12[] = "XXXYYYXXXYY12";
char topic13[] = "XXXYYYXXXYY13";
char topic14[] = "XXXYYYXXXYY14";
char topic15[] = "XXXYYYXXXYY15";

//Topic handler

//char topicRcv[] = "/0000";

//Payload handler
//char payloadRcv[5];

//Change the clientname to your liking
String clientName = "Node1";
unsigned long PreviousMillis = 0;
unsigned long PreviousMillis_reset = 0;
int mqt=0;
int fff=0;
int hall_sens=0;
int wifiConnectCounter, loopCounter, httpConnectCounter = 0;
///////////////////////////////////////////////////////////

WiFiClient wclient;
PubSubClient MQTTclient(wclient, MQTTserver);
MDNSResponder mdns;
ESP8266WebServer server(808);
File fsUploadFile;

void setup()
{
// espconn_tcp_set_max_con(7);
  Serial.begin(230400);
  Serial.setDebugOutput(true);
 // delay(10);
  Serial.println();
  ds.reset();
  pinMode(4, INPUT);
  pinMode(12,OUTPUT);
  analogWrite(12,0);
  analogWriteRange(100);
  analogWriteFreq(2000);
  Wire.begin(2,13);
  Rtc.Begin();
  lightMeter.begin();
  attachInterrupt(4,hall_sensor,RISING);
/////////////////////////////////////////////////
SPIFFS.begin();

  ///DBG_OUTPUT_PORT.printf("FS Pages: allocated: %d, deleted: %d, size: %s\n", FS.allocatedPages(), FS.deletedPages(), formatBytes(FS.pageSize()));
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      DBG_OUTPUT_PORT.printf("FS File: %s, type: %s, size: %s\n", fileName.c_str(), "file", formatBytes(fileSize).c_str());
    }
    DBG_OUTPUT_PORT.printf("\n");
  }
/////////////////////////////////////////

WifiConnect();
//WiFi.mode(WIFI_STA);
//WiFi.begin(ssid, pass);
/*
         /// WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
         /// WiFi.softAP("ESP_DENNIS", "zyxel2011");


           //    WiFi.config(ip, gateway, subnet);
              // delay(1000);
         int retries = 0;
              while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
                     retries++;
                     delay(500);
                    Serial.print(".");
                     if (WiFi.status() == WL_CONNECTED) {
                        Serial.println("");
                        Serial.println("WiFi connected");
                             }
            }
*/
//  mDNS INIT
  if (MDNS.begin(host, WiFi.localIP()))
    DBG_OUTPUT_PORT.printf("mDNS responder started for %s.local\n", host);

  //SERVER INIT
  //list directory
  server.on("/list", HTTP_GET, handleFileList);
  //load editor
  server.on("/edit", HTTP_GET, [](){
    if(!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
  });
  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);
  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  //called after file upload
  server.on("/edit", HTTP_POST, [](){ server.send(200, "text/plain", ""); });
  //called when a file is received inside POST data
  server.onFileUpload(handleFileUpdate);

  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, [](){
    String json = "{";
    json += "\"heap\":"+String(ESP.getFreeHeap());
    json += ", \"analog\":"+String(analogRead(A0));
    //json += ", \"analog2\":"+String(analogRead(A1));
    json += ", \"gpio\":"+String((uint32_t)(((GPI | GPO) & 0xFFFF) | ((GP16I & 0x01) << 16)));
    json += "}";
    server.send(200, "text/json", json);
    json = String();
  });
  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");
temperature();
}




//}
 void loop()
{

server.handleClient();
///////////////////////////////////Blynk.run();
//BlnkCC();
///ligth();


  // if (client.connect("arduinoClient")) client.publish("outTopic","hello world");
IPAddress ip(192,168,0,100);
               IPAddress gateway(192,168,0,1);
               IPAddress subnet(255,255,255,0);
 //////////////////////////////////////////

/////////////webServer.handleClient();
///////////////////////////////////
  unsigned long CurrentMillis=millis();
//}
 //    client.loop();//This keeps the connection to the broker alive

    //Get and publish the DS18b20 temp every 95 seconds
       if(CurrentMillis-PreviousMillis>95000)
            {
              PreviousMillis=CurrentMillis;
                //delay(1000);
          // WiFi.mode(
                //        int memory=ESP.getFreeHeap();
          //              temp08=(char*)memory.c_str();
                        Serial.print("FreeMemory=");
                        Serial.println(ESP.getFreeHeap());
        
                  ////////////////////////////////////////////////
                        MQTTclient.connect(MQTT::Connect("Kotelnaya")
                         .set_clean_session()
                         // .set_keepalive(0)
                         );
                        MQTTclient.subscribe("inTopic");
                     //  TempCounter=TempCounter+1;
                   ///   Blynk.disconnect();
             //////////////////////////////////////////////////////////////////
	                     temperature();
             
                   MQTTsend();
                 //  Blynk.disconnect();
                   ThingSpeak1();
                   ThingSpeak2();
                        //TempCounter=TempCounter+1;
                      //  BlnkCC();
                   ///////////   Blynk.connect();
                        Serial.println("");
                        Serial.println(millis());
						Serial.println(PreviousMillis);
					///	Serial.print("Difference between CurrentMillis-PreviousMillis=");
					////	Serial.println(CurrentMillis-PreviousMillis);
                        Serial.println("");
                    /// mail();
                   //MQTTclient.disconnect();
             }
             //  else
			//   {
			   /* Open, if need disconnect from WiFi
          *
			   if (WiFi.status() == WL_CONNECTED)
			   {
			   WiFi.disconnect();
			//   WiFi.mode(WIFI_OFF);
			   delay(100);
			   Serial.println("WiFi Disconnect");
			   }
         */
         ///////////////////////////////////////////
			  // Serial.println("WiFi Disconnect");
			//   }
                MQTTclient.disconnect();
			   }

////void BlnkCC()

//}
//BLYNK_READ(V0);
 // analogWrite(12, PWM);
  //Blynk.virtualWrite(
  //BLYNK_READ(1);
 // Blynk.virtualWrite(1, temp01);
  //BLYNK_READ(2);
 // Blynk.virtualWrite(2, temp02);
  //BLYNK_READ(3);
 // Blynk.virtualWrite(3, temp03);

//}



BLYNK_WRITE(1)
{
  analogWrite(12, param.asInt());
  PWM=param.asInt();
  Serial.print("PWM Range=");
  Serial.println(PWM);
}
BLYNK_WRITE(3)
{
  PWM=param.asInt();
  Serial.print("Switch Ligth=");
  Serial.println(PWM);
  if (PWM==0){analogWrite(12,0); Blynk.virtualWrite(1, 0);}
//  {on_del();
    //analogWrite(12,0); Blynk.virtualWrite(1, 0);
//  }
  else {PWM==1;analogWrite(12,100); Blynk.virtualWrite(1, 100);}

}

///BLYNK_READ(1)
///{
  // Usually, you will need to respond with a virtual pin value.
///  Blynk.virtualWrite(1, PWM);
///}
/*
BLYNK_READ(4)
{
  // Usually, you will need to respond with a virtual pin value.
  Blynk.virtualWrite(4, VirtTemp1);
}
BLYNK_READ(6)
{
  // Usually, you will need to respond with a virtual pin value.
 Blynk.virtualWrite(6, VirtTemp2);
}
*/
/*
void on_del()
{
unsigned long CurrentMillis=millis();
 if(CurrentMillis-PreviousMillis>2000)
            {
              PreviousMillis=CurrentMillis;
                //delay(1000);

            }

}
*/

