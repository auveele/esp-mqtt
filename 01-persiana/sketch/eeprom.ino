

void setup_eeprom()
{
  EEPROM.begin(512);
  read_restart();
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

void read_restart(){
  conscient_restart = EEPROM.read(1);
  
  if (conscient_restart == 0) {
    #ifdef DEBUG
      Serial.print("Reinicio inesperado");
    #endif
    for (int i = 0; i < bad_restart_delay; i++){
      #ifdef DEBUG
      Serial.print(".");
      #endif
      delay(1000);
    }
    #ifdef DEBUG
    Serial.println("");
    #endif
  } else {
    // No lo cambiamos en la variable conscient_restart,
    // para poder enviar mensaje de RESET después
    EEPROM.write(1, 0);
    EEPROM.commit();
    EEPROM.end();
    #ifdef DEBUG
    Serial.println("Reinicio consciente");
    #endif
  }
  
}

void write_restart(){
  conscient_restart = 1;
  EEPROM.write(1, conscient_restart);
  EEPROM.commit();
  delay(500);
  #ifdef DEBUG
  Serial.println("Variable del reseteo guardada en eeprom");
  #endif
}

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
