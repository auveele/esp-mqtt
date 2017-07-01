#include <ESP8266WiFi.h>        // For ESP8266
#include <PubSubClient.h>       // For MQTT
#include <Ticker.h>             // For avoid blockin functions

// ==========
// DECLARAMOS
// ==========
#define DEBUG 1
#define UP_PIN 12
#define DOWN_PIN 13
#define UP_BUTTON 2
#define DOWN_BUTTON 0
#define SECURITY_DELAY 300
#define INTERVAL_DELAY 50

Ticker flipper;

// MQTT client
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

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
  setup_wifi();
  setup_mqtt();

  #ifdef DEBUG
    Serial.println("Setup completado! Iniciando módulo...");
  #endif
}

// ==============
// LOOP PRINCIPAL
// ==============
void loop() {
  loop_persiana();
  loop_mqtt();
}
