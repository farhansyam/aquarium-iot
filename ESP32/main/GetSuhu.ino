float GetSuhu(){
    sensor.requestTemperatures();       // send the command to get temperatures
    tempC = sensor.getTempCByIndex(0);  // read temperature in °C
    return tempC;
    //Serial.println(tempC);
    delay(500);
}