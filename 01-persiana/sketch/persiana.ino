
int up_state = 0;
int down_state = 0;
// Saber de dónde viene la orden: LOW = botón, HIGH = mqtt
int mqtt_control = LOW;


// ==========
// SUBIMOS PERSIANA
// ==========
void up() {
  digitalWrite(DOWN_PIN, LOW);
  delay(SECURITY_DELAY);
  digitalWrite(UP_PIN, HIGH);
  delay(SECURITY_DELAY);
  // mqtt_client.publish("/DOMUS/OFFICE/PERSIANA", "UP", true);

  #ifdef DEBUG
    Serial.println("ENTRA EN UP");
  #endif
  
}

// ==========
// BAJAMOS PERSIANA
// ==========
void down() {
  digitalWrite(UP_PIN, LOW);
  delay(SECURITY_DELAY);
  digitalWrite(DOWN_PIN, HIGH);
  delay(SECURITY_DELAY);
  // mqtt_client.publish("/DOMUS/OFFICE/PERSIANA", "DOWN", true);

  #ifdef DEBUG
    Serial.println("ENTRA EN DOWN");
  #endif
}

// ==========
// PARAMOS PERSIANA
// ==========
void stop_all() {
  // mqtt_client.publish("/DOMUS/OFFICE/PERSIANA", "STOP", true);
  digitalWrite(UP_PIN, LOW);
  digitalWrite(DOWN_PIN, LOW);
}



// ==========
// RECIBIMOS "SUBIR" por MQTT
// ==========
void up_mqtt() {
  mqtt_control = HIGH;
  up_state = LOW;
  down_state = HIGH;
}

// ==========
// RECIBIMOS "BAJAR" por MQTT
// ==========
void down_mqtt() {
  mqtt_control = HIGH;
  up_state = HIGH;
  down_state = LOW;
}

// ==========
// RECIBIMOS "STOP" por MQTT
// ==========
void stop_mqtt() {
  stop_all();
  mqtt_control = LOW;
}


// ==========
// LOOP PERSIANA
// ==========
void loop_persiana() {
  // Si mandan los botones, pillo valor botones.
  if (mqtt_control == LOW) {
    up_state = digitalRead(UP_BUTTON);
    down_state = digitalRead(DOWN_BUTTON);
  } else {
    // En cambio, si manda mqtt,
    // pero algún botón está pulsado:
    // Manda botón de nuevo.
    if ((digitalRead(UP_BUTTON) != HIGH) or (digitalRead(DOWN_BUTTON) != HIGH)){
      mqtt_control = LOW;
    }
  }

  // Si el botón UP se pulsa
  if (up_state != HIGH) {
    up();
  // Si el botón DOWN se pulsa
  } else if (down_state != HIGH){
    down();
  // Sino hay nada pulsado y mandan botones.
  } else {
    if (mqtt_control == LOW) {
      stop_all();
    }
  }
  delay(INTERVAL_DELAY);
}
