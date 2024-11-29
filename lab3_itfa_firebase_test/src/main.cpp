

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
  auth.user.email = "itfa-name@lab3-itfa.iam.gserviceaccount.com";
  auth.user.password = "nGXXFUS@3204";
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

