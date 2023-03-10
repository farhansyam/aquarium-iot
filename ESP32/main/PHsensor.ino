float PHsensor(){
    int PH_value = analogRead(18);
    float Voltage= PH_value * (5 / 1024.0);
    Serial.println(Voltage);
    return Voltage;
    delay(500);
}