
/*########################
##########################

  wifi.ino

  Este archivo contiene aquello relacionado con la conexión wifi.

    Setup fifi
    Connect wifi
    Event - On wifi connect
    Event - On wifi disconnect

##########################
########################*/

Ticker wifiReconnectTimer;

// ##########
// SETUP WIFI
// ##########
void setup_wifi() {
  WiFi.disconnect(true);
  WiFi.onEvent(event_wifi);
  WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET);
  connect_wifi();
}

// ##########
// EVENT WIFI
// ##########
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

// ############
// CONNECT WIFI
// ############
void connect_wifi() {
  WiFi.hostname("TEST_ESP");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  DEBUG_PRINT("Conectando a wifi ...");
  delay(200);
}

// #######################
// EVENT - ON WIFI CONNECT
// #######################
void on_wifi_connect() {
  DEBUG_PRINTLN("OK");
  DEBUG_PRINT("\tIP: ");
  DEBUG_PRINTLN(WiFi.localIP());
  // En conectar la wifi, se intenta conectar a MQTT
  connect_mqtt();
}

// ##########################
// EVENT - ON WIFI DISCONNECT
// ##########################
void on_wifi_disconnect() {
  DEBUG_PRINTLN("Desconectado de la wifi.");
  // Aseguramos que no intenta reconectar MQTT sino hay wifi.
  mqttReconnectTimer.detach();
  // Programamos reconexión a Wifi tras 2 segundos.
  wifiReconnectTimer.once(2, connect_wifi);
}


