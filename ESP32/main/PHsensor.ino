float PHsensor()
{
    nilaiAnalogPH = analogRead(phPin);
    teganganPH = 3.3 / 4095 * nilaiAnalogPH;
    sumTegangan += teganganPH;
    countTegangan++;

    if (countTegangan == 10) { // hitung rata-rata setiap 10 kali pembacaan
        float rataTegangan = sumTegangan / countTegangan;
        PHStep = (PH4 - PH7) / 3;
        Po = 7.00 + ((PH7 - rataTegangan) / PHStep);
        Serial.print("Nilai PH cairan: ");
        Serial.println(Po, 2);
        Serial.print("Rata-rata tegangan: ");
        Serial.println(rataTegangan, 3);
        sumTegangan = 0;
        countTegangan = 0;
    }
    
    delay(500); // tunggu 1 detik sebelum melakukan pembacaan berikutnya
}
