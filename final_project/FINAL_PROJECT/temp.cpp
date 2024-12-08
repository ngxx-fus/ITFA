#include <Arduino.h>
#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define INDICATOR_LED_PIN 26
#define DEV_0_PIN 25
#define DEV_1_PIN 27


void set_indicator(int err_code = 0){
  switch (err_code){
    case 0x0: err_code = 1; break;
    case 0x1: err_code = 2; break;
    case 0x2: err_code = 3; break;
    case 0x3: err_code = 4; break;
    case 0x4: err_code = 5; break;
    default:  err_code = 0;
  }
  while(err_code--){
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
    digitalWrite(INDICATOR_LED_PIN, HIGH); delay(200);
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
  }
}

void gpio_init(){
    pinMode(INDICATOR_LED_PIN, OUTPUT);
    pinMode(DEV_0_PIN, OUTPUT);
    pinMode(DEV_1_PIN, OUTPUT);
}

void serial_init(uint32_t baud_rate = 9600){
  Serial.begin(baud_rate);
  Serial.println(("\n\nHello!\nFrom NGXXFUS!"));
}

void msg2ser(String msg = ""){
    Serial.println(msg);
}

void msg2ser(String msg0, String msg1){
    Serial.print(msg0);
    Serial.println(msg1);
}

void msg2ser(String msg0, String msg1, String msg2){
    Serial.print(msg0);
    Serial.print(msg1);
    Serial.println(msg2);
}

#include <DHT.h>
#define DHT_DAT_PIN 5
#define DHTTYPE DHT11

DHT dht(DHT_DAT_PIN, DHTTYPE);

struct SENSOR_DATA{
    float temp, humid;
    SENSOR_DATA( float temp = 0.0, float humid = 0.0){
        this->temp = temp;
        this->humid = humid;
    }
};
bool is_data_corrupted(SENSOR_DATA data){
    if( isnan(data.temp) || isnan(data.humid)){
        return true;
    }
    return false;
}

SENSOR_DATA dht11_read(uint16_t delay_ms = 2000){
    delay(delay_ms);
    return SENSOR_DATA(dht.readTemperature(), dht.readHumidity());
}

#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#define EMAIL "ngxxfus@lab3-itfa.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"

#include "FirebaseESP32.h"

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
    do Firebase.begin(&config, &auth);
    while(!Firebase.ready());
    msg2ser("Connected to Firebase!");
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
    Firebase.getString(firebaseData, "Temp");
    return true;
}

void setup(){
	gpio_init();
	set_indicator(0);
	serial_init(115200);
	dht.begin();
	wifi_init();
	firebase_init();
}

void warning(bool activate = true){
	if(activate == false){
		delay(1000);
		return;
	}
	digitalWrite(DEV_0_PIN, 0); delay(100);
	digitalWrite(DEV_0_PIN, 1); delay(100);
	digitalWrite(DEV_0_PIN, 0); delay(100);
	digitalWrite(DEV_0_PIN, 1); delay(100);
	digitalWrite(DEV_0_PIN, 0); delay(100);
	digitalWrite(DEV_0_PIN, 1); delay(100);
	digitalWrite(DEV_0_PIN, 0); delay(100);
	digitalWrite(DEV_0_PIN, 1); delay(100);
	digitalWrite(DEV_0_PIN, 0); delay(100);
	digitalWrite(DEV_0_PIN, 1); delay(100);
	digitalWrite(DEV_0_PIN, 0);
}

void loop(){
	set_indicator(0);
	SENSOR_DATA dat = dht11_read(2000);
	if(is_data_corrupted(dat)) return;
	warning(dat.temp > 60);
	(10 <= dat.temp && dat.temp <= 50 && dat.humid < 70)?
	digitalWrite(DEV_0_PIN, 1):digitalWrite(DEV_0_PIN, 0);
	firebase_upload(dat);
}