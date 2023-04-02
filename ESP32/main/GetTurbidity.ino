float getTurbidity (){
  float V = 0;
  float kekeruhan, akhir, VRata2, VHasil;
  for(int i=0; i<800; i++)
  {
    V += ((float)analogRead(34)/4095)*5;
  }
  VRata2 = V/800;
  VHasil = roundf(VRata2*10.0f)/10.0f;
  VFinal = VHasil-7;
  kekeruhan = -1120.4*powf(VFinal,2)+5742.3*VFinal-4353.8;
  akhir = kekeruhan-13488;
  if(VFinal <2.5){
    kekeruhan = 3000;
    Serial.print("tegangan :");
    Serial.print(VFinal);
    Serial.print(" V");
    Serial.print("\t kekeruhan :");
    Serial.println(kekeruhan);
  }
  else{
    Serial.print("tegangan :");
    Serial.print(VFinal);
    Serial.print(" V");
    Serial.print("\t kekeruhan :");
    Serial.println(akhir);
  }
  Serial.print("V sebenarnya : "); Serial.println(VHasil);
  return kekeruhan;
}
