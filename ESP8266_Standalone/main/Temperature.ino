void hall_sensor()
{
hall_sens=digitalRead(4);
Serial.println(hall_sens);
}

void temperature()
{
  byte array;
  byte topicname=0;
  int circle=1;
  int CircleTemp=1;
  ////////////////////////////
  for ( circle = 1; circle <16; circle++) {           // we need 9 bytes
   // data[i] = ds.read();
 //  }
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
      temp=1;
   	  break;
    case 2:
      for (array=0; array<=7; array++) {sensor[array]=sensor2[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic2[topicname];};
      temp=2;
      break;
    case 3:
      for (array=0; array<=7; array++) {sensor[array]=sensor3[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic3[topicname];};
      temp=3;
      break;
    case 4:
      for (array=0; array<=7; array++) {sensor[array]=sensor4[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic4[topicname];};
      temp=4;
      break;
    case 5:
      for (array=0; array<=7; array++) {sensor[array]=sensor5[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic5[topicname];};
      temp=5;
      break;
    case 6:
      for (array=0; array<=7; array++) {sensor[array]=sensor6[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic6[topicname];};
      temp=6;
      break;
    case 7:
      for (array=0; array<=7; array++) {sensor[array]=sensor7[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic7[topicname];};
      temp=7;
      break;
     case 8:
      for (array=0; array<=7; array++) {sensor[array]=sensor8[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic8[topicname];};
      temp=8;
      break;
     case 9:
      for (array=0; array<=7; array++) {sensor[array]=sensor9[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic9[topicname];};
      temp=9;
      break;
     case 10:
      for (array=0; array<=7; array++) {sensor[array]=sensor10[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic10[topicname];};
      temp=10;
      break;
     case 11:
      for (array=0; array<=7; array++) {sensor[array]=sensor11[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic11[topicname];};
      temp=11;
      break;
     case 12:
      for (array=0; array<=7; array++) {sensor[array]=sensor12[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic12[topicname];};
      temp=12;
      break;
     case 13:
      for (array=0; array<=7; array++) {sensor[array]=sensor13[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic13[topicname];};
      temp=13;
      break;
     case 14:
      for (array=0; array<=7; array++) {sensor[array]=sensor14[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic14[topicname];};
      temp=14;
      break;
     case 15:
      for (array=0; array<=7; array++) {sensor[array]=sensor15[array];};
      for (topicname=0; topicname<=12; topicname++) {topicTemperature[topicname]=topic15[topicname];};
      //circle=0;
      temp=15;
      break;
  }
  ds.select(sensor);
  delay(10);
  /*
  for ( CircleTemp = 1; CircleTemp <680000; CircleTemp++) {           // we need 9 bytes
  // delay(1);
   }
   */
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
 /* for ( CircleTemp = 1; CircleTemp <680000; CircleTemp++) {           // we need 9 bytes
  // delay(1);
   }

  */

//  delay(680);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
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
for(int i=0;i<4;i++)
     {
        payload+=charVal[i];
     }
      charVal[4]='\0';
   //   if (client.connect("Kotelnaya")){
    // delay(300);
  //// if (TempCounter>0)
  //  Blynk.disconnect();// Disconnect from Blynk server
   ///// {
     /*  MQTTclient.connect(MQTT::Connect("Kotelnaya")
                .set_clean_session()
               // .set_keepalive(20)
                ); */
    ///  MQTTclient.publish(topicTemperature, (char*) payload.c_str());
    ///  delay(50);
      //MQTTclient.disconnect();
   // }
///////////////////////////////////////////////////////////////////////////////

//int circle2=1;

switch (temp){
    case 1:
      temp01=(char*) payload.c_str();
     
   ////   topicName1=topicTemperature;
    //  Serial.println (topicName1);
      //Blynk.virtualWrite(10, VirtTemp1);
      break;
    case 2:
      temp02=(char*) payload.c_str();
  
   ////   topicName2=topicTemperature;
    ///  Serial.println (topicName2);
      //Serial.println (VirtTemp2);
      break;
    case 3:
      temp03=(char*) payload.c_str();
////      topicName3=topicTemperature;
   ///  Serial.println (topicName3);
      break;
    case 4:
      temp04=(char*) payload.c_str();
   /////   topicName4=topicTemperature;
   ///   Serial.println (topicName4);
      break;
    case 5:
      temp05=(char*) payload.c_str();
  /////    topicName5=topicTemperature;
       break;
    case 6:
      temp06=(char*) payload.c_str();
  /////    topicName6=topicTemperature;
      break;
    case 7:
      temp07=(char*) payload.c_str();
  ////    topicName7=topicTemperature;
      break;
     case 8:
      temp08=(char*) payload.c_str();
   /////   topicName8=topicTemperature;
      break;
     case 9:
      temp09=(char*) payload.c_str();
   /////   topicName9=topicTemperature;
      break;
     case 10:
      temp10=(char*) payload.c_str();
   /////   topicName10=topicTemperature;
      break;
     case 11:
      temp11=(char*) payload.c_str();
   /////   topicName11=topicTemperature;
      break;
     case 12:
      temp12=(char*) payload.c_str();
   ////   topicName12=topicTemperature;
      break;
     case 13:
      temp13=(char*) payload.c_str();
   ////   topicName13=topicTemperature;
      break;
     case 14:
      temp14=(char*) payload.c_str();
   /////   topicName14=topicTemperature;
      break;
     case 15:
      temp15=(char*) payload.c_str();
   ////   topicName15=topicTemperature;
      break;
  }
   ///// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//      .set_keepalive(30);
   //   }
if (TempCounter>1){Serial.print(topicTemperature); Serial.print("  ");Serial.println(celsius,1);}
/////Serial.println(topicTemperature);
//temp=String(celsius);
//temp=celsius;
//ThingSpeak1();
}
TempCounter=TempCounter+1;
//Blynk.connect();
 }
