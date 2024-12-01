#include "pin_def.h"
#include "serial_def.h"
#include "dht11_def.h"
#include "firebase_def.h"

void setup(){
    serial_init(115200);
    gpio_init();
    wifi_init();
    firebase_init();
}

void loop(){
    SENSOR_DATA data = dht11_read();
    msg2ser("Temp :", (String)data.temp);
    msg2ser("Temp :", (String)data.humid);
    if(is_data_corrupted(data)){
        set_indicator(0x1);
        return;
    }
    firebase_upload(data);
}

