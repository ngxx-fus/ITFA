#include "Arduino.h"
#include "pin_def.h"
#include "serial_def.h"
#include "dht_def.h"
#include "firebase_thingspeak_def.h"
#include "TFT_176x220.h"

unsigned long lastcheck = 0;

void setup(){
    tft_initial();
    drawline(line0, String("Connections: "), 0x46f0);
    serial_init(115200);
    drawline(line1, String(" Serial: OK"), 0x46f0);
    gpio_init();
    drawline(line2, String(" GPIO: OK"), 0x46f0);
    wifi_init();
    drawline(line3, String(" Wi-Fi: OK"), 0x46f0);
    firebase_init(); 
    drawline(line4, String(" Firebase: OK"), 0x46f0);
    thingspeak_init();
    drawline(line5, String(" ThingSpeak:OK"), 0x46f0);
}


void loop(){
    auto data = dht_read(1000);
    msg2ser("Temp :", (String)data.temp);
    msg2ser("Humid :", (String)data.humid);
    tft.clear();
    if(is_data_corrupted(data)){
        set_indicator(0x1);
        return;
    }
    drawline(line0, String("Env info:"), 0x46f0);
    drawline(line1, String(" Temp:  ") + String(data.temp), 0x46f0);
    drawline(line2, String(" Humid: ") + String(data.humid), 0x46f0);

    drawline(line3, String("Upload info:"), 0x46f0);
    if( millis() - lastcheck > 15000UL){
        lastcheck = millis();
        firebase_upload(data)?
        drawline(line4, String(" Firebase   OK"), 0x46f0):
        drawline(line4, String(" Firebase   :<"), 0x46f0);

        thingspeak_upload(data)?
        drawline(line5, String(" ThingSpeak OK"), 0x46f0):
        drawline(line5, String(" ThingSpeak :<"), 0x46f0);
    }else{
        drawline(line4, String(" Firebase   x"), 0x46f0);
        drawline(line5, String(" ThingSpeak x"), 0x46f0);
    }

    drawline(line6, String("Download info:"), 0x46f0);
    bool dev0_state, dev1_state;
    firebase_download(&dev0_state, &dev1_state)?
    drawline(line7, String("Firebase OK"), 0x46f0):
    drawline(line7, String("Firebase :<"), 0x46f0);

    drawline(line8, String("Dev info:"), 0x46f0);
    drawline(line9, String(" DEV0: ")+String(dev0_state?"ON":"OFF"), 0x46f0);
    drawline(line10, String(" DEV1: ")+String(dev1_state?"ON":"OFF"), 0x46f0);

    digitalWrite(DEV_0_PIN, dev0_state);
    digitalWrite(DEV_1_PIN, dev1_state);
}

