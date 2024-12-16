#include <Arduino.h>
#include "pin_def.h"
#include "tft22_extended.h"
#include "image.h"

void setup(){
    io_pin::init();
    tft_lcd::init();
    tft_lcd::drawImage(0, 70, _176x220_bitmap, 0, 40);
}

void loop(){
    io_pin::set_indicator(0x2);
    delay(1000);
}