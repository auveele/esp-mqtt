
// ==========
// config.ino
//
// Archivo para el respositorio, renombrar a 'config' para compilar.
// El archivo config.ino se ignorará al hacer un commit para no
// publicar las credenciales.
//
// Si este archivo es modificado,
// eliminar del .gitignore para que se sincronice.
// ==========


// ===========
// DECLARE PIN
// ===========
#define UP_PIN 12
#define DOWN_PIN 13
#define UP_BUTTON 2
#define DOWN_BUTTON 0

// ============
// AUTO RESTART
// ============
#define H 6
#define M 0
#define S 0
#define SES 60
unsigned long RESTART_TIME = (H * SES * SES) + (M * SES) + S; // H * M * S

// ===========
// WIFI CONFIG
// ===========
#define WIFI_SSID "XXX"
#define WIFI_PASS "XXX"
#define WIFI_IP IPAddress(192, 168, 1, 101)
#define WIFI_GATEWAY IPAddress(192, 168, 1, 1)
#define WIFI_SUBNET IPAddress(255, 255, 255, 0)

// ===========
// MQTT SERVER
// ===========
#define MQTT_BROKER IPAddress(192, 168, 1, 6)
#define MQTT_PORT 1883
#define MQTT_USER "XXX"
#define MQTT_PASS "XXX"

// ===========
// MQTT CLIENT
// ===========

String mqtt_slash = "/";
String mqtt_scope = "DOMUS";
String mqtt_room = "OFFICE";
String mqtt_device = "PERSIANA";

String mqtt_client_id = "ESP8266-";         // This text is concatenated with ChipId to get unique client_id
String mqtt_base_topic = mqtt_slash + mqtt_scope + mqtt_slash + mqtt_room + mqtt_slash + mqtt_device; // + mqtt_slash + "#";

// Bloqueo del botón físico, LOW funciona todo, HIGH sólo MQTT
boolean mqtt_only = LOW;

// ===========
// PERSIANA
// ===========

#define INPUT_INTERVAL 100    // ms
#define AUTO_INTERVAL 15      // segs
#define SECURITY_DELAY 150   // ms

//==========
// PIN SETUP
//==========
void setup_pins() {
  pinMode(UP_PIN, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
}
