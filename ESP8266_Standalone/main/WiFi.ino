
//WiFi.mode(WIFI_STA);
void WifiConnect()
{
///system_phy_set_rfoption(1);
  ///  system_phy_set_max_tpw(82);
  
   
   //WIFI INIT
  DBG_OUTPUT_PORT.printf("Connecting to %s\n", ssid);
 /// if (String(WiFi.SSID()) != String(ssid)) {
    WiFi.begin(ssid, pass);
 /// }
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  DBG_OUTPUT_PORT.print("Connected! IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());
   /*
    WiFi.begin(ssid, pass);
///
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
}

