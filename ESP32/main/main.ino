#include "Configuration.h"
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TFT_eSPI.h> // Include the library
#include <SPI.h>
#include "time.h"
#include <Servo.h>
#include "monitor.h"
#include "pompa.h"
#include "ON.h"
#include "OFF.h"
#include "RTClib.h"
#include "wifi_idle.h"
#include "alert.h" // Out of range alert icon
#include "lost connections.h" // Out of range alert icon
#include "loading.h"
#include "connections.h"
#include <EEPROM.h> 
//#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <Fuzzy.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        26 

#define NUMPIXELS 16 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


static const int servoPin = 12;
unsigned long previousMillis = 0;
const unsigned long interval = 10000; // interval waktu dalam milidetik (1 menit)
const int   daylightOffset_sec = 3600;
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

RTC_DS3231 rtc;
FirebaseData firebaseData;
Servo servo1;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
OneWire oneWire(SENSOR_SUHU);
DallasTemperature sensor(&oneWire);
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite sprite = TFT_eSprite(&tft);
TwoWire myWire(1);
//uint32_t runTime = -99999; // time for next update
//int d = 0;       // Variable used for the sinewave test waveform
boolean range_error = 0;
#define TFT_GREY 0x2104 // Dark grey 16 bit colour
//WiFiManager wm;
Fuzzy *fuzzy = new Fuzzy();




//input perbandingan PH
FuzzySet *InputPhRendah = new FuzzySet(0, 0, 0.4, 0.6);
FuzzySet *InputPhTinggi = new FuzzySet(1.4, 1.6, 2, 2);

//input perbandingan kekeruhan
FuzzySet *InputKekeruhanJernih = new FuzzySet(0, 3, 3, 5);
FuzzySet *InputKekeruhanKeruh = new FuzzySet(5, 7, 7, 9);
FuzzySet *InputKekeruhanSangatKeruh = new FuzzySet(9, 12, 12, 15);

//fuzzyOutput
FuzzySet *ServoCepat = new FuzzySet(0, 500, 500, 1000);
FuzzySet *ServoSedang = new FuzzySet(1000, 1500, 1500, 2000);
FuzzySet *ServoLama = new FuzzySet(2000, 2500, 2500, 3000);


 
//unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
//unsigned long debounceDelay = 1000; // the debounce time; increase if the output flickers


void setup() {

    myWire.begin(25, 32);
    WiFi.mode(WIFI_STA);
    //wm.setConnectTimeout(5);

    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
    #endif
    // END of Trinket-specific code.

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pinMode(relay1,OUTPUT);
    if (!rtc.begin(&myWire)) {
        Serial.println(F("Couldn't find RTC"));
        Serial.flush();
        while (1) delay(10);
    }

    if (rtc.lostPower()) {
        Serial.println(F("RTC is NOT running, let's set the time!"));
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    //rtc.adjust(DateTime(2023, 5, 25, 16, 0, 12));
    if (!EEPROM.begin(1000)) {
        Serial.println(F("Failed to initialise EEPROM"));
        Serial.println(F("Restarting..."));
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

    Serial.begin(115200);
    servo1.attach(servoPin);
    while(!Serial){delay(100);}
    
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
    sensor.begin();
    //firebase config
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    Firebase.begin(&config, &auth);

    for (int i = 0; i <= 100; i += 5) { // Change the increment value and max value to adjust loading speed
        drawLoadingBar();
        delay(100); // Change the delay time to adjust loading speed
    }
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);
    fuzzyServo();
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

        pixels.setPixelColor(i, pixels.Color(0, 0, 150));

        pixels.show();   // Send the updated pixel colors to the hardware.

        delay(200); // Pause before next pass through loop
    }

}
void loop(){
    //wm.process();
    Serial.println(WiFi.status());
    //digitalWrite(relay1,HIGH);
    PHsensor();
    getTurbidity();
    Serial.println(analogRead(34));
    static uint16_t color;
    DateTime now = rtc.now();
    uint8_t Temperature = GetSuhu();
    // format tanggal
    String tanggal = (now.day() < 10 ? "0" : "") + String(now.day(), DEC) + "-" + (now.month() < 10 ? "0" : "") + String(now.month(), DEC) + "-" + String(now.year(), DEC);
    String waktu = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC) + ":" + (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
    Serial.println(waktu);


    uint8_t angka_random = random(0, 100);


    if(SwitchOn){
        ringMeter(kekeruhan, 0, 100, 180, 100, 63, "kekeruhan", GREEN2RED); // Draw analogue meter
        ringMeter(Po, 0, 16, 310, 25, 63, "PH", RED2GREEN);
        ringMeter(Temperature, -10, 50, 50, 25, 63, "C", BLUE2RED);
    }
    if (WiFi.status() == 3) {
        unsigned long currentMillis = millis(); // get the current time
        if (currentMillis - previousMillis >= 5000) { // check if enough time has passed
            previousMillis = currentMillis; // store the current time as the previous time for the next iteration
            tft.fillRect(wifilogo_x, wifilogo_y, wifilogo_width, wifilogo_height, TFT_BLACK);
            tft.pushImage(wifilogo_x, wifilogo_y, wifilogo_width, wifilogo_height, connections);
            if (Firebase.ready()) {
                Serial.println(F("Firebase connection successful"));
            } else {
                Serial.println(F("Firebase connection failed"));
            }
        }
    }
    if (WiFi.status() == 6 || WiFi.status() == 255 ) {
        unsigned long currentMillis = millis(); // get the current time
        if (currentMillis - previousMillis >= 5000) { // check if enough time has passed
            previousMillis = currentMillis; // store the current time as the previous time for the next iteration
            tft.fillRect(wifilogo_x, wifilogo_y, wifilogo_width, wifilogo_height, TFT_BLACK);
            tft.pushImage(wifilogo_x, wifilogo_y, wifilogo_width, wifilogo_height, lost_connections);
        }
    }
    menu();

    char str_time[7]; // buat array karakter untuk menampung string waktu
    sprintf(str_time, "%02d:%02d", now.hour(), now.minute()); // format string waktu menjadi "hh:mm:ss"
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(str_time,240,27,7); // cetak string waktu
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor (220, 55);
    tft.print(tanggal); // This uses the standard ADAFruit small font

    FirebaseJson json;
    // Mengirim data ke Firestore setiap hari sekali pada jam 6 pagi WIB
    if (now.hour() == 6 && now.minute() == 0 && now.second() == 0 && Firebase.ready()) {
        // membuat objek JSON
        String documentPath = "/admin/aquarium-1/update-harian/";
        json.set(F("fields/ph/doubleValue"), Po);
        json.set(F("fields/temp/doubleValue"), Temperature);
        json.set(F("fields/turbidity/doubleValue"), kekeruhan);
        json.set(F("fields/created_at/stringValue"),tanggal);

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
    if (Firebase.ready() /*&& (currentMillis - previousMillis >= interval)*/) {
        // Simpan nilai millis saat ini ke dalam previousMillis
        previousMillis = currentMillis;
        FirebaseJson jVal;
        FirebaseJsonData result1;
        FirebaseJsonData result2;
        FirebaseJsonData result3;
        if (Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/ph"), Po) && Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/temp"), Temperature) && Firebase.RTDB.setFloat(&fbdo, F("/admin/aquarium-1/turbidity"), kekeruhan) && Firebase.RTDB.setString(&fbdo, F("/admin/aquarium-1/updated_at"), tanggal)) {
            Serial.println(F("Data berhasil dikirim ke Realtime Database."));
        } else {
            Serial.printf("Data gagal dikirim ke Realtime Database. Error: %s\n", fbdo.errorReason().c_str());
        }

        //baca data dari rtdb untuk pakan  
        Serial.printf("Get json ref... %s\n", Firebase.RTDB.getJSON(&fbdo, F("/admin/aquarium-1/pakan"), &jVal) ? jVal.raw() : fbdo.errorReason().c_str());
        jVal.get(result1,F("/feed_time_1"));
        jVal.get(result2,F("/feed_time_2"));
        jVal.get(result3,F("/feed_time_3"));
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
                Serial.println(F("data sudah sama dengan eeprom"));
            }
            Serial.printf("pakan no 1: %s \npakan no 2: %s \npakan no 3: %s",EEPROM.readString(addressFeedtime0),EEPROM.readString(addressFeedtime1),EEPROM.readString(addressFeedtime2));
        }
        localVarFeedTime[0] = EEPROM.readString(addressFeedtime0);
        localVarFeedTime[1] = EEPROM.readString(addressFeedtime1);
        localVarFeedTime[2] = EEPROM.readString(addressFeedtime2);
        Serial.printf("waktu pakan no 1: %s \nwaktu pakan no 2: %s \nwaktu pakan no 3: %s",localVarFeedTime[0],localVarFeedTime[1],localVarFeedTime[2]);
        //getServo(waktu,localVarFeedTime,numFeed,timedel);



    }



    bool isServoRotated[numFeed] = {false}; // Array untuk melacak status putaran servo

    for (int i = 0; i < numFeed; i++) {
        if (waktu == localVarFeedTime[i] && !isServoRotated[i]) {
            nilaiKekeruhanSaatMakan[i] = kekeruhan;
            nilaiPhSaatMakan[i] = Po;
            fuzzy->setInput(1, perbedaanKekeruhanSaatIni[i]);
            fuzzy->setInput(2, perbedaanPhSaatIni[i]);
            fuzzy->fuzzify();
            int output = fuzzy->defuzzify(1);
            servo1.write(130); // Menggerakkan servo
            Serial.println("saatnya makan");
            
            delay(3000);
            servo1.write(170); // Kembali ke posisi semula
            
            isServoRotated[i] = true; // Mengubah status putaran servo menjadi true
            printf("isServoRotated[%d] = true\n", i);
            
            // Jika Anda ingin servo hanya berputar sekali pada setiap jam makan,
            // Anda dapat keluar dari loop setelah servo berputar dengan menggunakan pernyataan "break"
            break;
        }
            printf("blom waktunya makan\n");
            printf("isServoRotated[%d] = %s\n", i, isServoRotated[i] ? "true" : "false");
    }



}


