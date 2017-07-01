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
// MQTT RECONNECT
// ==============
void mqtt_reconnect() {
  // Loop hasta que reconecte
  while (!mqtt_client.connected()) {
    #ifdef DEBUG
      Serial.print("Intentando conexion MQTT...");
    #endif
    // Intentamos conexión con user y pass
    if (mqtt_client.connect(mqtt_client_id.c_str(), MQTT_USER, MQTT_PASS)) {
      mqtt_client.subscribe(mqtt_base_topic.c_str());
      #ifdef DEBUG
        Serial.println("Conectado!");
      #endif
    } else {
      #ifdef DEBUG
        Serial.print("failed, rc=");
        Serial.print(mqtt_client.state());
        Serial.println(" nuevo intento en 5 segundos...");
      #endif
      // Esperamos 5 segundos para reintento
      // TODO: Hacer no bloqueante.
      delay(5000);
    }
  }
}

// =========
// LOOP MQTT
// =========
void loop_mqtt(){
  // Comprobar conexión de MQTT o reconectar
  if (!mqtt_client.connected()) {
    mqtt_reconnect();
  }
  mqtt_client.loop();
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
