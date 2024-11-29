#ifndef _FIREBASE_DEF_H_
#define _FIREBASE_DEF_H_

#include <Arduino.h>
#include "pin_def.h"
#include "dht11_def.h"

#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"


#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#define EMAIL "itfa-name@lab3-itfa.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"
#include "FirebaseESP32.h"
// #include "addons/TokenHelper.h"
// #include "addons/RTDBHelper.h"

FirebaseData firebaseData;
String path = "/";
FirebaseAuth auth;
FirebaseConfig config;

bool is_connected_to_wifi(){
    if(WiFi.status() != WL_CONNECTED){
        set_indicator(0x2);
        Serial.println("No Wi-Fi connection!");
        return false;
    }
    return true;
}

void wifi_init(){
    WiFi.begin(WIFI_SSID, WIFI_PWD);
        do{
            Serial.println("Connecting to Wi-fi...");
            delay(2000);
        }while(!is_connected_to_wifi());
    Serial.println("Connected to Wi-fi!");
}

void firebase_init() {
    Serial.println("Connecting to Firebase...");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;
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
    // config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

bool firebase_upload(SENSOR_DATA data){
    if(is_connected_to_wifi() == false) return false;
    // Sync sensor data
    if(
        !Firebase.setString(firebaseData, "Temp", String(data.temp))
        || !Firebase.setString(firebaseData, "Humid", String(data.humid))
    ){
        Serial.println("Failed to sync to Firebase!");
        set_indicator(0x2);
        return false;
    }
    return true;
}



#endif
