#include "main.h"
 
void TFT_Screen(){
    // Serial.println("Called: TFT_Screen");
    Set_Indicator_Flag();
    tft.clear();
    tft.fillCircle(50,50 , 15, 0x3452);
    tft.drawTriangle(30,30, 130,0, 0,130, 0xFFFF);
}

void Update_Sensor_Data(){
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
    }
}

void setup() {
    Initial_Serial();
    Initial_GPIO_Pin();
    vspi.begin();
    tft.begin(vspi);
    tft.begin(vspi);
}

void loop() {
    TFT_Screen();
    // delay(1000);
}

