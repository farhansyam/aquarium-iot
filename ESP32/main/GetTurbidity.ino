int pinTurb = 34;
float V;
float kekeruhan;
float VRata2;
float VHasil;

void setup()
{
  Serial.begin(9600);
  Serial.println("SENSOR KEKERUHAN AIR");
  delay(2000);
}

void loop()
{
  V = 0;
  for(int i=0; i<800; i++)
  {
    V += ((float)analogRead(pinTurb)/4095)*3.3;
  }

  VRata2 = V/800;
  VHasil = roundf(VRata2*10.0f)/10.0f;

  if(VHasil < 1.25)
  {
    kekeruhan = 3000;
  }
  else
  {
    kekeruhan = -1120.4*pow(VHasil, 2) + 5742.3*VHasil - 4353.8;
  }

  Serial.print("Tegangan: ");
  Serial.print(VHasil, 1);
  Serial.print(" V");

  Serial.print("\tKekeruhan: ");
  Serial.print(kekeruhan);
  Serial.println(" NTU");
  delay(10);
}
