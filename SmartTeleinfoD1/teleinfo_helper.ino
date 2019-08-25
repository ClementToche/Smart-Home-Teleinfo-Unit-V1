SoftwareSerial STInfo(rxPin, txPin);
TInfo tinfo;

void teleinfo_label_callback(ValueList *me, uint8_t flags)
{
  if (flags & TINFO_FLAGS_ADDED)
    Serial.print(F("NEW -> "));

  if (flags & TINFO_FLAGS_UPDATED)
    Serial.print(F("MAJ -> "));

  // Display values
  Serial.print(me->name);
  Serial.print("=");
  Serial.println(me->value);

  pin_led(true);

  if (0 == strcmp(me->name, "HCHP"))
  {
    long int val = strtol(me->value, NULL, 10);
    mqtt_send_tinfo_status(TINFO_HP, val);
  }
  else if (0 == strcmp(me->name, "HCHC"))
  {
    long int val = strtol(me->value, NULL, 10);
    mqtt_send_tinfo_status(TINFO_HC, val);
  }
  else if (0 == strcmp(me->name, "PAPP"))
  {
    long int val = strtol(me->value, NULL, 10);
    mqtt_send_tinfo_status(TINFO_PAPP, val);
  }
  else if (0 == strcmp(me->name, "IINST"))
  {
    long int val = strtol(me->value, NULL, 10);
    mqtt_send_tinfo_status(TINFO_IINST, val);
  }
  else if (0 == strcmp(me->name, "OPTARIF"))
  {
    Serial.print("optarif reçu");
  }

  pin_led(false);
}

void teleinfo_setup()
{
  STInfo.begin(1200);
  tinfo.init();

  tinfo.attachData(teleinfo_label_callback);

  Serial.println(F("TeleInfo Setup done !"));
}

void teleinfo_print_process()
{
  if (STInfo.available())
    tinfo.process(STInfo.read());
}