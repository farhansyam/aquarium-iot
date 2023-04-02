const int phPin = 12;
float Po = 0;
float PHStep;
int nilaiAnalogPH;
double teganganPH;

//untuk kalibrasi

float PH4 = 3.239;
float PH7 = 2.527;

void setup()
{
    pinMode(phPin,INPUT);
    Serial.begin(115200);
    
}

void loop()
{
    nilaiAnalogPH = analogRead(phPin);
    Serial.print("Nilai ADC PH: ");
    Serial.println(nilaiAnalogPH);
    teganganPH = 3.3 / 4095 * nilaiAnalogPH;
    Serial.print("Tegangan: ");
    Serial.println(teganganPH,3);

    PHStep = (PH4 - PH7) / 3;
    Po = 7.00 + ((PH7 -teganganPH) / PHStep);
    Serial.print("Nilai PH cairan: ");
    Serial.println(Po, 2);
    delay(3000);
    
}