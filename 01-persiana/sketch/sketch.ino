#include <ESP8266WiFi.h>        // For ESP8266
#include <AsyncMqttClient.h>    // For Async MQTT
#include <Ticker.h>             // For avoid blockin functions
#include <EEPROM.h>

#define DEBUG 1

// ===============
// SETUP PRINCIPAL
// ===============
void setup() {
  delay(3000);
  #ifdef DEBUG == 1
    Serial.begin(115200);
    Serial.println("\r\nIniciando!");
  #endif

  setup_pins();
  setup_persiana();  
  setup_eeprom();
  setup_restart();
  setup_mqtt();
  setup_wifi();  
}

// ==============
// LOOP PRINCIPAL
// ==============
void loop() {
}

void print_memory(){
  long mem = ESP.getFreeHeap();
  Serial.print("freeMemory()=");
  Serial.println(mem);
}
