#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"
#define ERA_AUTH_TOKEN "a48df8f0-3073-430a-9148-b89a532c778d"

#define delta_seccond(t_i, t_f) (((t_f)-(t_i))/1000.0f)
#define in_accepted_range(mean, x) (((mean)-4<=(x)) && ((x)<=(mean)+4))

#define DHTTYPE DHT11
#define DHT_DAT_PIN 21
#include <DHT.h>
DHT dht(DHT_DAT_PIN, DHTTYPE);

#define LED_CTL_PIN_1 22
#define INDICATOR_LED_PIN 23
#define LED_CTL_PIN_2 19
#define WIND_SPEED_PIN 18
#define WIND_DIRECTION_PIN 35

#include <Arduino.h>
#include <ERa.hpp>
#include <ERa/ERaTimer.hpp>

const char ssid[] = "rm.note.11";
const char pass[] = "nGXXFUS@3204";

WiFiClient mbTcpClient;

ERA_CONNECTED() {
    ERA_LOG(ERA_PSTR("ERa"), ERA_PSTR("ERa connected!"));
}

ERA_DISCONNECTED() {
    ERA_LOG(ERA_PSTR("ERa"), ERA_PSTR("ERa disconnected!"));
}

// Codes:
// 0x0: Read data from sensor
// 0x1: DHT Received data corrupted
// 0x2: WiFi error
// 0x3: Database connection error
// 0x4: Speed direction error 
void Set_Indicator_Flag(int err_code = 0){
  // Blink led to noti error
  switch (err_code){
    case 0x0: err_code = 1; break;
    case 0x1: err_code = 2; break;
    case 0x2: err_code = 3; break;
    case 0x3: err_code = 4; break;
    case 0x4: err_code = 5; break;
    default:  err_code = 0;
  }
  while(err_code--){
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
    digitalWrite(INDICATOR_LED_PIN, HIGH); delay(100);
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(50);
  }
}

uint32_t last_t = 0;
uint32_t curr_t = 0;
uint32_t turn_count = 0;
void Wind_Speed_Count_Turn(){
    if ( digitalRead(WIND_SPEED_PIN) == LOW )
    turn_count++;
}

void Initial_GPIO_Pin(){
    pinMode(LED_CTL_PIN_1, OUTPUT);
    pinMode(INDICATOR_LED_PIN, OUTPUT);
    pinMode(LED_CTL_PIN_2, OUTPUT);
    pinMode(WIND_SPEED_PIN, INPUT_PULLDOWN);
    attachInterrupt( digitalPinToInterrupt(WIND_SPEED_PIN), Wind_Speed_Count_Turn, FALLING);
    pinMode(WIND_DIRECTION_PIN, INPUT_PULLUP);
    analogReadResolution(10);
}

ERA_WRITE(V3){
    int value = param.getInt();
    (value)?(digitalWrite(LED_CTL_PIN_1,HIGH)):
             digitalWrite(LED_CTL_PIN_1,LOW);
};

ERA_WRITE(V4){
    int value = param.getInt();
    (value)?(digitalWrite(LED_CTL_PIN_2,HIGH)):
             digitalWrite(LED_CTL_PIN_2,LOW);
};

void Update_Sensor_Data(){
    Serial.println();
    Set_Indicator_Flag(0x0);
    // Update LED pins
    ERa.virtualWrite(V4, digitalRead(LED_CTL_PIN_2));
    ERa.virtualWrite(V3, digitalRead(LED_CTL_PIN_1));
    // Read humid and temp from dht sensor
    delay(4000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    // Check read data
    if( isnan(t) || isnan(h) ){
            // Send Error msg to serial
            Serial.println("DHT11 - E: Corrupted data!");
            Set_Indicator_Flag(0x1);
        }else{
        // Send Temp + Humid data to serial
        Serial.print("Temp: ");
        Serial.println(t);
        Serial.print("Humid: ");
        Serial.println(h);
        // Update data sensor
        ERa.virtualWrite(V0, t);
        ERa.virtualWrite(V1, h);
    }
    //WIND SPEED
    float wspeed = 0;
    float wdirection = 0;
    curr_t = millis();
    if( !last_t || last_t > curr_t){
        turn_count = 0;
        last_t = curr_t;
        return;
    }{
        wspeed = 0.667*turn_count/delta_seccond(last_t, curr_t);
        turn_count = 0;
        last_t = curr_t;
        ERa.virtualWrite(V5, wspeed);

        Serial.print("Wind speed: ");
        Serial.println(wspeed);
    }
    //WIND DIRECTION
    wdirection = analogRead(WIND_DIRECTION_PIN);
    if(in_accepted_range(786, wdirection))
        wdirection = 0;
    else if(in_accepted_range(406, wdirection))
        wdirection = 22.5;
    else if(in_accepted_range( 461, wdirection))
        wdirection = 45;
    else if(in_accepted_range( 84, wdirection))
        wdirection = 67.5;
    else if(in_accepted_range( 93, wdirection))
        wdirection = 90;
    else if(in_accepted_range( 65, wdirection))
        wdirection = 112.5;
    else if(in_accepted_range( 185, wdirection))
        wdirection = 135;
    else if(in_accepted_range( 126, wdirection))
        wdirection = 157.5;
    else if(in_accepted_range( 287, wdirection))
        wdirection = 180;
    else if(in_accepted_range( 244, wdirection))
        wdirection = 202.5;
    else if(in_accepted_range( 630, wdirection))
        wdirection = 225;
    else if(in_accepted_range( 599, wdirection))
        wdirection = 247.5;
    else if(in_accepted_range( 945, wdirection))
        wdirection = 270;
    else if(in_accepted_range( 827, wdirection))
        wdirection = 292.5;
    else if(in_accepted_range( 887, wdirection))
        wdirection = 315;
    else if(in_accepted_range( 702, wdirection))
        wdirection = 337.5;
    else {
        Set_Indicator_Flag(0x4);
        return;
    }
    Serial.print("Wind direction: ");
    Serial.println(wdirection);
    ERa.virtualWrite(V6, wdirection);
    
}

void timerEvent() {
    ERA_LOG(ERA_PSTR("Timer"), ERA_PSTR("Uptime: %d"), ERaMillis() / 1000L);
    Update_Sensor_Data();
}

void Initial_Serial(){
  Serial.begin(115200);
  Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
}

void setup() {
    Initial_Serial();
    Initial_GPIO_Pin();
    ERa.setModbusClient(mbTcpClient);
    ERa.setScanWiFi(true);
    ERa.begin(ssid, pass);
    ERa.addInterval(1000L, timerEvent);
}

void loop() {
    ERa.run();
}

