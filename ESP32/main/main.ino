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
#include "monitor.h"
#include "pompa.h"
#include "ON.h"
#include "OFF.h"
#include "RTClib.h"


static const int servoPin = 12;
unsigned long previousMillis = 0;
const unsigned long interval = 60000; // interval waktu dalam milidetik (1 menit)
const char* ntpServer = "0.id.pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

RTC_DS1307 rtc;
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
TwoWire myWire(1);


void setup() {
    myWire.begin(25, 32); 
    if (! rtc.begin(&myWire)) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    uint16_t calData[5] = { 261, 3521, 367, 3422, 7 };
    tft.setTouch(calData);

    sprite.setColorDepth(8);
    sprite.createSprite(LOADING_BAR_WIDTH, LOADING_BAR_HEIGHT + 20);
    /*uint16_t calData[5] = { 350, 3800, 350, 3400, 7 };
    tft.setTouch(calData); */

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
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);

}
void loop(){
    PHsensor();
    uint16_t x, y;
    static uint16_t color;
    DateTime now = rtc.now();
    float Temperature = GetSuhu();


    // format tanggal
    String tanggal = "";
    if (now.day() < 10) {
        tanggal += "0";
    }
    tanggal += String(now.day(), DEC);
    tanggal += "-";
    if (now.month() < 10) {
        tanggal += "0";
    }
    tanggal += String(now.month(), DEC);
    tanggal += "-";
    tanggal += String(now.year(), DEC);

    if (tft.getTouch(&x, &y)) {
        if(SwitchOn){
            tft.drawString("ini tampilan monitor",160,150,2);
            tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
            if (x >= monitor_x && x <= monitor_x + monitor_width && y >= monitor_y && y <= monitor_y + monitor_height) {
                tft.fillScreen(TFT_BLACK);
                tft.drawString("AKTIFKAN PENGURAS AIR",160,10,2);
                tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
                tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                SwitchOn = false;

             // contoh: tampilkan menu monitor
            }

        

        }else{
            tft.drawString("AKTIFKAN PENGURAS AIR",160,10,2);
            tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
            if (x >= pompa_x && x <= pompa_x + pompa_width &&  y >= pompa_y && y <= pompa_y + pompa_height) {
                tft.fillScreen(TFT_BLACK);
                tft.drawString("ini tampilan monitor",160,150,2);
                tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
                SwitchOn = true;
                SwitchButton = true;
            }
            if(SwitchButton){
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width &&  y >= buttonOnOff_y && y <= buttonOnOff_y + buttonOnOff_height){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,ON);
                    SwitchButton = false;
                }
            }else{
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width &&  y >= buttonOnOff_y && y <= buttonOnOff_y + buttonOnOff_height){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                    SwitchButton = true;
                    
                }
                // kode untuk mengaktifkan pompa air
            }
            Serial.printf("switchbutton: %d \n",SwitchButton);
            

        }
        Serial.printf("SwitchOn: %d \n",SwitchOn);

        tft.setCursor(5, 5, 2);
        tft.printf("x: %i     ", x);
        tft.setCursor(5, 20, 2);
        tft.printf("y: %i    ", y);
        tft.drawPixel(x, y, color);
        color += 155;
    }



    // Mengirim data ke Firestore setiap hari sekali pada jam 6 pagi WIB
    if (now.hour() == 6 && now.minute() == 0 && now.second() == 0) {
        // membuat objek JSON
        FirebaseJson json;
        String documentPath = "/admin/aquarium-1/update-harian/";
        json.set("fields/ph/doubleValue", Po);
        json.set("fields/temp/doubleValue", Temperature);
        json.set("fields/turbidity/doubleValue", Po);
        json.set("fields/created_at/stringValue",tanggal);

        // mengirim data JSON ke Firestore
        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), json.raw())){
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        }
        else{
            Serial.println(fbdo.errorReason());
        }            
        
        
    }



    //Serial.println(Temperature);
    //getServo();

    unsigned long currentMillis = millis();
    // Jika sudah lewat waktu 1 menit sejak data terakhir dikirim
    if (Firebase.ready() && (currentMillis - previousMillis >= interval)) {
        // Simpan nilai millis saat ini ke dalam previousMillis
        previousMillis = currentMillis;

        // Kirim data ke Realtime database
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/ph"), Po) ? "data ph terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/temp"), Temperature)  ? "data temperature suhu terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/turbidity"), Temperature) ? "data turbidity sukses terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setString(&fbdo,F("/admin/aquarium-1/updated_at"),tanggal) ? "data tanggal saat ini sukses terkirim" : fbdo.errorReason().c_str());


    }



}