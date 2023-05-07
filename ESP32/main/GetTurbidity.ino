void getTurbidity (){
  unsigned long previousMillis = 0;
  const long interval = 100;
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int totalADCValue = 0;
    int numReadings = 1000;

    for(int i=0; i<numReadings; i++){
      V = ((float)analogRead(pinTurb)/4095)*3.3; // Mengubah rumus untuk tegangan dan ADC ESP32
      int ADCValue = round(V*4095/3.3); // Menghitung nilai ADC yang sesuai dengan tegangan
      totalADCValue += ADCValue;
    }

    // Menghitung rata-rata nilai ADC
    int averageADCValue = totalADCValue / numReadings;

    // Menghitung nilai kekeruhan dalam persen
    kekeruhan = ((CleanWaterADCValue - averageADCValue) * RangeKekeruhan) / RangeADC;

    // Pastikan nilai kekeruhan tidak melebihi 100% atau kurang dari 0%
    if(kekeruhan > 100) kekeruhan = 100;
    else if(kekeruhan < 0) kekeruhan = 0;

    Serial.print("kekeruhan : ");
    Serial.print(kekeruhan);
    Serial.println(" %");
    Serial.print("ADC : ");
    Serial.print(averageADCValue);
    Serial.println(" %");
  }


}