/*******************************************************************
 *  this is a basic example how to program a Telegram Bot          *
 *  using TelegramBOT library on Arduino Zero and WiFiSchield101   *
 *                                                                 *
 *  Open a conversation with the bot, it will echo your messages   *
 *                                                                 *
 *  written by Giacarlo Bacchio                                    *
 *******************************************************************/

//#include <TelegramBot.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <TelegramBot.h>


// Initialize Wifi connection to the router
const char *ssid = "xxx";   // cannot be longer than 32 characters!
const char *pass = "yyy";   //                              // your network key
int status = WL_IDLE_STATUS;


// Initialize Telegram BOT
#define BOTtoken "56u56qdKcXPyzbp6Tbj98MF7o"  //token of TestBOT
#define BOTname "S56u56rt"
#define BOTusername "S56u56ueBot"
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done



void setup() {

  Serial.begin(115200);
    // check for the presence of the shield:
  WiFi.begin(ssid, pass);
 /// }
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  bot.begin();      // launch Bot functionalities
}



void loop() {

  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    ///Bot_EchoMessages();   // reply to message with Echo
    Bot_lasttime = millis();
  }
}


/********************************************
 * EchoMessages - function to Echo messages *
 ********************************************/
/*
void Bot_EchoMessages() {

  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    bot.sendMessage(bot.message[i][4], bot.message[i][5], "");
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}*/






