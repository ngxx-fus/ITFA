/*
*   This file provide you how to prevent delay if (w/o interrupt).
    In this file, i'm using milis() to handle when i read the sensor instead of
    delay all process. Yeah, it's not the good solution, but simple :> kkkkkk
*/

    #include <Arduino.h>

    #define msg2ser(msg) Serial.println(msg)

    #include <DHT.h>
    #define DHT_DAT_PIN 5
    #define DHTTYPE DHT22
    DHT dht(DHT_DAT_PIN, DHTTYPE);

    #define WIFI_SSID "Wokwi-GUEST"
    #define WIFI_PASSWORD ""
    #include "WiFi.h"

    #define IO_USERNAME  "ngxxfus3204"
    #define IO_KEY       "aio_Tibv38mz3bXI2znP9vET3oexfbMQ"
    #include <AdafruitIO.h>
    #include <AdafruitIO_WiFi.h> 

    AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASSWORD); 

    #define INDICATOR_LED_PIN 19
    #define DEV_0_PIN 12
    #define DEV_1_PIN 13

    unsigned long lastcheck_t = 0;

    void run_indicator(){
        digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
        digitalWrite(INDICATOR_LED_PIN, HIGH); delay(200);
        digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
    }


    AdafruitIO_Feed *DEV0 = io.feed("DEV0");
    AdafruitIO_Feed *DEV1 = io.feed("DEV1");
    AdafruitIO_Feed *HUMID = io.feed("HUMID");
    AdafruitIO_Feed *TEMP = io.feed("TEMP");

    void OnMessageHandle(AdafruitIO_Data *data){
        digitalWrite(DEV_0_PIN, data->toPinLevel());
    }

    void setup() {
        Serial.begin(115200);
        msg2ser("\nHello from ESP32!\n");

        msg2ser("GPIO: Setting-up ...");
        pinMode(INDICATOR_LED_PIN, OUTPUT);
        pinMode(DEV_0_PIN, OUTPUT);
        pinMode(DEV_1_PIN, OUTPUT);
        msg2ser("GPIO: OK!\n");

        msg2ser("Adafruit: Connecting...");
        io.connect();
        while( io.status() != AIO_CONNECTED){
            msg2ser("Adafruit: " + String(io.statusText()));
            msg2ser("Adafruit: re-trying...");
            io.connect();
            delay(1000);
        }

        msg2ser("Adafruit: Setting-up handleMsg...\n");

        DEV0->get();
        DEV0->onMessage([](AdafruitIO_Data *data){
                digitalWrite(DEV_0_PIN, data->toPinLevel());
        });

        DEV1->get();
        DEV1->onMessage([](AdafruitIO_Data *data){
                digitalWrite(DEV_1_PIN, data->toPinLevel());
        });

        msg2ser("Adafruit: OK!\n");

        msg2ser("\nAll setup are done!\n");
    }



    void loop() {
        run_indicator();
        io.run();
        
        float t, h;
        if(millis() - lastcheck_t >= 5000UL){
            lastcheck_t = millis(); 
            h = dht.readHumidity(), t = dht.readTemperature();
            if( isnan(t) || isnan(h) ) return;
            HUMID->save(h); TEMP->save(t);
            msg2ser("Temp: "+String(t)); msg2ser("Humid: "+String(h));
        }
    }
