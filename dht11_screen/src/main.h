#include <DHT.h>
#include "TFT_176x220.h"

#define INDICATOR_LED_PIN 25

#define DHTTYPE DHT11
#define DHT_DAT_PIN 5
DHT dht(DHT_DAT_PIN, DHTTYPE);


// Codes:
// 0x0: Read data from sensor
// 0x1: DHT Received data corrupted
// 0x2: WiFi error
// 0x3: Database connection error
// 0x4: Speed direction error 
void Set_Indicator_Flag(int err_code = 0){
  // Blink led to noti error
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
    digitalWrite(INDICATOR_LED_PIN, HIGH); delay(100);
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
  }
}


void Initial_GPIO_Pin(){
    pinMode(INDICATOR_LED_PIN, OUTPUT);
}

void Initial_Serial(){
  Serial.begin(115200);
  Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
}

void Initial_DHT(){
  dht.begin();
}

void Update_Sensor_Data(float* ph = nullptr, float* pt = nullptr){
    Serial.println();
    Set_Indicator_Flag(0x0);
    delay(4000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    // Check read data
    if( isnan(t) || isnan(h) ){
            // Send Error msg to serial
            Serial.println("DHT11 - E: Corrupted data!");
            Set_Indicator_Flag(0x1);
        }else{
        // Send Temp + Humid data to serial
        Serial.print("Temp: ");
        Serial.println(t);
        Serial.print("Humid: ");
        Serial.println(h);
        // update temp, humid into ptr
        (ph==nullptr)?(0):(*ph=h);
        (pt==nullptr)?(0):(*pt=t);
    }
}
