#include "era_def.h"
#include "serial_def.h"
#include "dht11_def.h"
#include "pin_def.h"

void Update_Sensor_Data(){
    Set_Indicator_Flag(0x0);
    float t, h;
    if(dht11_read(t, h)){
        msg2ser("Temp: ", String(t), " (oC)");
        msg2ser("Humid: ", String(h), " (%)");
        msg2ser();
    }
}

void timerEvent() {
    ERA_LOG(ERA_PSTR("Timer"), ERA_PSTR("Uptime: %d"), ERaMillis() / 1000L);
    Update_Sensor_Data();
}

void main_init(){
    era_init();
    serial_init(115200);
    gpio_init();
    ERa.addInterval(1000L, timerEvent);
}