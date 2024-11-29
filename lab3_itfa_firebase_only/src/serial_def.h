#ifndef _SERIAL_DEF_H_
#define _SERIAL_DEF_H_
#include <Arduino.h>

void serial_init(uint32_t baud_rate = 9600){
  Serial.begin(baud_rate);
  Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
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


#endif