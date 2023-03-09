#include <OneWire.h>
#include <DallasTemperature.h>


float suhuDS18B20;

float GetSuhu(){
    sensor.requestTemperatures();
    sensor.requestTemperatures();       // send the command to get temperatures
    tempC = sensor.getTempCByIndex(0);  // read temperature in °C
    tempF = tempC * 9 / 5 + 32; // convert °C to °F

    Serial.print("Temperature: ");
    Serial.print(tempC);    // print the temperature in °C
    Serial.print("°C");
    Serial.print("  ~  ");  // separator between °C and °F
    Serial.print(tempF);    // print the temperature in °F
    Serial.println("°F");

    delay(500);
}