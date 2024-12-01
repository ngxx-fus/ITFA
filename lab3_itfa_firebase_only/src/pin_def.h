#ifndef _PIN_DEF_H_
#define _PIN_DEF_H_

#include <Arduino.h>

#define INDICATOR_LED_PIN 19
#define DEV_0_PIN 12
#define DEV_1_PIN 13


// Codes:
// 0x0: Read data from sensor
// 0x1: DHT Received data corrupted
// 0x2: WiFi error
// 0x3: Database connection error
// 0x4: Speed direction error 
void set_indicator(int err_code = 0){
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
    digitalWrite(INDICATOR_LED_PIN, HIGH); delay(200);
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
  }
}

void gpio_init(){
    pinMode(INDICATOR_LED_PIN, OUTPUT);
    pinMode(DEV_0_PIN, OUTPUT);
    pinMode(DEV_1_PIN, OUTPUT);
}


#endif