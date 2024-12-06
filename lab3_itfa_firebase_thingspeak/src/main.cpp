#include "pin_def.h"
#include "serial_def.h"
#include "dht_def.h"
#include "firebase_thingspeak_def.h"
#include "TFT_176x220.h"

void Hello(){
    tft.drawGFXText(3, 15, "Hello ;>", 0x46f0);
    tft.drawGFXText(3, 30, "from ngxxfus!", 0x46f0);
    delay(2000);
}

void setup(){
    // Gọi các hàm thiết lập cho các mục đích 
    // Đã được định nghĩa trước
    serial_init(115200);
    gpio_init();
    tft_initial();
    wifi_init();
    firebase_init();
    thingspeak_init();
}

void loop(){
    // Tạo một đối tượng kiểu SENSOR_DATA
    // Để lưu giá trị đọc được từ cảm biến
    // Sau đó gán giá trị được được từ cảm biến
    // Cho đối tượng đó
    SENSOR_DATA data = dht_read(3000);
    // In giá trị T và H qua Serial
    msg2ser("Temp :", (String)data.temp);
    msg2ser("Temp :", (String)data.humid);
    // Nếu dữ liệu lỗi, lặp lại bước đọc dữ liệu
    if(is_data_corrupted(data)){
        //Thông báo lỗi
        set_indicator(0x1);
        return;
    }
    // Gọi phương thức gởi dữ liệu lên Firebase
    firebase_upload(data);
    // Gọi phương thức gởi dữ liệu lên ThingSpeak
    thingspeak_upload(data);
    // Tạo đối tượn DEV để nhận dữ liệu trạng thái 
    // đọc được từ Firebase và dữ liệu trạng thái
    // vào dev.
    DEV dev = firebase_download();
    // thiết lập trạng thái thiết bị
    digitalWrite(DEV_0_PIN, dev.__0);
    digitalWrite(DEV_1_PIN, dev.__1);
}

