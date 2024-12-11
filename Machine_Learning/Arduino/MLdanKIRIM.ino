
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "EINSTEIN"
#define WIFI_PASSWORD "emil23062001"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAM2RGVIizrgf0558K1TcoI6HOCxVd6iTY"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://fall-detection-iot-e3062-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
int counter=0;
bool signupOK = false;
unsigned long int timer;
String statuse;
float totalAcceleration;

//ML
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <eml_net.h>
#include <eml_common.h>
#include "TrainedUMAFALLCoventry2.h" // the generated code basedon on keras.Sequential
float values[300] = {};
int DetectTime=0;
#define arrSize sizeof(values) / sizeof(values[0])
#define StepSize 20
#define FullStep 50
#define Sepi (arrSize-StepSize*6)
Adafruit_MPU6050 mpu;
#define LED_PIN 2          // Pin LED pada Beetle ESP32C6


void FirebaseSetup(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void FirebaseSend(){
  if (Firebase.ready() && signupOK){
    int timestamp=millis()/1000;
    String jalurstring="sensor_data/history/" + String(timestamp)+"/status";
    if ( Firebase.RTDB.setString(&fbdo,jalurstring , statuse)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
     if ( Firebase.RTDB.setInt(&fbdo,"sensor_data/history/" + String(timestamp)+"/timestamp", timestamp)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    totalAcceleration = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z)) / 9.81;
    if ( Firebase.RTDB.setFloat(&fbdo, "sensor_data/history/" + String(timestamp)+"/total_acceleration", totalAcceleration)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if ( Firebase.RTDB.setString(&fbdo,"sensor_data/status", statuse)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
     else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
        if ( Firebase.RTDB.setFloat(&fbdo, "sensor_data/total_acceleration", totalAcceleration)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}

void ReadSensor(){
  const float predicted_value = Trained2_regress1(values,300 );
  memmove(values, values + StepSize*6, (arrSize-StepSize*6) * sizeof(int));
 int j=0;
while (j<StepSize){  
 sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
  values[Sepi+j*6] = accel.acceleration.y/9.81f;
  values[Sepi+j*6+1]=-accel.acceleration.x/9.81f;
  values[Sepi+j*6+2]=accel.acceleration.z/9.81f;
  values[Sepi+j*6+3]=gyro.gyro.y*57.2958f;
  values[Sepi+j*6+4]=-gyro.gyro.x*57.2958f;
  values[Sepi+j*6+5]=gyro.gyro.z*57.2958f;
  j++;
  delay(50);
}
if (predicted_value == NAN) {
    exit(-1);
}
Serial.println(predicted_value);
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);
totalAcceleration = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z)) / 9.81;
if (predicted_value>0.2) {
    Serial.println("Jatuh terdeteksi!");
    statuse= "Jatuh";
    DetectTime++;
    digitalWrite(LED_PIN, HIGH);  // Nyalakan LED jika jatuh terdeteksi
    if(DetectTime>2){
    FirebaseSend();
    }
}
else{
  digitalWrite(LED_PIN, LOW);
  if (totalAcceleration>0.1){
    statuse="Jalan";
  }
  else{
    statuse="Diam";
  }
  if (millis()/1000>timer){
    timer=millis()/1000+15;
    FirebaseSend();
  }
  DetectTime=0;
  
  Serial.print(predicted_value); 
}
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
FirebaseSetup();
  // Inisialisasi LED sebagai output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Inisialisasi MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 tidak terdeteksi!");
    while (1);
  }
  Serial.println("MPU6050 terhubung.");
   mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
   mpu.setGyroRange(MPU6050_RANGE_250_DEG);
   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
   int j=0;
   while (j<50){ 
  sensors_event_t accel, gyro, temp;
  // Get accelerometer and gyroscope data
  mpu.getEvent(&accel, &gyro, &temp);
  values[j*6] = accel.acceleration.y/9.81f;
  values[j*6+1]=accel.acceleration.x/9.81f;
  values[j*6+2]=accel.acceleration.z/9.81f;
  values[j*6+3]=gyro.gyro.y*57.2958f;
  values[j*6+4]=gyro.gyro.x*57.2958f;
  values[j*6+5]=gyro.gyro.z*57.2958f;
  j++;
  delay(50);
   }
    timer=millis()/1000+15;
}

void loop() {
  // put your main code here, to run repeatedly:
ReadSensor();
}
