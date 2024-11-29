#include <Arduino.h>
#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define DHTTYPE DHT11
#define DHT_DAT_PIN 5
#include <DHT.h>
DHT dht(DHT_DAT_PIN, DHTTYPE);

#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#include "FirebaseESP32.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

FirebaseData firebaseData;
String path = "/";
FirebaseAuth auth;
FirebaseConfig config;