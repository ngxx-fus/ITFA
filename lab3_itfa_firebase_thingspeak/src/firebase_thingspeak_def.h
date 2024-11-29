#ifndef _FIREBASE_THINGSPEAK_DEF_H_
#define _FIREBASE_THINGSPEAK_DEF_H_

#include <Arduino.h>
#include "pin_def.h"
#include "dht_def.h"
#include "serial_def.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PWD ""
#include "WiFi.h"

#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#define EMAIL "ngxxfus@lab3-itfa.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"

#include "FirebaseESP32.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

#define CHANNEL_ID 2768618
#define WRITE_API_KEY "YGOYAN7BXVVMG4XE"
WiFiClient client;
#include "ThingSpeak.h"

//-------------- Firebase --------------//
bool is_connected_to_wifi(){
    if(WiFi.status() != WL_CONNECTED){
        set_indicator(0x2);
        msg2ser("No Wi-Fi connection!");
        return false;
    }
    return true;
}

void wifi_init(){
    if(is_connected_to_wifi()) return;
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
    do Firebase.begin(&config, &auth);
    while(!Firebase.ready());
    msg2ser("Connected to Firebase!");
    Firebase.reconnectWiFi(true);
}

bool firebase_upload(SENSOR_DATA data){
    if(is_connected_to_wifi() == false) return false;
    // Sync sensor data
    uint8_t STATUS = 0;
    STATUS += Firebase.setString(firebaseData, "Temp", String(data.temp)) * 0x1;
    STATUS += Firebase.setString(firebaseData, "Humid", String(data.humid)) * 0x2;
    if(STATUS&0x1 == 0) msg2ser("Thingspeak: Upload Temp feiled!");
    if(STATUS&0x2 == 0) msg2ser("Thingspeak: Upload Humud feiled!");
    return bool(STATUS==3);
}

DEV firebase_download(){
    DEV dev;
    // for dev 0
    if(Firebase.getInt(firebaseData, "DEV0")){
        // if(firebaseData.dataType() == "int"){
            dev.__0 = firebaseData.intData();
            msg2ser("DEV0: ", (String) dev.__0);
            msg2ser("dataType: ", (String) firebaseData.dataType());
        // }else
            // msg2ser("Firebase: Get DEV0: Error type!");
    }else
        msg2ser("Firebase: Get: Failed!");
    
    // for dev 1
    if(Firebase.getInt(firebaseData, "DEV1")){
        if(firebaseData.dataType() == "int")
            dev.__1 = firebaseData.intData();
        else
            msg2ser("Firebase: Get DEV1: Error type!");
    }else
        msg2ser("Firebase: Get: Failed!");
    
    return dev;
}

//-------------- Thingspeak --------------//

void thingspeak_init(){
    msg2ser("Connecting to Thingspeak...");
    WiFi.mode(WIFI_STA); 
    ThingSpeak.begin(client);  // Initialize ThingSpeak
    while(ThingSpeak.writeField(CHANNEL_ID, 8, 1, WRITE_API_KEY) != 200){
        msg2ser("Connecting to Thingspeak...");
        delay(2000);
    }
    msg2ser("Connected to Thingspeak!");
}

bool thingspeak_upload(SENSOR_DATA data){
    uint8_t STATUS = 0;
    STATUS += uint8_t(ThingSpeak.writeField(CHANNEL_ID, 1, data.temp, WRITE_API_KEY) == 200)*1;
    STATUS += uint8_t(ThingSpeak.writeField(CHANNEL_ID, 2, data.humid, WRITE_API_KEY) != 200)*2;
    if(STATUS&0x1 == 0) msg2ser("Thingspeak: Upload Temp feiled!");
    if(STATUS&0x2 == 0) msg2ser("Thingspeak: Upload Humud feiled!");
    return bool(STATUS==3);
}

#endif 