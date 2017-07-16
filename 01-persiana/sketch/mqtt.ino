
// ==========
// mqtt.ino
//
// Este archivo contiene aquello relacionado con el protocolo MQTT
// ==========


AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;


// ==========
// SETUP MQTT
// ==========
void setup_mqtt() {
  #ifdef DEBUG
    Serial.println("Configurando cliente MQTT...");
  #endif

  mqtt_client_id = mqtt_client_id + ESP.getChipId();
  
  mqttClient.onConnect(on_mqtt_connect);
  mqttClient.onDisconnect(on_mqtt_disconnect);
  mqttClient.onSubscribe(on_mqtt_subscribe);
  mqttClient.onUnsubscribe(on_mqtt_unsubscribe);
  mqttClient.onMessage(on_mqtt_message);
  mqttClient.onPublish(on_mqtt_publish);
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASS);

  #ifdef DEBUG
    Serial.print("   Server IP: ");
    Serial.println(MQTT_BROKER);
    Serial.print("   Username: ");
    Serial.print(MQTT_USER);
    Serial.println("   Cliend Id: " + mqtt_client_id);
    Serial.println("   MQTT configurado!");
  #endif
}

// ==========
// CONNECT TO MQTT BROKER
// ==========
void connect_mqtt() {
  #ifdef DEBUG
    Serial.print("Conectando al Broker MQTT...  ");
  #endif
  mqttClient.connect();
}

// ==========
// EVENT - ON CONNECT
// ==========
void on_mqtt_connect(bool sessionPresent) {
  #ifdef DEBUG
    Serial.println("OK!!");
    // Serial.print("Sesión actual: ");
    // Serial.println(sessionPresent);
  #endif
  mqtt_suscribe();
}

// ==========
// MQTT SUSCRIBE
// ==========
void mqtt_suscribe(){
  // uint16_t packetIdSub = mqttClient.subscribe("/DOMUS/OFFICE/PERSIANA/#", 2);
  uint16_t packetIdSub = mqttClient.subscribe(mqtt_base_topic.c_str(), 2);
  #ifdef DEBUG
    Serial.print("Solicitud de suscripción a ");
    Serial.print(packetIdSub);
    Serial.print(". ");
    Serial.println(mqtt_base_topic);
  #endif
}

// ==========
// EVENT - ON DISCONNECT
// ==========
void on_mqtt_disconnect(AsyncMqttClientDisconnectReason reason) {
  #ifdef DEBUG
    Serial.println("Desconectado de Broker MQTT.");
  #endif

  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connect_mqtt);
  }
}

// ==========
// EVENT - ON SUSCRIBE
// ==========
void on_mqtt_subscribe(uint16_t packetId, uint8_t qos) {
  #ifdef DEBUG
    Serial.print("Suscrito a topic ");
    Serial.print(packetId);
    Serial.print(", qos: ");
    Serial.println(qos);
  #endif
}

// ==========
// EVENT - ON UNSUSCRIBE
// ==========
void on_mqtt_unsubscribe(uint16_t packetId) {
  #ifdef DEBUG
    Serial.println("Unsubscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
  #endif
}

// ==========
// EVENT - ON PUBLISH
// ==========
void on_mqtt_publish(uint16_t packetId) {
  /*
  #ifdef DEBUG
    Serial.println("Publish acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
  #endif
  */
}

// ==========
// EVENT - ON MESSAGE RECEIVED
// ==========
void on_mqtt_message(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {

  // Declaro variables
  String mqtt_command = "";
  String mqtt_topic = (char*)topic;
  // Paso el CHAR a String
  for (int i = 0; i < len; i++) {
    mqtt_command = mqtt_command + (char)payload[i];
  }
  
  #ifdef DEBUG
    Serial.print("Recibo: [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.print(mqtt_command);
    Serial.println();
  #endif

  // ==========
  // CONTROL PERSIANA
  // ==========
  if (mqtt_topic.equals(mqtt_base_topic)) {
    if (mqtt_command.equals("UP")) {
      up_mqtt();
    } else if (mqtt_command.equals("DOWN")) {
      down_mqtt();
    } else if (mqtt_command.equals("STOP")) {
      stop_mqtt();
    }
  }
}

