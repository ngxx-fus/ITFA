## Hardware Specs
Board: DOIT ESP32 DEVKIT V1
![pinout](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/board_pinout.png?raw=true)

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
Before Sign-up to Firebase, you must connect to Wi-Fi via the command:
```
WiFi.begin(WIFI_SSID, WIFI_PWD);
```
To check Wi-Fi connection, you can use ```WiFi.status()```, this function return a code with enum formed:
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
#include <Arduino.h>

#define WIFI_SSID "rm.note.11"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define DATABASE_URL "https://this-is-a-test-a0f7d-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyDNSbmHmGsDEip7-m6zFJKe9TZ5d56bjDs"

#include "FirebaseESP32.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;


void setup(){
    Serial.begin(115200);
    Serial.println("Hello from ESP32!");

    WiFi.begin(WIFI_SSID, WIFI_PWD);

    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    Firebase.signUp(&config, &auth, "", "");
    
    config.token_status_callback = tokenStatusCallback;
    
    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);

    //TEST
    Serial.printf(config.signer.signupError.message.c_str());
    Serial.printf("Setup done!");

}

void loop(){
    Serial.printf("loading");
    delay(1000);
    if(!Firebase.setString(firebaseData, "TEST_ADDR", "TEST_VALUE"))
        Serial.println("Uload: e");
}
```

Result:
![res](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/demo.png?raw=true)

## Section-2 Specified user
### Step-1 Set-up Authentication
Choose **Email/Password** privider.
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image20.png?raw=true)
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image21.png?raw=true)
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image22.png?raw=true)

### Step-2 Create Email+Password
Go to [Service Account Website](https://console.cloud.google.com/iam-admin/serviceaccounts). Select your project and continue.
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image23.png?raw=true)
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image24.png?raw=true)
Enter name
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image25.png?raw=true)
Grant this service account access to YOUR_PROJECT so that it has permission to complete specific actions on the resources in your project
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image26.png?raw=true)
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image27.png?raw=true)
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image28.png?raw=true)
Copy your EMAIL ADDRESS!
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image29.png?raw=true)
Back to Authentication tag, Sign-up Method tab, click **Add user**
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image30.png?raw=true)
Using Email has been created before and create new password. This user only has Editor permition.
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image31.png?raw=true)
Done.
![img](https://github.com/ngxx-fus/ITFA/blob/main/lab3_itfa_firebase_test/imgs/image32.png?raw=true)
NOTE: Copy this UID :> (U will need it to set rule for only this user to access the resource).

### Step-3 Set-up rule
```
{
  "rules": {
    ".read": "auth.uid === 'Wxkxj977qSdL9Fp9fYet20U6Rai2'",
    ".write": "auth.uid === 'Wxkxj977qSdL9Fp9fYet20U6Rai2'"
  }
}
```
### Step-3 Set-up in code
To lazy to write more detail, research by yourself, gud luck.
```
#include <Arduino.h>
#include "pin_def.h"
#include "dht11_def.h"
#include "serial_def.h"

#define WIFI_SSID "**********"
#define WIFI_PWD "**********"
#include "WiFi.h"


#define DATABASE_URL "*****************************************"
#define API_KEY "*****************************************"
#define EMAIL "***********@*********.iam.gserviceaccount.com"
#define PASSWORD "**********"

#include "FirebaseESP32.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

#define LED_CTL_PIN_1 21
#define INDICATOR_LED_PIN 23
#define LED_CTL_PIN_2 19

struct SENSOR_DATA{
  float temp;
  float humid;
} sensor_data;

// Codes:
// 0x0: Read data from sensor
// 0x1: wifi error
// 0x2: Firebase error
void Set_Indicator_Flag(int err_code = 0){
  // Blink led to noti error
  switch (err_code){
    case 0x0: err_code = 1; break;
    case 0x1: err_code = 2; break;
    case 0x2: err_code = 3; break;
    default:  err_code = 0;
  }
  while(err_code--){
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(100);
    digitalWrite(INDICATOR_LED_PIN, HIGH); delay(200);
    digitalWrite(INDICATOR_LED_PIN, LOW); delay(100);
  }
}

void Initial_Serial(){
  Serial.begin(9600);
  Serial.println(("\n\nHello!\nFrom MEOW GROUP!"));
}

void Initial_GPIO_Pin(){
  pinMode(LED_CTL_PIN_1, OUTPUT);
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  pinMode(LED_CTL_PIN_2, OUTPUT);
}

bool WiFi_Is_Connected(){
  if(WiFi.status() != WL_CONNECTED){
      Set_Indicator_Flag(0x1);
      Serial.println("No Wi-Fi connection!");
      return false;
  }
  return true;
}

void Initial_Wifi(){
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  do{
    Serial.println("Connecting to Wi-fi...");
    delay(2000);
  }while(!WiFi_Is_Connected());
  Serial.println("Connected to Wi-fi!");
}

void Initial_Firebase() {
  Serial.println("Connecting to Firebase...");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = EMAIL;
  auth.user.password = PASSWORD;

  while(0x1)
    // sign-up as anonymous
    if(Firebase.signUp(&config, &auth, "", "")){
      Serial.println("Connected to Firebase!");
      break;
    }else{
      Serial.println("Failed to connect to Firebase!");
      Serial.print("E:");
      Serial.println(config.signer.signupError.message.c_str());
      Serial.println("Re-try...");
    }
  // config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void Firebase_Sync(){
  if(WiFi_Is_Connected() == false) return;
  // Sync sensor data
  if(
    !Firebase.setString(firebaseData, "Temp", String(sensor_data.temp))
    || !Firebase.setString(firebaseData, "Humid", String(sensor_data.humid))
  ){
    Serial.println("Failed to sync to Firebase!");
    Set_Indicator_Flag(0x2);
  }
}

void Update_Sensor_Data(){
  Set_Indicator_Flag(0x0);
  // Wait 4 seconds for DHT sensor
  delay(4000);
  // Read humid and temp from dht sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check read data
  if( isnan(t) || isnan(h) ){
        // Send Error msg to serial
        Serial.println("DHT11 - E: Corrupted data!");
        Set_Indicator_Flag();
      }else{
      // Send Temp + Humid data to serial
      Serial.println("Temp: ");
      Serial.println(t);
      Serial.println("Humid: ");
      Serial.println(h);
      // Update data sensor
      sensor_data.humid = h;
      sensor_data.temp = t;
      // Sync to Firebase
      Firebase_Sync();

    }
}

void setup(){
  Initial_Serial();
  Initial_GPIO_Pin();
  dht.begin();
  Initial_Wifi();
  Initial_Firebase();
}

void loop(){
  Update_Sensor_Data();
  delay(1000);
}
```
