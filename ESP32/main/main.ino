#include "Configuration.h"
#include <FirebaseESP32.h>
FirebaseData firebaseData;
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TFT_eSPI.h> // Include the library
#include <SPI.h>
#include "time.h"
TFT_eSPI tft = TFT_eSPI(240, 320); 
#include <Servo.h>
OneWire oneWire(SENSOR_SUHU);
DallasTemperature sensor(&oneWire);
static const int servoPin = 12;
Servo servo1;

unsigned long previousMillis = 0;
const unsigned long interval = 60000; // interval waktu dalam milidetik (1 menit)

const char* ntpServer = "0.id.pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;


void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
    pinMode(phPin, INPUT);
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
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();

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
    printLocalTime();
    //getTurbidity();
    PHsensor();

    // Jika sudah lewat waktu 1 menit sejak data terakhir dikirim
    if (currentMillis - previousMillis >= interval) {
        // Simpan nilai millis saat ini ke dalam previousMillis
        previousMillis = currentMillis;

        // Kirim data ke Firebase
        Firebase.setFloat(firebaseData, "/admin/aquarium-1/ph", Po);
        Firebase.setFloat(firebaseData, "/admin/aquarium-1/temp", Temperature);
        Firebase.setFloat(firebaseData, "/admin/aquarium-1/turbidity", randNumber);
        Firebase.setString(firebaseData,"/admin/aquarium-1/updated_at",dateStr);
    }
    Serial.println(Temperature);
    //getServo();

}