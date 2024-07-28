#include <TFT_eSPI.h> 
#include "bitmaps.h"

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite ground = TFT_eSprite(&tft);
TFT_eSprite dino = TFT_eSprite(&tft);

bool gameOver;
int groundPosition;
int gameSpeed;
bool inJump;
int jumpPosition;


void setup() {
  groundPosition = 0;
  gameSpeed = 3;

  tft.init();
  tft.setRotation(3);

  background.createSprite(320, 240);
  ground.createSprite(ground_width, ground_height);

  tft.fillScreen(TFT_WHITE);
}

void loop() {
  while (1) {
    background.createSprite(320,240);
    background.fillSprite(TFT_WHITE);

    ground.createSprite(ground_width, ground_height);
    scroll_ground();

    background.pushSprite(0, 0);
    background.deleteSprite();
  }
}

void scroll_ground() {
  groundPosition -= gameSpeed;

  if (groundPosition <= -ground_width) {
    groundPosition = 0;
  }

  ground.drawXBitmap(0, 0, ground_bits, ground_width, ground_height, TFT_DARKGREY, TFT_BLACK);

  if (groundPosition <= -ground_width + 320) {
    ground.pushToSprite(&background, groundPosition, 222, TFT_BLACK);
    ground.pushToSprite(&background, groundPosition + ground_width, 222, TFT_BLACK);
  } else {
    ground.pushToSprite(&background, groundPosition, 222, TFT_BLACK);
  }
}