#include "Configuration.h"
#include <FirebaseESP32.h>
FirebaseData firebaseData;
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TFT_eSPI.h> // Include the library
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI(240, 320); 
#include <Servo.h>
OneWire oneWire(SENSOR_SUHU);
DallasTemperature sensor(&oneWire);
static const int servoPin = 12;
Servo servo1;

unsigned long previousMillis = 0;
const unsigned long interval = 60000; // interval waktu dalam milidetik (1 menit)


void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
    while(!Serial){delay(100);}

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(DATABASE_URL, API_KEY);
    sensor.begin();

}
void loop(){
    long randNumber;
    randNumber = random(300);
    float Temperature = GetSuhu();
    unsigned long currentMillis = millis();

    // Jika sudah lewat waktu 1 menit sejak data terakhir dikirim
    if (currentMillis - previousMillis >= interval) {
        // Simpan nilai millis saat ini ke dalam previousMillis
        previousMillis = currentMillis;

        // Kirim data ke Firebase
        Firebase.setFloat(firebaseData, "/admin/aquarium-1/ph", randNumber);
        Firebase.setFloat(firebaseData, "/admin/aquarium-1/temp", temperature);
        Firebase.setFloat(firebaseData, "/admin/aquarium-1/turbidity", turbidity);
    }
    Serial.println(Temperature);
    getServo();

}