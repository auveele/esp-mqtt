#include <ESP8266WiFi.h>        // For ESP8266
#include <AsyncMqttClient.h>    // For Async MQTT
#include <Ticker.h>             // For avoid blockin functions

// ==========
// DECLARAMOS
// ==========
#define DEBUG 1
#define UP_PIN 12
#define DOWN_PIN 13
#define UP_BUTTON 2
#define DOWN_BUTTON 0


//=========
//PIN SETUP
//=========
void setup_pins() {
  pinMode(UP_PIN, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
}

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
}

// ==============
// LOOP PRINCIPAL
// ==============
void loop() {
}
