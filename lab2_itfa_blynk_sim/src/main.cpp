// Các thư viện WiFi services 
#include <WiFi.h>
#include <WiFiClient.h>
#include "DHT.h"
//Đầu ra trực tiếp đến Serial
#define BLYNK_PRINT Serial
// Thiết lập SSDĐ và PASSWORD Wi-Fi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PWD ""
// Thông tin về BLYNK phải được định nghĩa 
// trước khi khai báo BLYNK header (BlynkSimpleEsp32.h)
#define BLYNK_TEMPLATE_ID "TMPL6SimSzvsi"
#define BLYNK_TEMPLATE_NAME "hehe"
#define BLYNK_AUTH_TOKEN "tD898pXYEhFpqDFi_BMTHYN-Y9ZyDIDt"
// Khai báo BLYNK header
#include <BlynkSimpleEsp32.h>

// Định nghĩa các chân
#define DHT_DAT_PIN 5
// Các loại cảm biến DHT cụ thể DHT11, DHT22)
#define DHTTYPE DHT22

#define LED_CTL_PIN_1 4
#define INDICATOR_LED_PIN 21
#define LED_CTL_PIN_2 18




// Tạo một đối tượng với BlynkTimer, để cập nhật dữ liệu mỗi giây
BlynkTimer timer;


// Tạo một đối tượng với DHT, để đọc dữ liệu (nhiệt độ và độ ẩm) từ DHT11
DHT dht(DHT_DAT_PIN, DHTTYPE);


// Thay đổi giá trị trong phần cứng bất cứ khi nào giá trị của pin ảo thay đổi.
BLYNK_WRITE(V1){
   int value = param.asInt();
   value? digitalWrite(LED_CTL_PIN_1, HIGH) : digitalWrite(LED_CTL_PIN_1, LOW);
}


// Thay đổi giá trị trong phần cứng bất cứ khi nào giá trị của pin ảo thay đổi.
BLYNK_WRITE(V3){
   int value = param.asInt();
   value? digitalWrite(LED_CTL_PIN_2, HIGH) : digitalWrite(LED_CTL_PIN_2, LOW);
}


// Để xử lý dữ liệu từ DHT và quyết định gửi hoặc KHÔNG gửi lại cho BLYNK.
void Send_Back_Sensor_Data()
{
   // Bật đèn INDICATOR để thông báo khi quá trình đọc bắt đầu
   digitalWrite(INDICATOR_LED_PIN, HIGH);
  //Đợi một vài giây trong quá trình delay.
   delay(4000);
   // Đọc nhiệt độ và độ ẩm mất 250 mili giây!
   // Các chỉ số cảm biến cũng mất đến 2 giây để đọc độ ẩm.
   float h = dht.readHumidity();
   // Đọc nhiệt độ bằng độ C (mặc định)
   float t = dht.readTemperature();
   if( isnan(t) || isnan(h)){
       //Khi nhận dữ liệu dễ bị hỏng
       //In thông báo lên Serial
         Serial.println("DHT11 - E: Corrupted data!");
         digitalWrite(INDICATOR_LED_PIN, LOW);
         delay(100);
         digitalWrite(INDICATOR_LED_PIN, HIGH);
         delay(100);
         digitalWrite(INDICATOR_LED_PIN, LOW);
         delay(100);
         digitalWrite(INDICATOR_LED_PIN, HIGH);
      }else{
       // In dữ liệu lên Serial
       Serial.println("Temp: ");
       Serial.println(t);
       Serial.println("Humid: ");
       Serial.println(h);
       // Gửi lại Blynk
       Blynk.virtualWrite(V2, h);
       Blynk.virtualWrite(V0, t);
   }
   // Tắt đèn INDICATOR để thông báo khi quá trình đọc dừng lại
   digitalWrite(INDICATOR_LED_PIN, LOW);
}


void setup() {
   // Bắt đầu Serial với tốc độ truyền=9600 baund/giây
   Serial.begin(11520);
   // Gửi một tin nhắn
   Serial.println(("\n\nHello!\n From MEOW GROUP!"));
   // Thiết lâp LED_CTL_PIN_1 là OUTPUT
   pinMode(LED_CTL_PIN_1, OUTPUT);
   // Thiết lập INDICATOR_LED_PIN là OUTPUT
   pinMode(INDICATOR_LED_PIN, OUTPUT);
   pinMode(LED_CTL_PIN_2, OUTPUT);
   // Bắt đầu DHT để đọc dữ liệu
   dht.begin();
   // Bắt đầu BLYNK để sẵn sàng làm việc (gửi hoặc nhận dữ liệu)
   Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PWD);
   // Thiết lập một hàm để gọi mỗi giây
   // Bộ hẹn giờ sẽ đợi trong 4 giây
   //Gọi Send_Back_Sensor_Data đầu tiên.
   timer.setInterval(1000, Send_Back_Sensor_Data);
}


void loop(){
   // Đồng bộ pin ảo V1, V3 (Điều khiển LED)
   Blynk.run();
   Blynk.syncVirtual(V1);
   Blynk.syncVirtual(V3);
   // Chạy bộ đếm thời gian Blynk ans
   delay(1000);
   timer.run();
}
