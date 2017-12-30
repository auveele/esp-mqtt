
/*########################
##########################
 
config.ino

Archivo para el respositorio, renombrar a 'config' para compilar.
El archivo config.ino se ignorará al hacer un commit para no
publicar las credenciales.

Si este archivo es modificado,
eliminar del .gitignore para que se sincronice.

##########################
########################*/

// ###########
// STRIP
// ###########
static const uint8_t Brightness =  255;
// --- FastLED Setings
#define NUM_LEDS 112
#define DATA_PIN     2
#define LED_TYPE     WS2812B // led strip type for FastLED
#define COLOR_ORDER  RGB     // color order for bitbang
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

int ANIMATION = 0;

// ###########
// WIFI CONFIG
// ###########
#define WIFI_SSID "xxxx"
#define WIFI_PASS "xxxx"
#define WIFI_IP IPAddress(192, 168, 1, 101)
#define WIFI_GATEWAY IPAddress(192, 168, 1, 1)
#define WIFI_SUBNET IPAddress(255, 255, 255, 0)

// ###########
// MQTT SERVER
// ###########
#define MQTT_BROKER IPAddress(192, 168, 1, 13)
#define MQTT_PORT 1883
#define MQTT_USER "domus"
#define MQTT_PASS "xxxxx"
// No tocables
AsyncMqttClient mqttClient;

// ###########
// MQTT CLIENT
// ###########
String mqtt_slash = "/";
String mqtt_scope = "DOMUS";
String mqtt_room = "OFFICE";
String mqtt_device = "STRIP";

String mqtt_client_id = "ESP8266-";         // This text is concatenated with ChipId to get unique client_id
String mqtt_base_topic = mqtt_slash + mqtt_scope + mqtt_slash + mqtt_room + mqtt_slash + mqtt_device; // + mqtt_slash + "#";

