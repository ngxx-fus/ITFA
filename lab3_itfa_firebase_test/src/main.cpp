
//refs: https://randomnerdtutorials.com/esp32-firebase-realtime-database/
#include <DHT.h>

#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#include "FirebaseESP32.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define DHTTYPE DHT11
#define DHT_DAT_PIN 21
DHT dht(DHT_DAT_PIN, DHTTYPE);

#define LED_CTL_PIN_1 21
#define INDICATOR_LED_PIN 23
#define LED_CTL_PIN_2 19

FirebaseData firebaseData;
String path = "/";
FirebaseAuth auth;
FirebaseConfig config;

void initWifi(){
  Serial.println("Connecting to Wi-fi");
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-fi");
}

void initFirebase() {
  Serial.println("Connecting to Firebase...");
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Connected to Firebase!");
  }else{
    Serial.println("Failed to connect to Firebase!");
    Serial.print("E:");
    Serial.println(config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void Sync_Sensor_Data(){
  digitalWrite(INDICATOR_LED_PIN, HIGH);
  delay(4000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if( isnan(t) || isnan(h)){
        Serial.println("DHT11 - E: Corrupted data!");
        digitalWrite(INDICATOR_LED_PIN, LOW);
        delay(100);
        digitalWrite(INDICATOR_LED_PIN, HIGH);
        delay(100);
        digitalWrite(INDICATOR_LED_PIN, LOW);
        delay(100);
        digitalWrite(INDICATOR_LED_PIN, HIGH);
      }else{
      Serial.println("Temp: ");
      Serial.println(t);
      Serial.println("Humid: ");
      Serial.println(h);
  }
  // Tắt đèn INDICATOR để thông báo khi quá trình đọc dừng lại
  digitalWrite(INDICATOR_LED_PIN, LOW);
}

void setup(){
  Serial.begin(9600);
  Serial.println(("\n\nHello!\n From MEOW GROUP!"));
  pinMode(LED_CTL_PIN_1, OUTPUT);
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  pinMode(LED_CTL_PIN_2, OUTPUT);
  dht.begin();
  initWifi();
  initFirebase();
}

void loop(){
  int so = random(0, 99);
  if (Firebase.setString(firebaseData, "/set", String(so))) {
    Serial.println("set: " + String(so));
  }
  Sync_Sensor_Data();
  delay(1000);
}