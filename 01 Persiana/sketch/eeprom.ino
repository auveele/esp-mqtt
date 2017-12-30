
/*########################
##########################
 
  eeprom.ino

  Este archivo contiene ...

##########################
########################*/

// ############
// SETUP EEPROM
// ############
void setup_eeprom() {
  EEPROM.begin(512);
  read_restart();
  read_blocked();
}

// #############
// BLOCKED VALUE
// #############
void read_blocked() {
  mqtt_only = (boolean)EEPROM.read(0);
  DEBUG_PRINT("Variable del blockeo leída desde eeprom: ");
  DEBUG_PRINTLN(mqtt_only);
}

void write_blocked() {
  EEPROM.write(0, (byte)mqtt_only);
  EEPROM.commit();
  DEBUG_PRINT("Variable del blockeo guardada en eeprom: ");
  DEBUG_PRINTLN(mqtt_only);
}

