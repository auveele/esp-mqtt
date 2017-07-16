
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


WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;


// ==========
// SETUP WIFI
// ==========
void setup_wifi() {
  wifiConnectHandler = WiFi.onStationModeGotIP(on_wifi_connect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(on_wifi_disconnect);
  WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET);
  connect_wifi();
}

// ==========
// CONNECT WIFI
// ==========
void connect_wifi() {
  #ifdef DEBUG
    Serial.print("Conectando a wifi ...");
  #endif
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

// ==========
// EVENT - ON WIFI CONNECT
// ==========
void on_wifi_connect(const WiFiEventStationModeGotIP& event) {
  #ifdef DEBUG
    Serial.println("OK");
    Serial.print("   IP: ");
    Serial.println(WiFi.localIP());
  #endif
  // En conectar la wifi, se intenta conectar a MQTT
  connect_mqtt();
}

// ==========
// EVENT - ON WIFI DISCONNECT
// ==========
void on_wifi_disconnect(const WiFiEventStationModeDisconnected& event) {
  #ifdef DEBUG
    Serial.println("Desconectado de la wifi.");
  #endif
  // Aseguramos que no intenta reconectar MQTT sino hay wifi.
  mqttReconnectTimer.detach();
  // Programamos reconexión a Wifi tras 2 segundos.
  wifiReconnectTimer.once(2, connect_wifi);
}

