void ThingSpeak1()
{
 ///Blynk.disconnect();// Disconnect from Blynk server
 httpConnectCounter++;
  WiFiClient thingspeakclient;
  const int httpPort = 80;

 if (!thingspeakclient.connect(hostThingSpeak, httpPort)) {
    Serial.println("http connection failed, will retry");
    if (httpConnectCounter < 20) {
      delay(20);
      return; // retry connection
    }
 }

  String url = "/update";
  url += "?key=";
  url += writeKey1;
  url += "&field1=";
  url += temp01;
  url += "&field2=";
  url += temp02;
  url += "&field3=";
  url += temp03;
  url += "&field4=";
  url += temp04;
  url += "&field5=";
  url += temp05;
  url += "&field6=";
  url += temp06;
  url += "&field7=";
  url += temp07;
  url += "&field8=";
  url += temp08;
 Serial.println("Requesting URL: ");
 Serial.println(url);
//WiFiClient thingspeakclient;
  // This will send the request to the server
 if (TempCounter>1)
  {
  thingspeakclient.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + hostThingSpeak + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(50);
  }
/*
  // Read all the lines of the reply from server and print them to Serial
  if (thingspeakclient.available()) {
    // print first line
    String line = thingspeakclient.readStringUntil('\r');
    Serial.println(line);
  }
  while (thingspeakclient.available()) {
   String line = thingspeakclient.readStringUntil('\r');
    Serial.println(line);
  }
*/
///Blynk.connect();
}

void ThingSpeak2()
{
 ///Blynk.disconnect();// Disconnect from Blynk server
 httpConnectCounter++;
  WiFiClient thingspeakclient;
  const int httpPort = 80;

 if (!thingspeakclient.connect(hostThingSpeak, httpPort)) {
    Serial.print("http connection failed, will retry");
    if (httpConnectCounter < 20) {
     // delay(20);
      return; // retry connection
    }
 }

  String url = "/update";
  url += "?key=";
  url += writeKey2;
  url += "&field1=";
  url += temp09;
  url += "&field2=";
  url += temp10;
  url += "&field3=";
  url += temp11;
  url += "&field4=";
  url += temp12;
  url += "&field5=";
  url += temp13;
  url += "&field6=";
  url += temp14;
  url += "&field7=";
  url += temp15;
//  url += "&field8=";
//  url += memory;
 Serial.println("Requesting URL: ");
 Serial.println(url);
//WiFiClient thingspeakclient;
  // This will send the request to the server
  if (TempCounter>1)
  {
  thingspeakclient.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + hostThingSpeak + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(50);
  }
  // Read all the lines of the reply from server and print them to Serial


  ////if (thingspeakclient.available()) {
    // print first line
    ///  String line = thingspeakclient.readStringUntil('\r');
    ///Serial.println(line);
 //// }
 //// while (thingspeakclient.available()) {
  /// String line = thingspeakclient.readStringUntil('\r');
  /// Serial.println(line);
 //// }



///Blynk.connect();
}
