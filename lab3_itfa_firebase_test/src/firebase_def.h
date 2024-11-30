#ifndef _FIREBASE_DEF_H_
#define _FIREBASE_DEF_H_

#include <Arduino.h>
#include "pin_def.h"
#include "dht11_def.h"
#include "serial_def.h"

#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"


#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#define EMAIL "itfa-name@lab3-itfa.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"

// #define DATABASE_URL "https://this-is-a-test-a0f7d-default-rtdb.firebaseio.com/"
// #define API_KEY "AIzaSyDNSbmHmGsDEip7-m6zFJKe9TZ5d56bjDs"
// #define EMAIL "hehe-470@this-is-a-test-a0f7d.iam.gserviceaccount.com"
// #define PASSWORD "nGXXFUS@3204"

#include "FirebaseESP32.h"
// #include "addons/TokenHelper.h"
// #include "addons/RTDBHelper.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

bool is_connected_to_wifi(){
    if(WiFi.status() != WL_CONNECTED){
        set_indicator(0x2);
        msg2ser("No Wi-Fi connection!");
        return false;
    }
    return true;
}

void wifi_init(){
    WiFi.begin(WIFI_SSID, WIFI_PWD);
        do{
            msg2ser("Connecting to Wi-fi...");
            delay(2000);
        }while(!is_connected_to_wifi());
    msg2ser("Connected to Wi-fi!");
}

void firebase_init() {
    msg2ser("Connecting to Firebase...");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;
    while(0x1)
        // sign-up as anonymous
        if(Firebase.signUp(&config, &auth, "", "")){
        msg2ser("Connected to Firebase!");
        break;
        }else{
        msg2ser("Failed to connect to Firebase!");
        Serial.print("E:");
        msg2ser(config.signer.signupError.message.c_str());
        msg2ser("Re-try...");
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
        msg2ser("Failed to sync to Firebase!");
        set_indicator(0x2);
        return false;
    }
    return true;
}



#endif
