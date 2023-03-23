float getTurbidity (){
  V = 0;
  for(int i=0; i<800; i++)
  {
    V += ((float)analogRead(14)/1023)*5;
  }
  VRata2 = V/800;
  VHasil = roundf(VRata2*10.0f)/10.0f;
  VFinal = VHasil-7;
  kekeruhan = -1120.4*sq(VFinal)+5742.3*VFinal-4353.8; //Air Jernih 13488 //kalo sqrt itu = akar, kalo sq itu = perpangkatan 2
  akhir = kekeruhan-13488;
  if(VFinal <2.5){
    kekeruhan = 3000;
    Serial.print("tegangan :");
    Serial.print(VFinal);
    Serial.print(" V");
    Serial.print("\t kekeruhan :");
    Serial.println(kekeruhan);
    tft.setCursor(4,189);
    tft.setTextColor(TFT_RED); tft.setTextSize(3);
    tft.print("KERUH ="); tft.print(kekeruhan); tft.println(" NTU");
    }
  else{
    Serial.print("tegangan :");
    Serial.print(VFinal);
    Serial.print(" V");
    Serial.print("\t kekeruhan :");
    Serial.println(akhir);
    tft.setCursor(4,189);
    tft.setTextColor(TFT_RED); tft.setTextSize(3);
    tft.print("KERUH ="); tft.print(akhir); tft.println(" NTU");
    }
  Serial.print("V sebenarnya : "); Serial.println(VHasil);
}