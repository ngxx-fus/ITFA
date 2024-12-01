#ifndef _DHT11_DEF_H_
#define _DHT11_DEF_H_

#include <Arduino.h>

#include <DHT.h>
#define DHT_DAT_PIN 5
#define DHTTYPE DHT11

DHT dht(DHT_DAT_PIN, DHTTYPE);

bool dht11_read(float& temp, float& humid){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if( isnan(h) || isnan(t)){
        return false;
    }
    temp = t, humid = h;
    return true;
}

#endif