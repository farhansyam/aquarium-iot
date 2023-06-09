void menu(){
    if (tft.getTouch(&x, &y)) {
        if(SwitchOn){
            if(WiFi.status() == 6){
                tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
                tft.pushImage(wifilogo_x,wifilogo_y,wifilogo_width,wifilogo_height,lost_connections);
            }
            if (x >= monitor_x && x <= monitor_x + monitor_width && y >= monitor_y && y <= monitor_y + monitor_height) {
                tft.fillScreen(TFT_BLACK);
                //tft.drawString("PENGURAS AIR",220,10,2);
                tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
                tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                digitalWrite(relay1,LOW);
                SwitchOn = false;
             // contoh: tampilkan menu monitor
            }
            if(x >= wifilogo_x && x <= wifilogo_x + wifilogo_width && y >= wifilogo_y && y <= wifilogo_y + wifilogo_height){
                
                if(WiFi.status() == 6 || WiFi.status() == 255  ){
                    tft.fillRect(wifilogo_x,wifilogo_y,wifilogo_width,wifilogo_height,TFT_BLACK);
                    tft.pushImage(wifilogo_x,wifilogo_y,wifilogo_width,wifilogo_height,loading);
                    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
                    Serial.println();
                    Serial.println("******************************************************");
                    Serial.print("Connecting to ");
                    Serial.println(WIFI_SSID);
                    if(WiFi.status() == 3){
                        Serial.println("conected"); 
                        //tft.fillRect(wifilogo_x, wifilogo_y, wifilogo_width, wifilogo_height, TFT_BLACK);
                        //tft.pushImage(wifilogo_x, wifilogo_y, wifilogo_width, wifilogo_height, connections);
                        ESP.restart();
                    }
                    
                    /*wm.resetSettings();

                    // res = wm.autoConnect(); // auto generated AP name from                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
                    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
                    bool res = wm.autoConnect("AutoConnectAP","password"); // password protected 

                    //wm.setCleanConnect(true);
                    if(!res) {
                        Serial.println("Failed to connect");
                        ESP.restart();
                    } */

                }

            }

        

        }else{
            //tft.drawString("PENGURAS AIR",220,10,2);
            tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
            if (x >= pompa_x && x <= pompa_x + pompa_width &&  y >= pompa_y && y <= pompa_y + pompa_height) {
                tft.fillScreen(TFT_BLACK);
                tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
                digitalWrite(relay1,LOW);
                SwitchOn = true;
                SwitchButton = true;
            }
            if(SwitchButton){
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width+5 &&  y >= buttonOnOff_y+15 && y <= buttonOnOff_y+15 + buttonOnOff_height-30){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y+15,buttonOnOff_width+5,buttonOnOff_height-40,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,ON);
                    digitalWrite(relay1,HIGH); 
                    SwitchButton = false;
                }
            }else{
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width+5 &&  y >= buttonOnOff_y+15 && y <= buttonOnOff_y + buttonOnOff_height-30){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y+15,buttonOnOff_width+5,buttonOnOff_height-40,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                    digitalWrite(relay1,LOW);
                    SwitchButton = true;
                }
                // kode untuk mengaktifkan pompa air
            }
            Serial.printf("switchbutton: %d \n",SwitchButton);
            

        }
        Serial.printf("SwitchOn: %d \n",SwitchOn);
    }
}