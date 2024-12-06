#include "main.h"
#define blank_line "               "

#define clearline(Line) tft.drawGFXText(3, Line, blank_line, 0x0)
#define drawline(Line, Text, Color) tft.drawGFXText(3, Line, (Text), Color)

void Hello(){
    tft.drawGFXText(3, 15, "Hello ;>", 0x46f0);
    tft.drawGFXText(3, 30, "from ngxxfus!", 0x46f0);
    delay(2000);
}

void setup() {
    Initial_Serial();
    Initial_GPIO_Pin();
    Initial_DHT();
    Initial_TFT();
    Hello();
}

void loop() {
    Set_Indicator_Flag(0x0);
    float h = 0, t = 0;
    Update_Sensor_Data(&h, &t);
    tft.clear();
    drawline(line0, String("Connections: "), 0x46f0);
    drawline(line1, String(" Firebase:  OK"), 0x46f0);
    drawline(line2, String(" ThingSpeak:OK"), 0x46f0);
    drawline(line3, String("Env info:"), 0x46f0);
    drawline(line4, String(" Temp:  ")+String(t), 0x46f0);
    drawline(line5, String(" Humid: ")+String(h), 0x46f0);
    drawline(line0, String("Connections: "), 0x46f0);

    delay(5000);
}

