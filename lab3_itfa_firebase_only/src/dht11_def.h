#ifndef _DHT11_DEF_H_
#define _DHT11_DEF_H_

#include <Arduino.h>

#include <DHT.h>
#define DHT_DAT_PIN 5
#define DHTTYPE DHT11

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
        return true;
    }
    return false;
}

SENSOR_DATA dht11_read(uint16_t delay_ms = 2000){
    delay(delay_ms);
    return SENSOR_DATA(dht.readHumidity(), dht.readTemperature());
}

#endif