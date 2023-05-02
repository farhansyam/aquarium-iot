void getServo(String waktu, String* arrayFeedTime,int numFeed, int delayservo){
    /*for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }

    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }*/
    for (int i = 0; i < numFeed; i++) {
        if (waktu == arrayFeedTime[i]) {
        servo1.write(180); // Menggerakkan servo
        Serial.println("saatnya makan");
        delay(delayservo); // Delay selama 1 detik
        servo1.write(0); // Kembali ke posisi semula
        }
        Serial.println("blom waktunya makan");
    }
}