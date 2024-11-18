//refs: https://randomnerdtutorials.com/esp32-firebase-realtime-database/

#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define DHTTYPE DHT11
#define DHT_DAT_PIN 21
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

#define LED_CTL_PIN_1 21
#define INDICATOR_LED_PIN 23
#define LED_CTL_PIN_2 19

struct SENSOR_DATA{
  float temp;
  float humid;
} sensor_data;

void Indicate_Error(){
  // Blink led to noti error
  digitalWrite(INDICATOR_LED_PIN, LOW); delay(100);
  digitalWrite(INDICATOR_LED_PIN, HIGH); delay(100);
  digitalWrite(INDICATOR_LED_PIN, LOW); delay(100);
  digitalWrite(INDICATOR_LED_PIN, HIGH);
}

void initSerial(){
  Serial.begin(9600);
  Serial.println(("\n\nHello!\n From MEOW GROUP!"));
}

void initGPIOPin(){
  pinMode(LED_CTL_PIN_1, OUTPUT);
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  pinMode(LED_CTL_PIN_2, OUTPUT);
}

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
  while(0x1)
    // sign-up as anonymous
    if(Firebase.signUp(&config, &auth, "", "")){
      Serial.println("Connected to Firebase!");
      break;
    }else{
      Serial.println("Failed to connect to Firebase!");
      Serial.print("E:");
      Serial.println(config.signer.signupError.message.c_str());
      Serial.println("Re-try...");
    }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void Firebase_Sync(){
  // Sync sensor data
  if(
    !Firebase.setString(firebaseData, "Temp", String(sensor_data.temp))
    || !Firebase.setString(firebaseData, "Humid", String(sensor_data.humid))
  ){
    Serial.println("Failed to sync to Firebase!");
    Indicate_Error();
  }
}

void Update_Sensor_Data(){
  // Turn-on indicator light
  digitalWrite(INDICATOR_LED_PIN, HIGH);
  // Wait 4 seconds for DHT sensor
  delay(4000);
  // Read humid and temp from dht sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check read data
  if( isnan(t) || isnan(h) ){
        // Send Error msg to serial
        Serial.println("DHT11 - E: Corrupted data!");
        Indicate_Error();
      }else{
      // Send Temp + Humid data to serial
      Serial.println("Temp: ");
      Serial.println(t);
      Serial.println("Humid: ");
      Serial.println(h);
      // Update data sensor
      sensor_data.humid = h;
      sensor_data.temp = t;
      // Sync to Firebase
      Firebase_Sync();

    }
  // Turn-off indicator light
  digitalWrite(INDICATOR_LED_PIN, LOW);
}

void setup(){
  initSerial();
  initGPIOPin();
  dht.begin();
  initWifi();
  initFirebase();
}

void loop(){
  Update_Sensor_Data();
  delay(1000);
}