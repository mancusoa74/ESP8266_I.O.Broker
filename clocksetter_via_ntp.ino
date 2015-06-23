#include <Time.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "DELTAWLAN";  //  your network SSID (name)
char pass[] = "lukop";       // your network password


unsigned int localPort = 2390;      // local port to listen for UDP packets

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup()
{
  Serial.begin(2400);
  delay(5000);
}

void loop()
{
  if(WiFi.status() != WL_CONNECTED)
     WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  udp.begin(localPort);
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  
  int cb = udp.parsePacket();
  if (cb) {
 //   Serial.print("packet received, length=");
 //   Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    bool dst = isDST(epoch);
    unsigned int y = year(epoch);
    unsigned int m = month(epoch);
    unsigned int d = day(epoch);
    unsigned int h = hour(epoch);
    if(dst)
      h += 2;
    else
      h += 1;
    if(h>23)
        h -=24;
    unsigned int min = minute(epoch);
    unsigned int s = second(epoch);
    Serial.print("{\"year\":");
    Serial.print(y);
    Serial.print(",\"month\":");
    Serial.print(m);
    Serial.print(",\"day\":");
    Serial.print(d);
    Serial.print(",\"hour\":");
    Serial.print(h);
    Serial.print(",\"minute\":");
    Serial.print(min);
    Serial.print(",\"seconds\":");
    Serial.print(s);
    Serial.println("}");
  }
  // wait ten seconds before asking for the time again
  delay(3600000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
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

bool isDST(unsigned long epoch) 
{
   unsigned int m = month(epoch);
   unsigned int d = day(epoch);
   unsigned int wd = weekday(epoch);
   unsigned int h = hour(epoch);
   unsigned int min = minute(epoch);
   unsigned int s = second(epoch);

	// work out if we should apply dst, modify according to your local rules
   if (m < 2 ||m > 9) {
      // these months are completely out of DST
   } 
   else if (m > 2 && m < 9) {
      // these months are completely in DST
      return true;
   } 
   else {
      // else we must be in one of the change months
      // work out when the last sunday was (could be today)
      int previousSunday = d - wd;
      if (m == 2) { // march
      // was last sunday (which could be today) the last sunday in march
         if (previousSunday >= 25) {
         // are we actually on the last sunday today
            if (wd == 0) {
               // if so are we at/past 2am gmt
               int s = (h * 3600) + (min * 60) + s;
               if (s >= 7200) return true;
            }
            else {
               return true;
            }
         }
      } else if (m == 9) {
         // was last sunday (which could be today) the last sunday in october
         if (previousSunday >= 25) {
            // we have reached/passed it, so is it today?
            if (wd == 0) {
               // change day, so are we before 1am gmt (2am localtime)
               int s = (h * 3600) + (min * 60) + s;
               if (s < 3600) return true;
            }
         } 
         else {
            // not reached the last sunday yet
            return true;
         }
      }
   }
   return false;
}
