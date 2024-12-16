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
    #define IO_KEY       "aio_HQlh01rjsdLN8UuaSz8SGP0tktja"
    #include <AdafruitIO.h>
    #include <AdafruitIO_WiFi.h> 

    AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASSWORD); 

    #define DEV_0_PIN 12
    #define DEV_1_PIN 13


    AdafruitIO_Feed *HUMID = io.feed("HUMID");
    AdafruitIO_Feed *TEMP = io.feed("TEMP");

    void setup() {
        Serial.begin(115200);
        msg2ser("\nHello from ESP32!\n");

        msg2ser("GPIO: Setting-up ...");
        // pinMode(INDICATOR_LED_PIN, OUTPUT);
        pinMode(DEV_0_PIN, OUTPUT);
        pinMode(DEV_1_PIN, OUTPUT);
        msg2ser("GPIO: OK!\n");

        msg2ser("Adafruit: Connecting...");
        io.connect();
        do{
            msg2ser("Adafruit: " + String(io.statusText()));
            msg2ser("Adafruit: re-trying...");
            io.connect();
            delay(1000);
        }while( io.status() != AIO_CONNECTED);

        msg2ser("Adafruit: OK!\n");

        msg2ser("\nAll setup are done!\n");
    }

    void warning(bool activate = true){
        if(activate == false){
            delay(1000);
            return;
        }
        digitalWrite(DEV_0_PIN, 0); delay(100);
        digitalWrite(DEV_0_PIN, 1); delay(100);
        digitalWrite(DEV_0_PIN, 0); delay(100);
        digitalWrite(DEV_0_PIN, 1); delay(100);
        digitalWrite(DEV_0_PIN, 0); delay(100);
        digitalWrite(DEV_0_PIN, 1); delay(100);
        digitalWrite(DEV_0_PIN, 0); delay(100);
        digitalWrite(DEV_0_PIN, 1); delay(100);
        digitalWrite(DEV_0_PIN, 0); delay(100);
        digitalWrite(DEV_0_PIN, 1); delay(100);
        digitalWrite(DEV_0_PIN, 0);
    }

    void loop() {
        io.run();
        
        float t, h;
        
        delay(5000);
        
        h = dht.readHumidity(), t = dht.readTemperature();
        if( isnan(t) || isnan(h) ) return;
        msg2ser("Temp: " + String(t) + String(" oC"));
        msg2ser("Humid: " + String(h) + String(" %"));

        HUMID->save(h); TEMP->save(t);

        warning(t > 60);
        if(10 <= t && t <= 50 && h <= 70)
            digitalWrite(DEV_1_PIN, 1);
        else
            digitalWrite(DEV_1_PIN, 0);

    }
