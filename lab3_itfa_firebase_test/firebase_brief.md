## How to setup RealtimeFirebase?
You can set-up your FirebaseRealtime in serveral steps below:
### Step-0 Sign-up
Go to the [link: https://console.firebase.google.com](https://console.firebase.google.com) and login.
![img](imgs\image.png)
### Step-1 Create new project
![alt text](imgs\image1.png)
Enter your project name.
![alt text](imgs\image2.png)
Continue
![alt text](imgs\image3.png)
Choose Default Account for Firebase
![alt text](imgs\image4.png)
Wait for the process done
![alt text](imgs\image5.png)
Continue
![alt text](imgs\image6.png)
### Step-2 set-up Authentication
In the left column, click **Build** tag then choose **Authentication** tag.
![alt text](imgs\image7.png)
Click **Get started**
![alt text](imgs\image8.png)
In tab Authentication/Sign-in method choose **Anonymous**. This option allow a anonymous user to access your Firebase resource. In the next section, i will introduce how to specify a user how can access the resource.
![alt text](imgs\image9.png)
Enable and save the setting.
![alt text](imgs\image10.png)
Oke.
![alt text](imgs\image11.png)
### Step-3 set-up Realtime Database
Back to **build** tag, choose **Realtime Database** tag then **Create Database**.
![alt text](imgs\image12.png)
Choose Database Center, there are some database centers for you to choose. I will choose ```us-cental1```.
![alt text](imgs\image13.png)
Select ***Start in locked mode*** option, then click **Enable** :v
![alt text](imgs\image14.png)
OKE.
![alt text](imgs\image15.png)
### Step-4 set-up Rules
In tag Build/Realtime Database choose **Rules** tab. This tab allow you set rules for **read** or **write** operation to your resource. For example if you set ```".read": false``` ```false``` this rule will deny any **read** operation to your resource.
<br>To access (R\W) to your resouce for anyone: 
```
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```
![alt text](imgs\image16.png)

To access (R\W) to your resouce for a specified user using uid (optional): 
```
{
  "rules": {
    ".read": "auth.uid === 'UID'",
    ".write": "auth.uid === 'UID'"
  }
}
```
### Step-5 Done
You have set-up your Realtime Firebase.

## How to push a data from ESP32 to the Realtime Firebase you have set-up?
### Step-0 install dependencies (lib)
If you are using PlatfromIO, append the setting bellow into ```lib_deps``` in **platformio.ini** file to install .
```
    mobizt/Firebase ESP32 Client@^4.4.14
```
After appended, **platformio.ini** file look like:
```
; env name also the name of build folder in .pio/build/
[env:esp32dev]
; platform
platform = espressif32
; board
board = esp32dev
; framework, although board is esp
; i will use arduino framework for easier of code :>
framework = arduino
; dependancies
lib_deps = 
	; for DHT sonsor
	adafruit/DHT sensor library@^1.4.6 
	adafruit/Adafruit Unified Sensor@^1.1.14
	; for Firebase
	mobizt/Firebase ESP32 Client@^4.4.14

; for "Serial" comunication (default baud_rate=9600);
; can be erased
monitor_speed = 115200
; for upload firmware to board, can be erased
upload_speed = 921600
upload_port = COM3
```
NOTE: **platformio.ini** is PlatformIO Project Configuration file, for more detail, pls visit the [doc: https://docs.platformio.org/page/projectconf.html](https://docs.platformio.org/page/projectconf.html).
<br>
<br>If you are using Arduino IDE, find the lib named **"Firebase ESP32 Client"**. Then Google how to set-up, i don't know :v Normally, the steps and libs is same.

### Step-1 coding yeah yeah
I will divide into 2 catagories, the first for set-up and connect to Realtime Firebase (only run at start-up), and the last one is run to upload data.
#### Set-up and Connect

The first thing to include in any project based on Arduino framework is ```#include <Arduino.h>```  It almost prevents "strange" errors :)

Then set-up Wi-Fi connection:
```
#define WIFI_SSID "your Wi-Fi name (SSID)"
#define WIFI_PWD "your Wi-Fi password"
#include "WiFi.h"

```

