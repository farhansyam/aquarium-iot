void wifimanager(){
    WiFiManager wm;
    wm.setConfigPortalTimeout(360);
    if (!wm.startConfigPortal("OnDemandAP")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      //ESP.restart();
      delay(5000);
    }
    Serial.println("connected...yeey :)");
}