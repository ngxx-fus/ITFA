#ifndef _LCD_176X220_H_
#define _LCD_176X220_H_

#pragma message("\n\
\
Hello from ngxxfus,\n\
    This header file have packaged again from TFT_22_ILI9225 lib. \
For add some notes and functions :v.\n\
\
The dependencies (PlatformIO.ini):\n\
    lib_deps = \n\
        adafruit/DHT sensor library@^1.4.6\n\
        adafruit/Adafruit Unified Sensor@^1.1.14\n\
        SPI\n\
        nkawu/TFT 22 ILI9225@^1.4.5\n\
")

#pragma message(" \n\
Connections:\n\
    LCD-TFT (slave)     ESP32 (master)\n\
    VCC                 VIN (5V)\n\
    GND                 GND\n\
    CLK                 HSPI-CLK  (GPIO14)\n\
    SDA                 HSPI-MOSI (GPIO13)\n\
    RS                  (any GPIO)\n\
    RST                 (any GPIO)\n\
    CS                  HSPI-CS (GPIO15)\n\
")

enum lines_enum{
    line0 = 15,
    line1 = 30,
    line2 = 45,
    line3 = 60,
    line4 = 75,
    line5 = 90,
    line6 = 105,
    line7 = 120,
    line8 = 135,
    line9 = 150,
    line10 = 165,
    line11 = 180,
};

#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include <../fonts/FreeSans12pt7b.h>
#include <../fonts/FreeSans24pt7b.h>
#include <../fonts/FreeMono9pt7b.h>

#define TFT_RST 4 
#define TFT_RS  2 
#define TFT_CS  15  
#define TFT_LED 0   
#define TFT_BRIGHTNESS 200 
SPIClass hspi(HSPI);
TFT_22_ILI9225 tft = TFT_22_ILI9225(
  TFT_RST, 
  TFT_RS, 
  TFT_CS, 
  TFT_LED, 
  TFT_BRIGHTNESS
);

int16_t w = 5, h = 9;

void tft_initial(){
    hspi.begin();
    tft.begin(hspi);
    tft.setGFXFont(&FreeMono9pt7b);
    tft.setBackgroundColor(0);
    tft.clear();
}


#endif