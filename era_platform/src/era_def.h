#ifndef _ERA_DEF_H_
#define _ERA_DEF_H_

#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"
#define ERA_AUTH_TOKEN "a48df8f0-3073-430a-9148-b89a532c778d"

#define delta_seccond(t_i, t_f) (((t_f)-(t_i))/1000.0f)
#define in_accepted_range(l,m,r, x) ( ((l+(m))/2.0) <= (x) && (x)<=((m)+(r))/2.0+4)


#include <Arduino.h>
#include <ERa.hpp>
#include <ERa/ERaTimer.hpp>

#include "pin_def.h"

const char ssid[] = "rm.note.11";
const char pass[] = "nGXXFUS@3204";

WiFiClient mbTcpClient;

ERA_CONNECTED() {
    ERA_LOG(ERA_PSTR("ERa"), ERA_PSTR("ERa connected!"));
}

ERA_DISCONNECTED() {
    ERA_LOG(ERA_PSTR("ERa"), ERA_PSTR("ERa disconnected!"));
}

ERA_WRITE(V3){
    Set_Indicator_Flag(0x3);
};

ERA_WRITE(V4){
    Set_Indicator_Flag(0x4);
};

void msg2era(uint32_t virtual_pin, float data){
    ERa.virtualWrite(virtual_pin, data);
}

void era_init(){
    ERa.setModbusClient(mbTcpClient);
    ERa.setScanWiFi(true);
    ERa.begin(ssid, pass);
}

#endif