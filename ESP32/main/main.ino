#include "Configuration.h"
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TFT_eSPI.h> // Include the library
#include <SPI.h>
#include "time.h"
#include <Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>




static const int servoPin = 12;
unsigned long previousMillis = 0;
const unsigned long interval = 60000; // interval waktu dalam milidetik (1 menit)
const char* ntpServer = "0.id.pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

FirebaseData firebaseData;
Servo servo1;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
OneWire oneWire(SENSOR_SUHU);
DallasTemperature sensor(&oneWire);
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite sprite = TFT_eSprite(&tft);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600); // GMT+7

void setup() {
    
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    sprite.setColorDepth(8);
    sprite.createSprite(LOADING_BAR_WIDTH, LOADING_BAR_HEIGHT + 20);
    /*uint16_t calData[5] = { 350, 3800, 350, 3400, 7 };
    tft.setTouch(calData); */
    uint16_t calData[5] = { 261, 3521, 367, 3422, 7 };
    tft.setTouch(calData);
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
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    sensor.begin();
    timeClient.begin();
    while (!timeClient.update()) {
        timeClient.forceUpdate();
    }

    //firebase config
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    Firebase.begin(&config, &auth);

    if (Firebase.ready()) {
        Serial.println("Firebase connection successful");
    } else {
        Serial.println("Firebase connection failed");
    }
    for (int i = 0; i <= 100; i += 5) { // Change the increment value and max value to adjust loading speed
        drawLoadingBar();
        delay(100); // Change the delay time to adjust loading speed
    }
    tft.fillScreen(TFT_BLACK);

}
void loop(){
    long randNumber;
    randNumber = random(300);
    float Temperature = GetSuhu();
    PHsensor();


    unsigned long currentMillis = millis();
    // Jika sudah lewat waktu 1 menit sejak data terakhir dikirim
    if (Firebase.ready() && (currentMillis - previousMillis >= interval)) {
        // Simpan nilai millis saat ini ke dalam previousMillis
        previousMillis = currentMillis;

        // Kirim data ke Realtime database
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/ph"), Po) ? "data ph terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/temp"), Temperature)  ? "data temperature suhu terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/turbidity"), randNumber) ? "data turbidity sukses terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setString(&fbdo,F("/admin/aquarium-1/updated_at"),dateStr) ? "data tanggal saat ini sukses terkirim" : fbdo.errorReason().c_str());

    }
    //Serial.println(Temperature);
    //getServo();
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    // Mengirim data ke Firestore setiap hari sekali pada jam 6 pagi WIB
     if (timeinfo->tm_hour == 6 && timeinfo->tm_min == 0 && timeinfo->tm_sec == 0) {
        // membuat objek JSON
        FirebaseJson json;
        String documentPath = "/admin/aquarium-1/update-harian/";
        json.set("fields/ph/doubleValue", randNumber);
        json.set("fields/temp/doubleValue", Temperature);
        json.set("fields/turbidity/doubleValue", Po);

        // mengirim data JSON ke Firestore
        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), json.raw())){
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        }
        else{
            Serial.println(fbdo.errorReason());
        }            
        
        
    }

}