#include <Arduino.h>
#include "pin_def.h"
#include "serial_def.h"
#include "dht_def.h"
#include "tft22_def.h"
#include "image.h"

void setup(){
    io_pin::init();
    serial_com::init(115200);
    dht_sensor::init();
    tft_lcd::init();
    tft_lcd::drawImage(0, 70, _176x220_bitmap, 0, 40);
    tft_lcd::println(0, "Temp(oC):");
    tft_lcd::println(2, "Humid(%):");
}

void loop(){
    io_pin::set_indicator(0x0);

    float t, h;
    dht_sensor::read(t, h);
    if(dht_sensor::corrupted(t, h)) return;

    tft_lcd::clearln(1);
    tft_lcd::println(1, t);
    tft_lcd::clearln(3);
    tft_lcd::println(3, h);
}