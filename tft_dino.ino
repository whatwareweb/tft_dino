#include <TFT_eSPI.h> 
#include "bitmaps.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background= TFT_eSprite(&tft);

TFT_eSprite ground= TFT_eSprite(&tft);

int gameSpeed = 3;

void setup() {
 tft.init();
 tft.setRotation(3);

 background.createSprite(320, 240);
 ground.createSprite(ground_width, ground_height);
 ground.drawXBitmap(0, 0, ground_bits, ground_width, ground_height, TFT_DARKGREY, TFT_BLACK);
}

void loop() {
 background.fillSprite(TFT_WHITE);

 ground.pushToSprite(&background, 0, 222, TFT_BLACK);
 ground.scroll(-gameSpeed);
 
 background.pushSprite(0, 0);
}
