#ifndef _DHT_DEF_H_
#define _DHT_DEF_H_

#include <Arduino.h>
#include "pin_def.h"

// Thư viện DHT dùng để đọc cảm biến
#include <DHT.h>
// Định nghĩa macro cho chân nhận dữ liệu từ cảm biến
#define DHT_DAT_PIN 5
// Định nghĩa macro cho kiểu DHT
#define DHTTYPE DHT11

// Tạo đối tượng DHT
DHT dht(DHT_DAT_PIN, DHTTYPE);

// Định nghĩa STRUCT sensor_data để đóng gói dữ liệu trả về
struct SENSOR_DATA{
    float temp, humid;
};

// Định nghĩa hàm kiểm tra dữ liệu lỗi
bool is_data_corrupted(SENSOR_DATA data){
    // Nếu dữ liệu is nan (Not a Number) thì trả về True
    if( isnan(data.temp) || isnan(data.humid)){
        set_indicator(0x1);
        return true;
    }
    return false;
}

// Định nghĩa hàm đọc dữ liệu từ cảm biến DHT 
// Trả về kiểu dữ liệu nhận được từ DHT được đóng gói
SENSOR_DATA dht_read(uint16_t delay_ms = 2000){
    // Chờ một khoảng thời gian để cảm biến đo
    delay(delay_ms);
    // Nháy LED để báo hiệu quá trình đọc dữ liệu từ cảm biến DHT
    set_indicator(0x0);
    // Trả về kiểu dữ liệu được đóng gói dạng SENSOR_DATA
    return {dht.readHumidity(), dht.readTemperature()};
}

#endif