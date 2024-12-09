#ifndef _TFT22_H_
#define _TFT22_H_

#pragma message("\
\n--------***--------\
\nHello from ngxxfus,\n\
    This header file have packaged again from TFT_22_ILI9225 \nlib. \
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
    void init(
        uint8_t Orientation = 2,
        uint16_t BackgroundColor = 0x0
    ){
        hspi.begin();
        tft.begin(hspi);
        tft.setGFXFont(&FreeMono9pt7b);
        tft.setBackgroundColor(BackgroundColor);
        tft.clear();
        tft.setOrientation(Orientation);
    }

    //Print msg into a line in tft screen.
    //Note: 
    //+ The limit range of row: [0, 180/line_height]
    //+ The limit of msg size: 16 characters
    //+ If line_height is too small, the lines can be overlapped each other!
    template<class T>
    void println(
        uint16_t line,
        T msg, 
        uint16_t text_color = 0x46f0,
        uint16_t line_height = 0x000f
    )
    {
        tft.drawGFXText(0, (line+1)*line_height, String(msg), text_color);
    }

    // Draw an image onto TFT 2.2" screen.
    // X : 0->175 (column)
    // y : 0->219 (row)
    // Maxsize of image: wxh=176x220
    // No. of elements of image >= img_w*img_h
    // This function draw image from top-left -> botom-right
    // in other words: (x, y) -> (x+img_w, y+img_h)
    // Image to 16bit array image: https://javl.github.io/image2cpp/
    void drawImage(
        uint16_t X, uint16_t Y, 
        uint16_t* image, 
        uint16_t img_w = 176, uint16_t img_h = 220
    ){
        if( X >= tft.maxX() || Y >= tft.maxY() ||\
            img_w > 176     || img_h > 220
        ) return; 

        for(uint16_t x = 0; x < img_w-X; ++x){
            for(uint16_t y = 0; y < img_h-Y; ++y){
                tft_lcd::tft.drawPixel(X+x, Y+y, image[(y)*img_w+(x)]);
            }
        }
    }

    // Draw an black rec onto TFT 2.2" screen.
    // Note:
    // - line         : 0 ->... (row)
    // - line_height  : 0->...
    // - line+line_height < 220
    void clearln(
        uint16_t line, 
        uint16_t line_height = 0x000f
    ){
        for(uint16_t x = 0; x < 176; ++x)
            for(uint16_t y = (line+1)*line_height+1; y > line*line_height+1; --y)
                tft.drawPixel(x, y, 0x0);
    }

    inline void clear(){
        tft.clear();
    }
}

#endif