#include <Arduino.h>
#include "pin_def.h"
#include "serial_def.h"
#include "dht_def.h"
#include "tft22_def.h"

void setup(){
    io_pin::init();
    serial_com::init(115200);
    dht_sensor::init();
    tft_lcd::init();
}

void loop(){
    float t, h;
    dht_sensor::read(t, h);
    if(dht_sensor::corrupted(t, h)) return;
    tft_lcd::tft.clear();
    tft_lcd::println(0, "Temp(oC):");
    tft_lcd::println(1, t);
    tft_lcd::println(2, "Humid(%):");
    tft_lcd::println(3, h);
}