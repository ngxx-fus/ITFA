// #include "pin_def.h"
// #include "serial_def.h"
// #include "dht11_def.h"
// #include "firebase_def.h"

// void setup(){
//     serial_init(115200);
//     gpio_init();
//     wifi_init();
//     firebase_init();

// }

// void loop(){
//     SENSOR_DATA data = dht11_read();
//     msg2ser("Temp :", (String)data.temp);
//     msg2ser("Temp :", (String)data.humid);
//     if(is_data_corrupted(data)){
//         set_indicator(0x1);
//         return;
//     }
//     firebase_upload(data);
// }

#include <Arduino.h>

#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define DATABASE_URL "https://this-is-a-test-a0f7d-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyDNSbmHmGsDEip7-m6zFJKe9TZ5d56bjDs"
#define EMAIL "hehe-470@this-is-a-test-a0f7d.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"

#include "FirebaseESP32.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;


void setup(){
    Serial.begin(115200);
    Serial.println("Hello from ESP32!");

    WiFi.begin(WIFI_SSID, WIFI_PWD);

    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;

    Firebase.signUp(&config, &auth, "", "");
    
    config.token_status_callback = tokenStatusCallback;
    
    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);

    //TEST
    Serial.printf(config.signer.signupError.message.c_str());
    Serial.printf("Setup done!");

}

void loop(){
    Serial.printf("loading");
    delay(1000);
    if(!Firebase.setString(firebaseData, "TEST_ADDR", "TEST_VALUE"))
        Serial.println("Uload: e");
    Firebase.setInt(firebaseData, "/path", 23)
}