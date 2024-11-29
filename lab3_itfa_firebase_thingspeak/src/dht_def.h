#ifndef _DHT_DEF_H_
#define _DHT_DEF_H_

#include <Arduino.h>

#include <DHT.h>
#define DHT_DAT_PIN 5
#define DHTTYPE DHT22

DHT dht(DHT_DAT_PIN, DHTTYPE);

struct SENSOR_DATA{
    float temp, humid;
    SENSOR_DATA( float temp = 0.0, float humid = 0.0){
        this->temp = temp;
        this->humid = humid;
    }
};

bool is_data_corrupted(SENSOR_DATA data){
    if( isnan(data.temp) || isnan(data.humid)){
        set_indicator(0x1);
        return true;
    }
    return false;
}

SENSOR_DATA dht_read(uint16_t delay_ms = 2000){
    delay(delay_ms);
    set_indicator(0x0);
    return SENSOR_DATA(dht.readHumidity(), dht.readTemperature());
}

#endif