#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "DHT.h"

#define FIREBASE_HOST "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "SftGzo6EJMJqpTa8i8DphVnYxwfdugy23FuNlcRE"

#define DHTTYPE DHT11
#define DHT_DAT_PIN 21
DHT dht(DHT_DAT_PIN, DHTTYPE);

#define LED_CTL_PIN_1 21
#define INDICATOR_LED_PIN 23
#define LED_CTL_PIN_2 19

void Sync_Sensor_Data()
{
  digitalWrite(INDICATOR_LED_PIN, HIGH);
  delay(4000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if( isnan(t) || isnan(h)){
        Serial.println("DHT11 - E: Corrupted data!");
        digitalWrite(INDICATOR_LED_PIN, LOW);
        delay(100);
        digitalWrite(INDICATOR_LED_PIN, HIGH);
        delay(100);
        digitalWrite(INDICATOR_LED_PIN, LOW);
        delay(100);
        digitalWrite(INDICATOR_LED_PIN, HIGH);
      }else{
      Serial.println("Temp: ");
      Serial.println(t);
      Serial.println("Humid: ");
      Serial.println(h);
  }
  // Tắt đèn INDICATOR để thông báo khi quá trình đọc dừng lại
  digitalWrite(INDICATOR_LED_PIN, LOW);
}

void setup(){
  Serial.begin(9600);
  Serial.println(("\n\nHello!\n From MEOW GROUP!"));
  pinMode(LED_CTL_PIN_1, OUTPUT);
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  pinMode(LED_CTL_PIN_2, OUTPUT);
  dht.begin();
  //
}

void loop(){
  Sync_Sensor_Data();
  delay(1000);
}