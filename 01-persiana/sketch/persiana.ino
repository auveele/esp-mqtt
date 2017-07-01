
int up_state = 0;
int down_state = 0;

int mqtt_control = 0;

void up() {
  digitalWrite(DOWN_PIN, LOW);
  delay(SECURITY_DELAY);
  digitalWrite(UP_PIN, HIGH);
  delay(SECURITY_DELAY);
  Serial.println("ENTRA EN UP");
}

void down() {
  digitalWrite(UP_PIN, LOW);
  delay(SECURITY_DELAY);
  digitalWrite(DOWN_PIN, HIGH);
  delay(SECURITY_DELAY);
  Serial.println("ENTRA EN DOWN");
}

void stop_all() {
  digitalWrite(UP_PIN, LOW);
  digitalWrite(DOWN_PIN, LOW);
}

void up_mqtt() {
  mqtt_control = HIGH;
  up_state = LOW;
  down_state = HIGH;
}

void down_mqtt() {
  mqtt_control = HIGH;
  up_state = HIGH;
  down_state = LOW;
}

void stop_mqtt() {
  stop_all();
  mqtt_control = LOW;
}

void loop_persiana() {
  if (mqtt_control != HIGH) {
    up_state = digitalRead(UP_BUTTON);
    down_state = digitalRead(DOWN_BUTTON);
  } else {
    if ((digitalRead(UP_BUTTON) == LOW) or (digitalRead(DOWN_BUTTON) == LOW)){
      mqtt_control = LOW;
    }
  }
  
  if (up_state != HIGH) {
    Serial.println("up");
    up();
  } else if (down_state != HIGH){
    down();
    Serial.println("down");
  } else {
    if (mqtt_control == LOW) {
      stop_all();
    }
  }
  delay(INTERVAL_DELAY);
}
