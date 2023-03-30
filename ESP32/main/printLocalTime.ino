void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  //char dateStr[20];
  strftime(dateStr, sizeof(dateStr), "%d-%m-%Y", &timeinfo);
  Serial.println(dateStr);
}