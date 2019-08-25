char* gSsid = NULL;
char* gPwd = NULL;
char str_mac[18] = {0};

void wifi_setup(bool list_network, char* ssid, char* pwd)
{
  Serial.println(F("Initializing Wifi..."));
  printMacAddress();

  if ( list_network )
  {
      Serial.println(F("Scanning available networks..."));
      listNetworks();
  }

  gSsid = ssid;
  gPwd = pwd;

  if ( NULL == gSsid ||
       NULL == gPwd )
  {
    Serial.println(F("Cannot get SSID or PWD! Rebooting ..."));
    delay(5000);
    ESP.restart();
  }
    
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(gSsid);

  wifi_set_phy_mode(PHY_MODE_11G);
  system_phy_set_max_tpw(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(gSsid, gPwd);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println(F("Connection Failed! Rebooting..."));
    delay(5000);
    ESP.restart();
  }

  Serial.println(F("WiFi Connected !"));
  printWiFiStatusInfo();
}

void wifi_check()
{
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println(F("Connection Failed! Rebooting..."));
    ESP.restart();
  }
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println(F("** Scan Networks **"));
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print(F("number of available networks:"));
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(F(") "));
    Serial.print(WiFi.SSID(thisNet));
    Serial.print(F("\tSignal: "));
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(F(" dBm"));
    Serial.print(F("\tEncryption: "));
    Serial.println(WiFi.encryptionType(thisNet));
  }
}

void printWiFiStatusInfo()
{
    Serial.print(F("SSID: "));
    Serial.println(WiFi.SSID());
    
    byte* bssid;
    bssid = WiFi.BSSID();    
    Serial.print(F("BSSID: "));
    Serial.print(bssid[5],HEX);
    Serial.print(F(":"));
    Serial.print(bssid[4],HEX);
    Serial.print(F(":"));
    Serial.print(bssid[3],HEX);
    Serial.print(F(":"));
    Serial.print(bssid[2],HEX);
    Serial.print(F(":"));
    Serial.print(bssid[1],HEX);
    Serial.print(F(":"));
    Serial.println(bssid[0],HEX);    
    Serial.print(F("RSSI: "));
    Serial.println(WiFi.RSSI());

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());  
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];    

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print(F("MAC: "));
  sprintf(str_mac,"%02X:%02X:%02X:%02X:%02X:%02X",mac[5],mac[4],mac[3],mac[2],mac[1],mac[0]);
  Serial.println(str_mac);
}

char* getStrMac()
{
  return str_mac;
}
