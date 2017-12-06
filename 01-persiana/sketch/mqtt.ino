
/*########################
##########################

  mqtt.ino

  Este archivo contiene aquello relacionado con el protocolo MQTT

##########################
########################*/


Ticker mqttReconnectTimer;


// ##########
// SETUP MQTT
// ##########
void setup_mqtt() {
  DEBUG_PRINTLN("Configurando cliente MQTT...");
  mqtt_client_id = mqtt_client_id + ESP.getChipId();
  
  mqttClient.onConnect(on_mqtt_connect);
  mqttClient.onDisconnect(on_mqtt_disconnect);
  mqttClient.onSubscribe(on_mqtt_subscribe);
  mqttClient.onUnsubscribe(on_mqtt_unsubscribe);
  mqttClient.onMessage(on_mqtt_message);
  mqttClient.onPublish(on_mqtt_publish);
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASS);

  DEBUG_PRINT("\tServer IP: ");  delay(200);
  DEBUG_PRINTLN(MQTT_BROKER);    delay(200);
  DEBUG_PRINT("\tUsername: ");   delay(200);
  DEBUG_PRINTLN(MQTT_USER);      delay(200);
  DEBUG_PRINT("\tClient Id: ");  delay(200);
  DEBUG_PRINTLN(mqtt_client_id); delay(200);
  DEBUG_PRINTLN("\tMQTT configurado!");
}

// ######################
// CONNECT TO MQTT BROKER
// ######################
void connect_mqtt() {
  DEBUG_PRINT("Conectando al Broker MQTT...  ");
  mqttClient.connect();
}

// ##################
// EVENT - ON CONNECT
// ##################
void on_mqtt_connect(bool sessionPresent) {
  DEBUG_PRINTLN("OK!!");
    // DEBUG_PRINT("Sesión actual: ");
    // DEBUG_PRINTLN(sessionPresent);
  send_reset_advice();
  mqtt_suscribe();
}

// #############
// MQTT SUSCRIBE
// #############
void mqtt_suscribe(){
  // uint16_t packetIdSub = mqttClient.subscribe("/DOMUS/OFFICE/PERSIANA/#", 2);
  uint16_t packetIdSub = mqttClient.subscribe(mqtt_base_topic.c_str(), 2);
  DEBUG_PRINT("Solicitud de suscripción a ");
  DEBUG_PRINT(packetIdSub);
  DEBUG_PRINT(". ");
  DEBUG_PRINTLN(mqtt_base_topic);
}

// #####################
// EVENT - ON DISCONNECT
// #####################
void on_mqtt_disconnect(AsyncMqttClientDisconnectReason reason) {
  DEBUG_PRINTLN("Desconectado de Broker MQTT.");
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connect_mqtt);
  }
}

// ###################
// EVENT - ON SUSCRIBE
// ###################
void on_mqtt_subscribe(uint16_t packetId, uint8_t qos) {
  DEBUG_PRINT("Suscrito a topic ");
  DEBUG_PRINT(packetId);
  DEBUG_PRINT(", qos: ");
  DEBUG_PRINTLN(qos);
}

// #####################
// EVENT - ON UNSUSCRIBE
// #####################
void on_mqtt_unsubscribe(uint16_t packetId) {
  DEBUG_PRINTLN("Unsubscribe acknowledged.");
  DEBUG_PRINT("  packetId: ");
  DEBUG_PRINTLN(packetId);
}

// ##################
// EVENT - ON PUBLISH
// ##################
void on_mqtt_publish(uint16_t packetId) {
  /*
  #ifdef DEBUG
    Serial.println("Publish acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
  #endif
  */
}

// ###########################
// EVENT - ON MESSAGE RECEIVED
// ###########################
void on_mqtt_message(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {

  // Declaro variables
  String mqtt_command = "";
  String mqtt_topic = (char*)topic;
  // Paso el CHAR a String
  for (int i = 0; i < len; i++) {
    mqtt_command = mqtt_command + (char)payload[i];
  }
  
  DEBUG_PRINT("Recibo: [");
  DEBUG_PRINT(topic);
  DEBUG_PRINT("] ");
  DEBUG_PRINT(mqtt_command);
  DEBUG_PRINTLN("");

  // ################
  // CONTROL PERSIANA
  // ################
  if (mqtt_topic.equals(mqtt_base_topic)) {
    if (mqtt_command.equals("UP")) {
      up_mqtt();
    } else if (mqtt_command.equals("DOWN")) {
      down_mqtt();
    } else if (mqtt_command.equals("STOP")) {
      stop_mqtt();
    } else if (mqtt_command.equals("BLOCK")) {
      // Bloquear mando físico
      only_mqtt();
    } else if (mqtt_command.equals("UNBLOCK")){
      // Habilitar mando físico
      not_only_mqtt();
    }
  }
}


