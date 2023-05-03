void drawLoadingBar() {
    static int progress = 0;
    
    // Get the screen width and height
    int screenWidth = tft.width();
    int screenHeight = tft.height();
    
    // Clear the sprite
    sprite.fillSprite(TFT_BLACK);
    
    // Draw the loading bar
    int barWidth = progress * LOADING_BAR_WIDTH / 100;
    sprite.fillRect(0, 20, barWidth, LOADING_BAR_HEIGHT, TFT_GREEN);
    
    // Display the percentage
    sprite.setTextColor(TFT_WHITE, TFT_BLACK);
    sprite.setTextSize(2);
    sprite.setCursor(LOADING_BAR_WIDTH/2 - 12, 0);
    sprite.print(String(progress) + "%");
    
    
    // Display the sprite on TFT
    sprite.pushSprite(screenWidth / 2 - LOADING_BAR_WIDTH / 2, screenHeight / 2 - (LOADING_BAR_HEIGHT + 20) / 2);
    
    // Increment the progress
    progress = (progress + 5) % 101;
}
