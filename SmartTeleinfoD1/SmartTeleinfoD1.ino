#include <SoftwareSerial.h>
#include <LibTeleinfo.h>

SoftwareSerial SerialTInfo(3,4); // Teleinfo Serial
TInfo          tinfo; // Teleinfo object

void printUptime(void)
{
  Serial.print(millis()/1000);
  Serial.print(F("s\t"));
}

void DataCallback(ValueList * me, uint8_t  flags)
{
  // Show our not accurate second counter
  //printUptime();

  if (flags & TINFO_FLAGS_ADDED) 
    Serial.print(F("NEW -> "));

  if (flags & TINFO_FLAGS_UPDATED)
    Serial.print(F("MAJ -> "));

  // Display values
  Serial.print(me->name);
  Serial.print("=");
  Serial.println(me->value);
}

void setup()
{
  // Serial, pour le debug
  Serial.begin(115200);

  Serial.println(F("========================================"));
  Serial.println(F(__FILE__));
  Serial.println(F(__DATE__ " " __TIME__));
  Serial.println();

  // Configure Teleinfo Soft serial 
  // La téléinfo est connectee sur D3
  // ceci permet d'eviter les conflits avec la 
  // vraie serial lors des uploads
  SerialTInfo.begin(1200);

  // Init teleinfo
  tinfo.init();

  // Attacher les callback dont nous avons besoin
  // pour cette demo, ici attach data
  tinfo.attachData(DataCallback);

  printUptime();
  Serial.println(F("Teleinfo started"));
}

void loop()
{
  // Teleinformation processing
  if ( SerialTInfo.available() ) {
    tinfo.process(SerialTInfo.read());
  }
}
