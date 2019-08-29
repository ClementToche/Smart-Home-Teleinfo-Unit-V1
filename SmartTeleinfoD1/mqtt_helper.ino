char *gMqtt_user;
char *gMqtt_pwd;
char *gMqtt_server;
char *gMqtt_name;
int gMqtt_port;
char topic[100] = {0};

WiFiClientSecure espClient;
PubSubClient mqtt_client(espClient);

void mqtt_setup(char *user, char *pwd, char *server, int port, char *name)
{
    if (!user || !pwd || !server || 0 == port || !name)
    {
        Serial.println(F("Cannot get MQTT connection info! Rebooting ..."));
        delay(5000);
        ESP.restart();
    }

    gMqtt_user = user;
    gMqtt_pwd = pwd;
    gMqtt_server = server;
    gMqtt_port = port;
    gMqtt_name = name;

    espClient.setInsecure();
    mqtt_client.setServer(gMqtt_server, gMqtt_port);
    mqtt_connect();
}

void mqtt_connect()
{
    while (!mqtt_client.connected())
    {
        Serial.print(F("Attempting MQTT connection..."));
        if (mqtt_client.connect(getStrMac(), gMqtt_user, gMqtt_pwd))
        {
            Serial.println(F("connected"));
        }
        else
        {
            Serial.print(F("failed, rc="));
            Serial.print(mqtt_client.state());
            Serial.println(F(" try again in 5 seconds"));
            delay(5000);
        }
    }
}

void mqtt_report_touch_level(int touch)
{
    sprintf(topic, "/audoche/home/smartmodule/%s/status/touch", gMqtt_name);
    char value[5] = {0};
    sprintf(value, "%i", touch);
    mqtt_client.publish(topic, value);
}

void mqtt_report_battery(int batt_level)
{
    sprintf(topic, "/audoche/home/smartmodule/%s/status/battery", gMqtt_name);
    char value[5] = {0};
    sprintf(value, "%i", batt_level);
    mqtt_client.publish(topic, value);
}

void mqtt_send_rotary_status(int id, rotaryMovement mvt)
{
    switch (mvt)
    {
    case ROTARY_UP:
        sprintf(topic, "/audoche/home/smartmodule/%s/actuator/rotary%i", gMqtt_name, id);
        mqtt_client.publish(topic, "up");
        break;
    case ROTARY_DOWN:
        sprintf(topic, "/audoche/home/smartmodule/%s/actuator/rotary%i", gMqtt_name, id);
        mqtt_client.publish(topic, "down");
    }
}

void mqtt_send_switch_status(int id)
{
    sprintf(topic, "/audoche/home/smartmodule/%s/actuator/switch%i", gMqtt_name, id);
    mqtt_client.publish(topic, "pressed");
}

void mqtt_send_tinfo_status(tinfoType type, int value)
{
    switch (type)
    {
    case TINFO_HP:
        sprintf(topic, "/audoche/home/smartmodule/%s/hp", gMqtt_name);
        mqtt_client.publish(topic, String(value).c_str());
        break;
    case TINFO_HC:
        sprintf(topic, "/audoche/home/smartmodule/%s/hc", gMqtt_name);
        mqtt_client.publish(topic, String(value).c_str());
        break;
    case TINFO_PAPP:
        sprintf(topic, "/audoche/home/smartmodule/%s/papp", gMqtt_name);
        mqtt_client.publish(topic, String(value).c_str());
        break;
    case TINFO_IINST:
        sprintf(topic, "/audoche/home/smartmodule/%s/iinst", gMqtt_name);
        mqtt_client.publish(topic, String(value).c_str());
        break;
    }
}

void mqtt_send_detect_status()
{
    sprintf(topic, "/audoche/home/smartmodule/%s/detector/pir", gMqtt_name);
    mqtt_client.publish(topic, "movement");
}

void mqtt_loop()
{
    mqtt_client.loop();

    if (!mqtt_client.connected())
    {
        pin_led(true);
        mqtt_connect();
        pin_led(false);
    }
}