
void spiffs_setup()
{
  SPIFFS.begin();
}

void spiffs_list_files()
{
  Dir dir = SPIFFS.openDir("");
  while (dir.next())
  {
    Serial.print(F("File "));
    Serial.print(dir.fileName());
    Serial.print(F(" | Size "));
    File f = dir.openFile("r");
    Serial.println(f.size());
  }
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_spiffs_param(const char* type)
{
  File f = SPIFFS.open(type, "r");
  if (!f)
  {
    Serial.print(type);
    Serial.println(" file open failed");
    return NULL;
  }

  String data = f.readString();
  Serial.print(type);
  Serial.print(" : ");
  Serial.println(data);

  int size = data.length() + 1;
  if ( 1 > size )
  {
    Serial.print(type);
    Serial.println(" name is zero size");
    return NULL;
  }
  
  char* ret_value = (char*) calloc(1, size);
  data.toCharArray( ret_value, size );

  return ret_value;
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_wifi_ssid()
{
  return spiffs_get_spiffs_param("/wifi_ssid.txt");
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_wifi_pwd()
{
  return spiffs_get_spiffs_param("/wifi_pwd.txt");
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_mqtt_user()
{
  return spiffs_get_spiffs_param("/mqtt_user.txt");
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_mqtt_pwd()
{
  return spiffs_get_spiffs_param("/mqtt_pwd.txt");
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_mqtt_server()
{
  return spiffs_get_spiffs_param("/mqtt_server.txt");
}

int spiffs_get_mqtt_port()
{
  char* number = spiffs_get_spiffs_param("/mqtt_port.txt");
  int port = (int)strtol(number, NULL, 10);
  free(number);
  return port;
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_board_name()
{
  return spiffs_get_spiffs_param("/mqtt_name.txt");
}

/*
 * Be sure to free-up the memory of the param when not needed anymore
 */
char* spiffs_get_ota_pwd()
{
  return spiffs_get_spiffs_param("/ota_pwd.txt");
}