
// ==========
// mqtt.ino
//
// Este archivo contiene aquello relacionado con
// la conexión wifi y el protocolo MQTT
//
// Setup wifi
// Setup mqtt.
// Reconexión mqtt.
// Loop mqtt.
// Llamada callback de la suscripción mqtt.
// ==========



// ==========
// SETUP WIFI
// ==========
void setup_wifi() {
  #ifdef DEBUG
    Serial.print("Conectando a ");
    Serial.print(WIFI_SSID);
  #endif

  delay(10);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG
        Serial.print(".");
    #endif
  }
  #ifdef DEBUG
    Serial.println("OK");
    Serial.print("   IP: ");
    Serial.println(WiFi.localIP());
  #endif
}


// ==========
// SETUP MQTT
// ==========
void setup_mqtt() {
  #ifdef DEBUG
    Serial.println("Configurando cliente MQTT...");
  #endif

  mqtt_client_id = mqtt_client_id + ESP.getChipId();
  mqtt_client.setServer(MQTT_SERVER, 1883);
  mqtt_client.setCallback(mqtt_callback);
  mqtt_client.subscribe(mqtt_base_topic.c_str());

  #ifdef DEBUG
    Serial.printf("   Server IP: %s\r\n", MQTT_SERVER);
    Serial.printf("   Username:  %s\r\n", MQTT_USER);
    Serial.println("   Cliend Id: " + mqtt_client_id);
    Serial.println("   MQTT configurado!");
  #endif
}

// ==============
// CHECK MQTT CONNECTION
// ==============
void check_mqtt_connection() {
  if (!mqtt_client.connected() and !connecting_state) {
    connecting_state = HIGH;
    mqtt_reconnect();
  }
}

// ==============
// MQTT RECONNECT
// ==============
void mqtt_reconnect() {
  #ifdef DEBUG
    Serial.print("Intentando conexion MQTT...");
  #endif
  delay(200);
  // Intentamos conexión con user y pass
  if (mqtt_client.connect(mqtt_client_id.c_str(), MQTT_USER, MQTT_PASS)) {
    // Dejamos de intentar contectar
    ESP.reset();
    connecting_state = LOW;
    // Recien conectamos, nos suscribimos
    mqtt_client.subscribe(mqtt_base_topic.c_str());
    delay(100);
    #ifdef DEBUG
        Serial.println("Conectado!");
    #endif
  } else {
    // Esperamos 5 segundos para reintento
    /* delay(5000);
    mqtt_reconnect();
    */
    flip_connection.once(5, mqtt_reconnect);
    #ifdef DEBUG
        Serial.print("failed, rc=");
        Serial.print(mqtt_client.state());
        Serial.println(" nuevo intento en 5 segundos...");
    #endif
  }
}

// =========
// LOOP MQTT
// =========
void loop_mqtt() {
  // Comprobar conexión de MQTT o reconectar
  check_mqtt_connection();
  if (mqtt_client.connected()) mqtt_client.loop();
}

// =======================
// MQTT CALLBACK PRINCIPAL
// =======================
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  #ifdef DEBUG
    Serial.print("Recibo: [");
    Serial.print(topic);
    Serial.print("] ");
  #endif

  String mqtt_command = "";
  String mqtt_topic = (char*)topic;

  for (int i = 0; i < length; i++) {
    mqtt_command = mqtt_command + (char)payload[i];
    #ifdef DEBUG
        Serial.print((char)payload[i]);
    #endif
  }

  #ifdef DEBUG
    Serial.println();
    Serial.print("topic = ");
    Serial.println(mqtt_topic);
    Serial.print("comando = ");
    Serial.println(mqtt_command);
    Serial.println();
  #endif

  // ==========
  // CONTROL PERSIANA
  // ==========
  if (mqtt_topic.equals("/DOMUS/OFFICE/PERSIANA")) {
    if (mqtt_command.equals("UP")) {
      up_mqtt();
    } else if (mqtt_command.equals("DOWN")) {
      down_mqtt();
    } else if (mqtt_command.equals("STOP")) {
      stop_mqtt();
    }

    #ifdef DEBUG
        Serial.println(mqtt_command);
    #endif
  }
}
