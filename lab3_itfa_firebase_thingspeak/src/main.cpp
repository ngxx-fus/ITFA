#include "pin_def.h"
#include "serial_def.h"
#include "dht_def.h"
#include "firebase_thingspeak_def.h"
void setup(){
    serial_init(115200);
    gpio_init();
    wifi_init();
    firebase_init();
    thingspeak_init();
}

void loop(){
    SENSOR_DATA data = dht_read(3000);
    msg2ser("Temp :", (String)data.temp);
    msg2ser("Temp :", (String)data.humid);
    if(is_data_corrupted(data)){
        set_indicator(0x1);
        return;
    }
    firebase_upload(data);
    thingspeak_upload(data);
    DEV dev = firebase_download();
    digitalWrite(DEV_0_PIN, dev.__0);
    digitalWrite(DEV_1_PIN, dev.__1);
}

