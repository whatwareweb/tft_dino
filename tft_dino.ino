#include <TFT_eSPI.h>
#include "bitmaps.h"

TFT_eSPI tft = TFT_eSPI();

uint16_t transparent = 0;
TFT_eSprite ground = TFT_eSprite(&tft);

int gameSpeed;

void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);

  gameSpeed = 2;

  // create ground sprite
  ground.setColorDepth(1);
  ground.createSprite(ground_width, ground_height);
  ground.fillSprite(TFT_WHITE);
  ground.drawXBitmap(0, 0, ground_bits, ground_width, ground_height, TFT_DARKGREY, TFT_WHITE);
  ground.setBitmapColor(TFT_DARKGREY, TFT_WHITE);
}

void loop() {
  ground.pushSprite(0, 225);
  ground.scroll(-gameSpeed);
}