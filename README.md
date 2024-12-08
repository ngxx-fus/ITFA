# Hello
    Hello from ngxxfus, this repo was made to store the labs in ITFA class at HCMUTE.

# Sumary
## Hardware
- ESP32; Board: ESP32_DOIT_DEVKIT_V1
- DTH11
- LED + Resistor (220 ohm)
- LCD TFT 2.2" (ILI9225)  

## Software
- Visualt Studio Code; [More detailed: Link](https://code.visualstudio.com/)
- PlatformIO; [More detailed: Link](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
- Wokwi [More detailed: Link](https://wokwi.com/)

## Working tree

    A project
    ├──── .pio
    │     ├──── build                           : Object, bin, firmware files (built by platformIO)
    │     │     ├──── esp32doit-devkit-v1 
    │     │     │     ├──── firmware.bin        : for simulate in Wokwi
    │     │     │     ├──── firmware.elf        : for simulate in Wokwi
    │     │     │     └──── ...
    │     │     └──── project.checksum
    │     └──── libdeps                         : fetched libs (declare in platformio.ini)
    ├──── src
    │     ├──── main.cpp                        : your source code
    │     └──── *.h                             : your hear files (if any)
    └──── ...

## Content

All project in this repo is a System that provides monitoring and control a simple device (ex. LED).
- lab2 : ESP32 + Blynk + LED
- lab3 : ESP32 + Firebase + ThingSpeak + LED
- lab4 : ESP32 + MQTT (Adafruit IO) + LED
- lab_bonus_1 : ESP32 + ERa
- lab_bonus_2 : ESP32 + WS3000 (Weather Station)
  
## Thank for your watching
Hope you have a greatful day!