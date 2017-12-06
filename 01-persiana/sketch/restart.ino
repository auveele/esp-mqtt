
/*########################
##########################
 
  restart.ino

  Este archivo contiene ...

##########################
########################*/

Ticker restartTimer;

// ##################
// SETUP NEXT RESTART
// ##################
void setup_restart(){
  restartTimer.once(RESTART_TIME, restart_system);
}

// ################
// RESTART FUNCTION
// ################
void restart_system(){
  DEBUG_PRINTLN("RESTART!");
  write_restart();
  ESP.restart();
}

// #################
// READ EEPROM VALUE
// #################
void read_restart(){
  conscient_restart = EEPROM.read(1);
  if (conscient_restart == 0) {
    DEBUG_PRINTLN("Reinicio inesperado.");

    for (int i = 0; i < bad_restart_delay; i++) {
      DEBUG_PRINT(".");
      delay(1000);
    }
    DEBUG_PRINTLN("");
  } else {
    // No lo cambiamos en la variable conscient_restart,
    // para poder enviar mensaje de RESET después
    EEPROM.write(1, 0);
    EEPROM.commit();
    DEBUG_PRINTLN("Reinicio consciente.");
  }
}

// ##################
// WRITE EEPROM VALUE
// ##################
void write_restart(){
  conscient_restart = 1;
  EEPROM.write(1, conscient_restart);
  EEPROM.commit();
  EEPROM.end();
  delay(500);
  DEBUG_PRINTLN("Variable del reseteo guardada en eeprom.");
}

// #################
// SEND MQTT MESSAGE
// #################
void send_reset_advice(){
  char topic[200];
  sprintf(topic,"%s%s",mqtt_base_topic.c_str(),"/PWR");
  if (conscient_restart == 1) {
    // MENSAJE DE REINICIO CONTROLADO 
    if (mqttClient.connected()) mqttClient.publish(topic, 2, true, "OK");
  } else {
    // MENSAJE DE REINICIO INESPERADO
    if (mqttClient.connected()) mqttClient.publish(topic, 2, true, "BAD");
  }
}
