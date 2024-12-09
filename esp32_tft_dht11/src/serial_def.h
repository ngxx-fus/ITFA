#ifndef _SERIAL_DEF_H_
#define _SERIAL_DEF_H_
#include <Arduino.h>

#pragma message(                                                    \
    "\n--------***--------"                                         \
    "\nHello from ngxxfus,"                                         \
    "\n    This header file has been packaged again. For add some " \
    "\nnotes and functions :v. If you got some errors... Example:"  \
    "\nYou have received a lot of \'weird\' char in your Serial-"   \
    "\nmonitor, you need check the baud-rate (by default, it's"     \
    "\n9600).")

namespace serial_com
{

    void init(uint32_t baud_rate = 9600)
    {
        Serial.begin(baud_rate);
        Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
    }

    template <class T>
    void sendmsg(T msg)
    {
        Serial.println(String(msg));
    }

    template <class T, class... Targs>
    void sendmsg(T msg, Targs... msgs)
    {
        Serial.print(msg);
        sendmsg(msgs...);
    }

}
#endif