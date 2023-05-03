void menu(){
    if (tft.getTouch(&x, &y)) {
        if(SwitchOn){
            tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
            if (x >= monitor_x && x <= monitor_x + monitor_width && y >= monitor_y && y <= monitor_y + monitor_height) {
                tft.fillScreen(TFT_BLACK);
                //tft.drawString("PENGURAS AIR",220,10,2);
                tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
                tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                SwitchOn = false;
             // contoh: tampilkan menu monitor
            }
            if(x >= wifilogo_x && x <= wifilogo_x + wifilogo_width && y >= wifilogo_y && y <= wifilogo_y + wifilogo_height){
                //untuk aktifkan wifi
                //wifimanager();
            }

        

        }else{
            //tft.drawString("PENGURAS AIR",220,10,2);
            tft.pushImage(pompa_x, pompa_y, pompa_width, pompa_height, pompa);
            if (x >= pompa_x && x <= pompa_x + pompa_width &&  y >= pompa_y && y <= pompa_y + pompa_height) {
                tft.fillScreen(TFT_BLACK);
                tft.pushImage(monitor_x, monitor_y, monitor_width, monitor_height, monitor);
                digitalWrite(relay1,HIGH);
                SwitchOn = true;
                SwitchButton = true;
            }
            if(SwitchButton){
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width+5 &&  y >= buttonOnOff_y+15 && y <= buttonOnOff_y+15 + buttonOnOff_height-30){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y+15,buttonOnOff_width+5,buttonOnOff_height-40,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,ON);
                    digitalWrite(relay1,LOW);
                    SwitchButton = false;
                }
            }else{
                if (x >= buttonOnOff_x && x <= buttonOnOff_x + buttonOnOff_width+5 &&  y >= buttonOnOff_y+15 && y <= buttonOnOff_y + buttonOnOff_height-30){
                    tft.fillRect(buttonOnOff_x,buttonOnOff_y+15,buttonOnOff_width+5,buttonOnOff_height-40,TFT_BLACK);
                    tft.pushImage(buttonOnOff_x,buttonOnOff_y,buttonOnOff_width,buttonOnOff_height,OFF);
                    digitalWrite(relay1,HIGH);
                    SwitchButton = true;
                }
                // kode untuk mengaktifkan pompa air
            }
            Serial.printf("switchbutton: %d \n",SwitchButton);
            

        }
        Serial.printf("SwitchOn: %d \n",SwitchOn);
    }
}