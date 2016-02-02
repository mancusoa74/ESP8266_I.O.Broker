/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

RCSwitch mySwitch = RCSwitch();
ESP8266WiFiMulti wifiMulti;
int wifi_counter;
void setup() {
   Serial.begin(115200);
  wifiMulti.addAP("RT50", "zyxel2011");   //write here your ssid and password
    wifiMulti.addAP("PALATA", "PALATA2012");
 // wifiMulti.addAP("PALATA3", "PALATA2015");
 //   wifiMulti.addAP("Smart", "zyxel2011");
    Serial.println("Connecting Wifi");
  //////////////////////////////////////////

    wifi_counter=0;
    while (wifi_counter<40 && wifiMulti.run()!= WL_CONNECTED) {
        Serial.print(".");
        delay(300);
        wifi_counter++;
    }
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

  mySwitch.enableReceive(4);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

  mySwitch.resetAvailable();
  }
}
