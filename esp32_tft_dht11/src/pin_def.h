#ifndef _PIN_DEF_H_
#define _PIN_DEF_H_

#include <Arduino.h>

#pragma message(                                              \
    "\n--------***--------"                                   \
    "\nHello from ngxxfus,"                                   \
    "\n    This header file was made for quick blink LED,"    \
    "\nsplit all setup command into modules, this module for" \
    "\nset-up all things related to GPIO (I/O devices only!).")

#define INDICATOR_LED 25
#define DEV_0 26
#define DEV_1 27

namespace io_pin
{
    // Codes:
    // 0x0: Normal operation :v
    // 0x1: DHT Received data corrupted
    // 0x2: WiFi error
    // 0x3: Database connection error
    // 0x4: Speed direction error
    void set_indicator(int err_code = 0)
    {
        // Blink led to noti error
        switch (err_code)
        {
        case 0x0:
            err_code = 1;
            break;
        case 0x1:
            err_code = 2;
            break;
        case 0x2:
            err_code = 3;
            break;
        case 0x3:
            err_code = 4;
            break;
        case 0x4:
            err_code = 5;
            break;
        default:
            err_code = 0;
        }
        while (err_code--)
        {
            digitalWrite(INDICATOR_LED, LOW);
            delay(50);
            digitalWrite(INDICATOR_LED, HIGH);
            delay(200);
            digitalWrite(INDICATOR_LED, LOW);
            delay(50);
        }
    }

    void init()
    {
        pinMode(INDICATOR_LED, OUTPUT);
        pinMode(DEV_0, OUTPUT);
        pinMode(DEV_1, OUTPUT);
        io_pin::set_indicator(0x0);
    }
}
#endif