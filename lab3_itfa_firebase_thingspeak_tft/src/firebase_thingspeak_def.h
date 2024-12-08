#ifndef _FIREBASE_THINGSPEAK_DEF_H_
#define _FIREBASE_THINGSPEAK_DEF_H_

#include <Arduino.h>
#include "pin_def.h"
#include "dht_def.h"
#include "serial_def.h"

// Định nghĩa các macro cho SSID và PW của Wi-Fi
#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
// Thư viện Wi-Fi
#include "WiFi.h"


// Định nghĩa các macro để kết nối tới Firebase
#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#define EMAIL "ngxxfus@lab3-itfa.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"

//Thư viện dùng để kết nối tới Firebase
#include "FirebaseESP32.h"

// Tạo các đối tượng để thiết lập, xác thực, là truy xuất dữ liệu 
// từ Firebase
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Định nghĩa các macro để kết nối với Thingspeak
#define CHANNEL_ID 2768618
#define WRITE_API_KEY "VOICB5QBOT4RPFY6"
#define READ_API_KEY "MPFD1MXPBOB5O51W"
// Tạo đối tượng kiểu WifiClient để gởi nhận dữ liệu đến ThingSpeak
WiFiClient client;
// Thư viện kết nối tới ThingSpeak
#include "ThingSpeak.h"

//-------------- Firebase --------------//
// Định nghĩa hàm kiểm tra trạng thái kết nối WiFi
bool is_connected_to_wifi(){
    if(WiFi.status() != WL_CONNECTED){
        // Nếu không có  kết nối Wi-Fi thì thông báo lỗi
        set_indicator(0x2);
        // và in ra serial lỗi
        msg2ser("No Wi-Fi connection!");
        return false;
    }
    return true;
}

// Định nghĩa hàm kết nối Wi-Fi
void wifi_init(){
    if(is_connected_to_wifi()) return;
    // Thiết lập Wi-Fi ở chế độ tiêu chuẩn
    WiFi.mode(WIFI_STA); 
    // Kết nối Wi-Fi với macro đã định nghĩa từ trước
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    do{
        msg2ser("Connecting to Wi-fi...");
        delay(5000);
    }while(!is_connected_to_wifi());
    msg2ser("Connected to Wi-fi!");
}

// Định nghĩa hàm thiết lập kết nối với Firebase
void firebase_init() {
    msg2ser("Connecting to Firebase...");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;
    // Thực hiện việc kết nối đến khi thành công
    do Firebase.begin(&config, &auth);
    while(!Firebase.ready());
    // Thông báo đã kết nối Wi-Fi thành công
    msg2ser("Connected to Firebase!");
    // Thiết lập tự động kết nối lại Wi-Fi
    Firebase.reconnectWiFi(true);
}

// Hàm gởi dữ liệu đến Firebase
bool firebase_upload(SENSOR_DATA data){
    // Nếu không có kết nối Wi-Fi, trả về 0 - Không gởi được dữ liệu
    if(is_connected_to_wifi() == false) return false;
    // Tạo biến STATUS để lưu trạng thái gởi dữ liệu
    uint8_t STATUS = 0;
    // Nếu gởi dữ liệu thành công, phương thức setString() của Firebase sẽ trả
    // về true, ngược lại false
    STATUS += Firebase.setString(firebaseData, "ESP32/Temp", String(data.temp)) * 0x1;
    STATUS += Firebase.setString(firebaseData, "ESP32/Humid", String(data.humid)) * 0x2;
    // Thông báo mã lỗi nếu có
    if(STATUS&0x1 == 0) msg2ser("Thingspeak: Upload Temp feiled!");
    if(STATUS&0x2 == 0) msg2ser("Thingspeak: Upload Humud feiled!");
    return bool(STATUS==3);
}

bool firebase_download(bool* dev0, bool* dev1){
    uint8_t success = 0;
    static char strON[] = {'\\', '"', 'O', 'N', '\\', '"', '\0'};
    if(Firebase.getString(firebaseData, "ESP32/DEV0")){
        if(firebaseData.dataType() == "string"){
            success += 1;
            firebaseData.stringData() == String(strON)?
            *dev0 = 1:  *dev0 = 0;
        }else
            msg2ser("Firebase: Get DEV0: Error type!");
    }else
        msg2ser("Firebase: Get DEV0: Failed!");
    
    if(Firebase.getString(firebaseData, "ESP32/DEV1")){
        if(firebaseData.dataType() == "string"){
            success += 2;
            firebaseData.stringData() == String(strON)?
            *dev1 = 1:*dev1 = 0;
        }
        else
            msg2ser("Firebase: Get DEV1: Error type!");
    }else
        msg2ser("Firebase: Get DEV1: Failed!");
    return (success == 3);
}

//-------------- Thingspeak --------------//
void thingspeak_init(){
    msg2ser("Connecting to Thingspeak...");
    ThingSpeak.begin(client);  
    ThingSpeak.readLongField(CHANNEL_ID, 1, READ_API_KEY);
    ThingSpeak.getLastReadStatus();
    while(ThingSpeak.getLastReadStatus() != 200){
        msg2ser("Connecting to Thingspeak...");
        delay(2000);
    }
    m5sg2ser("Connected to Thingspeak!");
}

bool thingspeak_upload(SENSOR_DATA data){
    bool STATUS = true;
    ThingSpeak.setField(1, data.temp);
    ThingSpeak.setField(2, data.humid);
    auto rcv_code = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);
    if(bool(rcv_code != 200)){
        msg2ser("Thingspeak: Upload: Failed! ","CODE: ", String(rcv_code));
        STATUS = false;
    }
    return STATUS;
}

#endif 