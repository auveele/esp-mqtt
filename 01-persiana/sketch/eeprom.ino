

void setup_eeprom()
{
  EEPROM.begin(512);
  read_blocked();
}

void read_blocked(){
  mqtt_only = (boolean)EEPROM.read(0);
  #ifdef DEBUG
  Serial.print("Variable del blockeo leída desde eeprom: ");
  Serial.println(mqtt_only);
  #endif
}

void write_blocked(){
  EEPROM.write(0, (byte)mqtt_only);
  EEPROM.commit();
  #ifdef DEBUG
  Serial.print("Variable del blockeo guardada en eeprom: ");
  Serial.println(mqtt_only);
  #endif
}

