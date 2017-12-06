
// ==========
// wifi.ino
//
// Este archivo contiene aquello relacionado con la conexión wifi.
//
// Setup fifi
// Connect wifi
// Event - On wifi connect
// Event - On wifi disconnect
// ==========


Ticker wifiReconnectTimer;


// ==========
// SETUP WIFI
// ==========
void setup_wifi() {
  WiFi.disconnect(true);
  WiFi.onEvent(event_wifi);
  WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET);
  connect_wifi();
}

// ==========
// EVENT WIFI
// ==========
void event_wifi(WiFiEvent_t event) {
    switch(event) {
        case WIFI_EVENT_STAMODE_GOT_IP:
            on_wifi_connect();
            break;
        case WIFI_EVENT_STAMODE_DISCONNECTED:
            on_wifi_disconnect();
            break;
    }
}

// ==========
// CONNECT WIFI
// ==========
void connect_wifi() {
  WiFi.hostname("TEST_ESP");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  #ifdef DEBUG
    Serial.print("Conectando a wifi ...");
    delay(200);
  #endif
}

// ==========
// EVENT - ON WIFI CONNECT
// ==========
void on_wifi_connect() {
// void on_wifi_connect(const WiFiEventStationModeConnected& event) {
  #ifdef DEBUG
    Serial.println("OK");
    Serial.print("\tIP: ");
    Serial.println(WiFi.localIP());
  #endif
  // En conectar la wifi, se intenta conectar a MQTT
  connect_mqtt();
}

// ==========
// EVENT - ON WIFI DISCONNECT
// ==========
void on_wifi_disconnect() {
  #ifdef DEBUG
    Serial.println("Desconectado de la wifi.");
  #endif
  // Aseguramos que no intenta reconectar MQTT sino hay wifi.
  mqttReconnectTimer.detach();
  // Programamos reconexión a Wifi tras 2 segundos.
  wifiReconnectTimer.once(2, connect_wifi);
}


