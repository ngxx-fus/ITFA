#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include <DHT.h>

#define DHTTYPE DHT11
#define DHT_DAT_PIN 32
#define INDICATOR_LED_PIN 26

#if defined ESP32
#pragma warning("Using built-in SPI for ESP32!")
#define TFT_RST 21 
#define TFT_RS  22 
#define TFT_CLK 18  
#define TFT_SDI 23  
#define TFT_CS  5  
#define TFT_LED 0   
SPIClass vspi(VSPI);
#define TFT_BRIGHTNESS 200 
#endif
DHT dht(DHT_DAT_PIN, DHTTYPE);
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);


// Codes:
// 0x0: Read data from sensor
// 0x1: DHT Received data corrupted
// 0x2: WiFi error
// 0x3: Database connection error
// 0x4: Speed direction error 
void Set_Indicator_Flag(int err_code = 0){
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
    digitalWrite(INDICATOR_LED_PIN, HIGH); delay(100);
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
  }
}


void Initial_GPIO_Pin(){
    pinMode(INDICATOR_LED_PIN, OUTPUT);
}

void Initial_Serial(){
  Serial.begin(115200);
  Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
}
