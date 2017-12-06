#include <ESP8266WiFi.h>        // For ESP8266
#include <AsyncMqttClient.h>    // For Async MQTT
#include <Ticker.h>             // For avoid blockin functions
#include <EEPROM.h>

#define DEBUG 1

// #####
// DEBUG
// #####
#ifdef DEBUG
 #define DEBUG_PRINT(x)     Serial.print (x)
 #define DEBUG_PRINTDEC(x)  Serial.print (x, DEC)
 #define DEBUG_PRINTLN(x)   Serial.println (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTDEC(x)
 #define DEBUG_PRINTLN(x)
#endif 

// ###############
// SETUP PRINCIPAL
// ###############
void setup() {
  delay(3000);
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  DEBUG_PRINTLN("\r\nIniciando!");

  setup_pins();
  setup_persiana();  
  setup_eeprom();
  setup_restart();
  setup_mqtt();
  setup_wifi();  
}

// ##############
// LOOP PRINCIPAL
// ##############
void loop() {
}
