
// ==========
// Archivo para el respositorio, renombrar a 'config' para compilar.
// El archivo config.ino se ignorará al hacer un commit para no
// publicar las credenciales.
//
// Si este archivo es modificado,
// eliminar del .gitignore para que se sincronice.
// ==========


// ===========
// WIFI CONFIG
// ===========
#define WIFI_SSID "XXX"
#define WIFI_PASS "xxx"

// ===========
// MQTT SERVER
// ===========
#define MQTT_SERVER "192.168.1.6"
#define MQTT_USER "xxxxxx"
#define MQTT_PASS "xxxxxx"

// ===========
// MQTT CLIENT
// ===========

String mqtt_slash = "/";
String mqtt_scope = "DOMUS";
String mqtt_room = "OFFICE";
String mqtt_device = "PERSIANA";

String mqtt_client_id = "ESP8266-";         // This text is concatenated with ChipId to get unique client_id
String mqtt_base_topic = mqtt_slash + mqtt_scope + mqtt_slash + mqtt_room + mqtt_slash + mqtt_device + mqtt_slash + "#";
