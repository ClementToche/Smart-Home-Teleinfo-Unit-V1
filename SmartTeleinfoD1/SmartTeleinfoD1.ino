#include <WiFiClientSecure.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <LibTeleinfo.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <FS.h>

#include "const.h"

void setup()
{
  pin_setup();

  Serial.begin(115200);
  while (!Serial)
    ;

  //  _________                      .__  __  .__       .__
  //  \_   ___ \  ____   ____   ____ |__|/  |_|__| ____ |__|____    ____
  //  /    \  \/ /  _ \ / ___\ /    \|  \   __\  |/ ___\|  \__  \  /    \ 
  //  \     \___(  <_> ) /_/  >   |  \  ||  | |  \  \___|  |/ __ \|   |  \
  //   \______  /\____/\___  /|___|  /__||__| |__|\___  >__(____  /___|  /
  //          \/      /_____/      \/                 \/        \/     \/

  Serial.println(F("********************************************************************"));
  Serial.println(F("_________                      .__  __  .__       .__               "));
  Serial.println(F("\\_   ___ \\  ____   ____   ____ |__|/  |_|__| ____ |__|____    ____  "));
  Serial.println(F("/    \\  \\/ /  _ \\ / ___\\ /    \\|  \\   __\\  |/ ___\\|  \\__  \\  /    \\ "));
  Serial.println(F("\\     \\___(  <_> ) /_/  >   |  \\  ||  | |  \\  \\___|  |/ __ \\|   |  \\"));
  Serial.println(F(" \\______  /\\____/\\___  /|___|  /__||__| |__|\\___  >__(____  /___|  /"));
  Serial.println(F("        \\/      /_____/      \\/                 \\/        \\/     \\/ "));
  Serial.println(F("********************************************************************"));
  Serial.println(F(__FILE__));
  Serial.println(F(__DATE__ " " __TIME__));
  Serial.print(F("Version "));
  Serial.println(version);
  Serial.println(F("********************************************************************"));

  spiffs_setup();

  spiffs_list_files();

  wifi_setup(false,
             spiffs_get_wifi_ssid(),
             spiffs_get_wifi_pwd(),
             spiffs_get_board_name());

  ota_setup(spiffs_get_board_name(),
            spiffs_get_ota_pwd());

  mqtt_setup(spiffs_get_mqtt_user(),
             spiffs_get_mqtt_pwd(),
             spiffs_get_mqtt_server(),
             spiffs_get_mqtt_port(),
             spiffs_get_board_name());

  teleinfo_setup();

  Serial.println(F("********** Started **********"));

  pin_led(false);
}

void loop()
{
  teleinfo_print_process();
  mqtt_client.loop();
  ArduinoOTA.handle();
}
