#ifndef _TFT22_H_
#define _TFT22_H_

#pragma message("\
\n--------***--------\
\nHello from ngxxfus,\n\
    This header file have packaged again from TFT_22_ILI9225 lib. \
For add some notes and functions :v.\n\
\
The dependencies (PlatformIO.ini):\n\
    lib_deps = \n\
        adafruit/DHT sensor library@^1.4.6\n\
        adafruit/Adafruit Unified Sensor@^1.1.14\n\
        SPI\n\
        nkawu/TFT 22 ILI9225@^1.4.5\n\
" \
                "The connections:\n\
    LCD-TFT (slave)     ESP32 (master)\n\
    VCC                 VIN (5V)\n\
    GND                 GND\n\
    CLK                 HSPI-CLK  (GPIO14)\n\
    SDA                 HSPI-MOSI (GPIO13)\n\
    RS                  (any GPIO)\n\
    RST                 (any GPIO)\n\
    CS                  HSPI-CS (GPIO15)\n"\
)


#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include <../fonts/FreeSans12pt7b.h>
#include <../fonts/FreeSans24pt7b.h>
#include <../fonts/FreeMono9pt7b.h>

#define TFT_RST 4
#define TFT_RS 2
#define TFT_CS 15
#define TFT_LED 0
#define TFT_BRIGHTNESS 200

namespace tft_lcd{
    SPIClass hspi(HSPI);
    TFT_22_ILI9225 tft = TFT_22_ILI9225(
        TFT_RST,
        TFT_RS,
        TFT_CS,
        TFT_LED,
        TFT_BRIGHTNESS);

    //Initial hspi, tft
    void init()
    {
        hspi.begin();
        tft.begin(hspi);
        tft.setGFXFont(&FreeMono9pt7b);
        tft.setBackgroundColor(0);
        tft.clear();
        tft.setOrientation(2);
    }

    //Print msg into a row in tft screen.
    //Note: 
    //+ The limit range of row: [0, 180/line_height]
    //+ The limit of msg size: 16 characters
    //+ If line_height is too small, the lines can be overlapped each other!
    template<class T>
    void println(
        uint16_t row, 
        T msg, 
        uint16_t text_color = 0x46f0,
        uint16_t line_height = 0x000f
    )
    {
        tft.drawGFXText(0, (row+1)*line_height, String(msg), text_color);
    }
}

#endif