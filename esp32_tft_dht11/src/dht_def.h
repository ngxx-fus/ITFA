#ifndef _DHT_DEF_H_
#define _DHT_DEF_H_

#include <Arduino.h>

#if !defined(string_of) && !defined(value_of)
#define string_of(x) #x
#define value_of(x) string_of(x)
#endif

#ifdef _PIN_DEF_H_
#include "pin_def.h"
#ifndef INDICATOR_EXISTED
#define INDICATOR_EXISTED true
#endif
#else
#define INDICATOR_EXISTED false
#endif

#ifdef _SERIAL_DEF_H_
#include "serial_def.h"
#ifndef STATUS_LOG
#define STATUS_LOG true
#endif
#else
#define STATUS_LOG false
#endif

#include <DHT.h>
#define DHT_SDA 5
#define DHT_TYPE DHT11

#pragma message(                                                 \
    "\n--------***--------"                                      \
    "\nHello from ngxxfus,"                                      \
    "\n    This header file has been packaged again from DHT.h"  \
    "\nlib. For add some notes and functions :v. You need check" \
    "\nsome dependencies and definitions (dht-type dht-sda-pin)" \
    "\nbefore panikkkkkkkkkk!"                                   \
                                                                 \
    "\nThe dependencies (PlatformIO.ini):"                       \
    "\n    lib_deps = "                                          \
    "\n        adafruit/DHT sensor library@^1.4.6"               \
    "\n        adafruit/Adafruit Unified Sensor@^1.1.14"         \
                                                                 \
    "\nThe definitions:"                                         \
    "\n    #define DHT_SDA " value_of(DHT_SDA)                   \
    "\n    #define DHT_TYPE " value_of(DHT_TYPE)                 \
)

namespace dht_sensor{

    DHT dht(DHT_SDA, DHT_TYPE);

    void init()
    {
        dht.begin();
    }

    bool corrupted(const float &temperature, const float &humidity)
    {
        if (isnan(temperature) || isnan(humidity))
        {
            #if INDICATOR_EXISTED == true
                    io_pin::set_indicator(0x1);
            #endif
            #if STATUS_LOG == true
                    serial_com::sendmsg("Data is corrupted!");
            #endif
            return true;
        }
        return false;
    }

    void read(float &temperature, float &humidity, uint16_t delay_ms = 2000)
    {
        delay(delay_ms);
        temperature = dht.readTemperature(),
        humidity = dht.readHumidity();
        #if STATUS_LOG == true
            serial_com::sendmsg("Temperature: ", temperature, " oC");
            serial_com::sendmsg("Humidity: ", humidity, " %");
        #endif
    }
}
#endif