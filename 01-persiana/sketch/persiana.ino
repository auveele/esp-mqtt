
// ==========
// persiana.ino
//
// Este archivo contiene aquello relacionado con
// la persiana: motor y conmutador de pared.
//
// Subir, bajar y parar persiana.
// Funciones a llamar por mqtt.
// Check estado de la persiana.
// Check auto: comprueba si ha cambiado el estado en un invervalo y sino, hace stop
//    para no mantener los relés continuamente encendidos.
// ==========


Ticker flip_persiana;
Ticker auto_persiana;

#define STOP_STATE 0
#define DOWN_STATE 1
#define UP_STATE 2

int up_button_state = 0;
int down_button_state = 0;
int persiana_state = STOP_STATE;
int last_persiana_state = STOP_STATE;
// Saber de dónde viene la orden: LOW = botón, HIGH = mqtt
int mqtt_control = LOW;

// ==========
// SETUP PERSIANA
// ==========
void setup_persiana(){
  flip_persiana.attach_ms(INPUT_INTERVAL, check_persiana);
  // auto_persiana.attach(AUTO_INTERVAL, check_auto);
}

// ==========
// SUBIMOS PERSIANA
// ==========
void up() {
  digitalWrite(DOWN_PIN, LOW);
  delay(SECURITY_DELAY);
  digitalWrite(UP_PIN, HIGH);
  delay(SECURITY_DELAY);
}

// ==========
// BAJAMOS PERSIANA
// ==========
void down() {
  digitalWrite(UP_PIN, LOW);
  delay(SECURITY_DELAY);
  digitalWrite(DOWN_PIN, HIGH);
  delay(SECURITY_DELAY);
}

// ==========
// PARAMOS PERSIANA
// ==========
void stop_all() {
  digitalWrite(UP_PIN, LOW);
  digitalWrite(DOWN_PIN, LOW);
}


// ==========
// RECIBIMOS "SUBIR" por MQTT
// ==========
void up_mqtt() {
  mqtt_control = HIGH;
  persiana_state = UP_STATE;
}

// ==========
// RECIBIMOS "BAJAR" por MQTT
// ==========
void down_mqtt() {
  mqtt_control = HIGH;
  persiana_state = DOWN_STATE;
}

// ==========
// RECIBIMOS "STOP" por MQTT
// ==========
void stop_mqtt() {
  mqtt_control = HIGH;
  persiana_state = STOP_STATE;
  stop_all();
}


// ==========
// LOOP PERSIANA
// ==========
void check_persiana() {

  // Leo botones
  up_button_state = !digitalRead(UP_BUTTON);
  down_button_state = !digitalRead(DOWN_BUTTON);

  // Si hay algún botón pulsado, manda botones
  if (up_button_state or down_button_state){
    mqtt_control = LOW;
  }

  // Si mandan los botones, pillo valor botones.
  if (!mqtt_control) {
    if (up_button_state and !down_button_state){
      persiana_state = UP_STATE;
    } else if (!up_button_state and down_button_state){
      persiana_state = DOWN_STATE;
    } else if (!up_button_state and ! down_button_state){
      persiana_state = STOP_STATE;
    }
  }

  // Si hay un cambio en el valor.
  if (persiana_state != last_persiana_state){

    // Según el estado de la persiana, actuo
    switch(persiana_state){
      case STOP_STATE:
        auto_persiana.detach();
        stop_all();
        break;
      case DOWN_STATE:
        auto_persiana.detach();
        auto_persiana.once(AUTO_INTERVAL, check_auto);
        down();
        break;
      case UP_STATE:
        auto_persiana.detach();
        auto_persiana.once(AUTO_INTERVAL, check_auto);
        up();
        break;
    }
    // Guardo valor para siguiente comprobación
    last_persiana_state = persiana_state;
  }
}

void check_auto(){
  if (last_persiana_state == persiana_state) {
    stop_all();
    if (mqttClient.connected()) mqttClient.publish(mqtt_base_topic.c_str(), 2, true, "STOP");
  }
}

