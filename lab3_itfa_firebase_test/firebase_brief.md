## How to setup RealtimeFirebase?
You can set-up your FirebaseRealtime in serveral steps below:
### Step-0 Sign-up
Go to the [link: https://console.firebase.google.com](https://console.firebase.google.com) and login.
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image.png?raw=true)
### Step-1 Create new project
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image.png?raw=true)
Enter your project name.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image1.png?raw=true)
Continue
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image3.png?raw=true)
Choose Default Account for Firebase
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image4.png?raw=true)
Wait for the process done
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image5.png?raw=true)
Continue
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image6.png?raw=true)
### Step-2 set-up Authentication
In the left column, click **Build** tag then choose **Authentication** tag.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image7.png?raw=true)
Click **Get started**
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image8.png?raw=true)
In tab Authentication/Sign-in method choose **Anonymous**. This option allow a anonymous user to access your Firebase resource. In the next section, i will introduce how to specify a user how can access the resource.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image9.png?raw=true)
Enable and save the setting.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image10.png?raw=true)
Oke.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image11.png?raw=true)
### Step-3 set-up Realtime Database
Back to **build** tag, choose **Realtime Database** tag then **Create Database**.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image12.png?raw=true)
Choose Database Center, there are some database centers for you to choose. I will choose ```us-cental1```.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image13.png?raw=true)
Select ***Start in locked mode*** option, then click **Enable** :v
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image14.png?raw=true)
OKE.
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image15.png?raw=true)
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
![alt text](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image16.png?raw=true)

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
### Step-0 Get Firebase Credentials
Before go to Step-1, you must copy some credential informations.
#### DATABASE_URL
In tag Build/Realtime Database choose **Data** tab, then copy the URL.
![inmg](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image17.png?raw=true)
#### API_KEY
From Project Overview tag, select ⚙️ then select **Project settings**
![inmg](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image18.png?raw=true)
At tab **General**, copy **Web API key**.
![inmg](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image19.png?raw=true)
(This API Key in the picture will be unusable :v bcz the project will be deleted after i make this guide.)

### Step-1 install dependencies (lib)
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

### Step-2 coding yeah yeah
I will divide into 2 catagories, the first for set-up and connect to Realtime Firebase (only run at start-up), and the last one is run to upload data.
#### Set-up and Connect

The first thing to include in any project based on Arduino framework is ```#include <Arduino.h>```  It almost prevents "strange" errors :)

Then set-up Wi-Fi connection:
```
#define WIFI_SSID "your Wi-Fi name (SSID)"
#define WIFI_PWD "your Wi-Fi password"
#include "WiFi.h"
```
To check Wi-Fi connection, you can use ```WiFi.status()```, this function return some code with enum formed:
```
typedef enum {
    WL_NO_SHIELD        = 255,   
    WL_IDLE_STATUS      = 0,
    WL_NO_SSID_AVAIL    = 1,
    WL_SCAN_COMPLETED   = 2,
    WL_CONNECTED        = 3,
    WL_CONNECT_FAILED   = 4,
    WL_CONNECTION_LOST  = 5,
    WL_DISCONNECTED     = 6
} wl_status_t;
```
For re-use or easier in fix bug, share code, ..., i rcm you define some macro:
```
#define DATABASE_URL "Firebase URL"
#define API_KEY "Web API Key"
```
Include Firebase header
```
#include "FirebaseESP32.h"
```
Include Firebase header (for get sendback-token, bcz of using ```Sign-in Method/Anonymous```)
```
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
```
Next, you need to make three objects: config, auth, firebaseData
```
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
```
Next, set value for ```config``` object:
```
config.api_key = API_KEY;
config.database_url = DATABASE_URL;
```
Sign-up to Firebase using ```Firebase.signUp```, this method return ```true``` if the progress is successful, ```false``` otherwise.
```
Firebase.signUp(&config, &auth, "", "");
```
You can log the error by print this code (using Serial.printlin(), ....):
```
config.signer.signupError.message.c_str()
```
After signed-up, Firebase will sendback the token stored in ```tokenStatusCallback```, you need set this token into **config** object.
```
config.token_status_callback = tokenStatusCallback;
```
Then start Firebase. For each time you reset, upload, ... this stuff will create an anonymous user :> (In next section i will introduce how to use ```Sign-in Method```/```Email/Password``` provider.)
```
Firebase.begin(&config, &auth);
```
One more step, set auto-connect Wi-Fi
```
Firebase.reconnectWiFi(true);
```

#### Data pushing
In this guide (until now), i only introduce how to push data from ESP32 into Realtime Database. To push data, you can use ```set``` method. This method return ```true``` if success, ```false``` otherwise.


With String:
```
Firebase.setString(firebaseData, "path/", "string value")
```
With int:
```
Firebase.setInt(firebaseData, "/path", 23)
```
And so on with other datatype.

## Full code (Simple Version)
```

```
