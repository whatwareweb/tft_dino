#include <TFT_eSPI.h>
#include "bitmaps.h"

TFT_eSPI tft = TFT_eSPI();

uint16_t transparent = 0;
TFT_eSprite ground = TFT_eSprite(&tft);
TFT_eSprite stillDino = TFT_eSprite(&tft);
TFT_eSprite walk1Dino = TFT_eSprite(&tft);
TFT_eSprite walk2Dino = TFT_eSprite(&tft);
TFT_eSprite deadDino = TFT_eSprite(&tft);

int gameSpeed;

void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);

  gameSpeed = 3;

  // create ground sprite
  ground.setColorDepth(1);
  ground.createSprite(ground_width, ground_height);
  ground.fillSprite(TFT_WHITE);
  ground.drawXBitmap(0, 0, ground_bits, ground_width, ground_height, TFT_DARKGREY, transparent);
  ground.setBitmapColor(TFT_DARKGREY, TFT_WHITE);

  // create dino sprites
  stillDino.setColorDepth(1);
  stillDino.createSprite(still_width, still_height);
  stillDino.fillSprite(TFT_WHITE);
  stillDino.drawXBitmap(0, 0, still_bits, still_width, still_height, TFT_DARKGREY, transparent);
  stillDino.setBitmapColor(TFT_DARKGREY, TFT_WHITE);

  walk1Dino.setColorDepth(1);
  walk1Dino.createSprite(walk1_width, walk1_height);
  walk1Dino.fillSprite(TFT_WHITE);
  walk1Dino.drawXBitmap(0, 0, walk1_bits, walk1_width, walk1_height, TFT_DARKGREY, transparent);
  walk1Dino.setBitmapColor(TFT_DARKGREY, TFT_WHITE);

  walk2Dino.setColorDepth(1);
  walk2Dino.createSprite(walk2_width, walk2_height);
  walk2Dino.fillSprite(TFT_WHITE);
  walk2Dino.drawXBitmap(0, 0, walk2_bits, walk2_width, walk2_height, TFT_DARKGREY, transparent);
  walk2Dino.setBitmapColor(TFT_DARKGREY, TFT_WHITE);

  deadDino.setColorDepth(1);
  deadDino.createSprite(dead_width, dead_height);
  deadDino.fillSprite(TFT_WHITE);
  deadDino.drawXBitmap(0, 0, dead_bits, dead_width, dead_height, TFT_DARKGREY, transparent);
  deadDino.setBitmapColor(TFT_DARKGREY, TFT_WHITE);
}

void loop() {
  ground.pushSprite(0, 222, transparent);
  stillDino.pushSprite(40,190, transparent);
  ground.scroll(-gameSpeed);
  delay(10);
}