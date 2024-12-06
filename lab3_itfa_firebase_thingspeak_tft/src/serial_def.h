#ifndef _SERIAL_DEF_H_
#define _SERIAL_DEF_H_
#include <Arduino.h>

// Hàm khởi tạo giao tiếp Serial
void serial_init(uint32_t baud_rate = 9600){
  Serial.begin(baud_rate);
  Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
}

// Định nghĩa phương thức gởi dữ liệu qua Serial
void msg2ser(String msg = ""){
    Serial.println(msg);
}

// Nạp chồng hàm
void msg2ser(String msg0, String msg1){
    Serial.print(msg0);
    Serial.println(msg1);
}

// Nạp chồng hàm
void msg2ser(String msg0, String msg1, String msg2){
    Serial.print(msg0);
    Serial.print(msg1);
    Serial.println(msg2);
}


#endif