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
#include "alert.h" // Out of range alert icon
#include <EEPROM.h> 


static const int servoPin = 12;
unsigned long previousMillis = 0;
const unsigned long interval = 60000; // interval waktu dalam milidetik (1 menit)
const char* ntpServer = "0.id.pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

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
uint32_t runTime = -99999; // time for next update
int d = 0;       // Variable used for the sinewave test waveform
boolean range_error = 0;
#define TFT_GREY 0x2104 // Dark grey 16 bit colour
 
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 1000; // the debounce time; increase if the output flickers


void setup() {
    myWire.begin(25, 32);
    pinMode(relay1,OUTPUT);
    if (! rtc.begin(&myWire)) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    if (!EEPROM.begin(1000)) {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
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
    int Temperature = GetSuhu();
    Serial.printf("suhu saat ini: %d\n",Temperature);
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

    String waktu = "";
    if (now.hour() < 10) {
        waktu += "0";
    }
    waktu += String(now.hour(), DEC);
    waktu += ":";
    if (now.minute() < 10) {
        waktu += "0";
    }
    waktu += String(now.minute(), DEC);
    Serial.println(waktu);


    float angka_random = random(0, 100) / 1.0 + 1.0;

    if(SwitchOn){
        ringMeter(int(angka_random), 0, 100, 185, 100, 63, "kekeruhan", GREEN2RED); // Draw analogue meter
        ringMeter(Po, 0, 16, 310, 25, 63, "PH", RED2GREEN);
        ringMeter(Temperature, -10, 40, 60, 25, 63, "C", BLUE2RED);
    }
    if (tft.getTouch(&x, &y)) {
        if(SwitchOn){
            tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
            if (x >= monitor_x && x <= monitor_x + monitor_width && y >= monitor_y && y <= monitor_y + monitor_height) {
                tft.fillScreen(TFT_BLACK);
                //tft.drawString("PENGURAS AIR",220,10,2);
                tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
                tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                SwitchOn = false;
             // contoh: tampilkan menu monitor
            }

        

        }else{
            //tft.drawString("PENGURAS AIR",220,10,2);
            tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
            if (x >= pompa_x && x <= pompa_x + pompa_width &&  y >= pompa_y && y <= pompa_y + pompa_height) {
                tft.fillScreen(TFT_BLACK);
                tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
                digitalWrite(relay1,HIGH);
                SwitchOn = true;
                SwitchButton = true;
            }
            if(SwitchButton){
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width+5 &&  y >= buttonOnOff_y+15 && y <= buttonOnOff_y+15 + buttonOnOff_height-30){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y+15,buttonOnOff_width+5,buttonOnOff_height-40,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,ON);
                    digitalWrite(relay1,LOW);
                    SwitchButton = false;
                }
            }else{
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width+5 &&  y >= buttonOnOff_y+15 && y <= buttonOnOff_y + buttonOnOff_height-30){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y+15,buttonOnOff_width+5,buttonOnOff_height-40,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                    digitalWrite(relay1,HIGH);
                    SwitchButton = true;
                    
                    
                }
                // kode untuk mengaktifkan pompa air
            }
            Serial.printf("switchbutton: %d \n",SwitchButton);
            

        }
        Serial.printf("SwitchOn: %d \n",SwitchOn);
    }
    char str_time[7]; // buat array karakter untuk menampung string waktu
    sprintf(str_time, "%02d:%02d", now.hour(), now.minute()); // format string waktu menjadi "hh:mm:ss"
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(str_time,240,27,7); // cetak string waktu
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor (220, 55);
    tft.print(tanggal); // This uses the standard ADAFruit small font

    FirebaseJson json;
    // Mengirim data ke Firestore setiap hari sekali pada jam 6 pagi WIB
    if (now.hour() == 6 && now.minute() == 0 && now.second() == 0) {
        // membuat objek JSON
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
        FirebaseJson jVal;
        FirebaseJsonData result1;
        FirebaseJsonData result2;
        FirebaseJsonData result3;


        
        // Kirim data ke Realtime database
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/ph"), Po) ? "data ph terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/temp"), Temperature)  ? "data temperature suhu terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/turbidity"), Temperature) ? "data turbidity sukses terkirim" : fbdo.errorReason().c_str());
        Serial.println(Firebase.RTDB.setString(&fbdo,F("/admin/aquarium-1/updated_at"),tanggal) ? "data tanggal saat ini sukses terkirim" : fbdo.errorReason().c_str());


        //baca data dari rtdb untuk pakan  
        Serial.printf("Get json ref... %s\n", Firebase.RTDB.getJSON(&fbdo, "/admin/aquarium-1/pakan", &jVal) ? jVal.raw() : fbdo.errorReason().c_str());
        jVal.get(result1,"/feed_time_1");
        jVal.get(result2,"/feed_time_2");
        jVal.get(result3,"/feed_time_3");
        if(result1.success && result2.success && result3.success){
           //Serial.printf("pakan no 1: %s \n pakan no 2: %s \n  pakan no 3: %s",result1.to<String>(),result2.to<String>(),result3.to<String>());
            myRtdbFeedTime[0]= result1.to<String>();
            myRtdbFeedTime[1]= result2.to<String>();
            myRtdbFeedTime[2]= result3.to<String>();


            if(EEPROM.readString(addressFeedtime0) != myRtdbFeedTime[0]){
                EEPROM.writeString(addressFeedtime0, myRtdbFeedTime[0]);
                EEPROM.commit();
                Serial.printf("data disimpan ke EEPROM addressFeedtime0 dengan nilai string: %s",myRtdbFeedTime[0]);
            }
            else if(EEPROM.readString(addressFeedtime1) != myRtdbFeedTime[1]){
                EEPROM.writeString(addressFeedtime1, myRtdbFeedTime[1]);
                EEPROM.commit();
                Serial.printf("data disimpan ke EEPROM addressFeedtime1 dengan nilai string: %s",myRtdbFeedTime[1]);

            }
            else if(EEPROM.readString(addressFeedtime2) != myRtdbFeedTime[2]){
                EEPROM.writeString(addressFeedtime2, myRtdbFeedTime[2]);
                EEPROM.commit();
                Serial.printf("data disimpan ke EEPROM addressFeedtime2 dengan nilai string: %s",myRtdbFeedTime[2]);

            }else{
                Serial.printf("data sudah sama dengan eeprom");
            }
            Serial.printf("pakan no 1: %s \n pakan no 2: %s \n  pakan no 3: %s",EEPROM.readString(addressFeedtime0),EEPROM.readString(addressFeedtime1),EEPROM.readString(addressFeedtime2));
        }
        localVarFeedTime[0] = EEPROM.readString(addressFeedtime0);
        localVarFeedTime[1] = EEPROM.readString(addressFeedtime1);
        localVarFeedTime[2] = EEPROM.readString(addressFeedtime2);
        Serial.printf("waktu pakan no 1: %s \n waktu pakan no 2: %s \n  waktu pakan no 3: %s",localVarFeedTime[0],localVarFeedTime[1],localVarFeedTime[2]);
        int timedel = 1000;
        getServo(waktu,localVarFeedTime,numFeed,timedel);



    }


}


