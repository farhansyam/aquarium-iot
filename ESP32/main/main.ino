#include "Configuration.h"
#include <FirebaseESP32.h>
FirebaseData firebaseData;
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>


OneWire oneWire(SENSOR_SUHU);
DallasTemperature sensor(&oneWire);

void setup() {
    Serial.begin(115200);
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
    Firebase.setFloat(firebaseData, "/admin/aquarium-1/ph", randNumber);
    Firebase.setFloat(firebaseData, "/admin/aquarium-1/temp",Temperature);
    Firebase.setFloat(firebaseData, "/admin/aquarium-1/turbidity", randNumber);
    delay(1000);
    Serial.println(Temperature);

}