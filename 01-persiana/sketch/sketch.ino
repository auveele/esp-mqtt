#include <ESP8266WiFi.h>        // For ESP8266
#include <AsyncMqttClient.h>    // For Async MQTT
#include <Ticker.h>             // For avoid blockin functions
#include <EEPROM.h>

#define DEBUG 1

// ===============
// SETUP PRINCIPAL
// ===============
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("\r\nIniciando...");
  #endif

  setup_pins();
  setup_mqtt();
  setup_wifi();
  setup_persiana();
  setup_restart();
  setup_eeprom();
}

// ==============
// LOOP PRINCIPAL
// ==============
void loop() {
}
