#include <TFT_eSPI.h>
#include "bitmaps.h"

const int jumpButton = 15;

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite background = TFT_eSprite(&tft);

TFT_eSprite ground = TFT_eSprite(&tft);

TFT_eSprite stillDino = TFT_eSprite(&tft);
TFT_eSprite walk1Dino = TFT_eSprite(&tft);
TFT_eSprite walk2Dino = TFT_eSprite(&tft);
TFT_eSprite deadDino = TFT_eSprite(&tft);

bool gameOver;

int groundPosition;
int gameSpeed;

bool buttonPressed;

const int dinoX = 40;
const int dinoY = 191;
const int jumpLength = 11;
const int jumpHover = 8;
const int jumpHeight = 8;
bool inJump;
int jumpPosition;
int walkFrame;


void setup() {
  pinMode(jumpButton, INPUT_PULLUP);

  gameOver = 0;

  groundPosition = 0;
  gameSpeed = 6;

  inJump = 0;
  jumpPosition = 0;
  walkFrame = 0;

  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);

  background.createSprite(320, 240);

  ground.createSprite(ground_width, ground_height);
  ground.drawXBitmap(0, 0, ground_bits, ground_width, ground_height, TFT_DARKGREY, TFT_BLACK);

  stillDino.createSprite(dino_width, dino_height);
  stillDino.drawXBitmap(0, 0, still_bits, dino_width, dino_height, TFT_DARKGREY, TFT_BLACK);

  walk1Dino.createSprite(dino_width, dino_height);
  walk1Dino.drawXBitmap(0, 0, walk1_bits, dino_width, dino_height, TFT_DARKGREY, TFT_BLACK);

  walk2Dino.createSprite(dino_width, dino_height);
  walk2Dino.drawXBitmap(0, 0, walk2_bits, dino_width, dino_height, TFT_DARKGREY, TFT_BLACK);

  deadDino.createSprite(dino_width, dino_height);
  deadDino.drawXBitmap(0, 0, dead_bits, dino_width, dino_height, TFT_DARKGREY, TFT_BLACK);
}

void loop() {
  buttonPressed = !digitalRead(jumpButton);

  if (!gameOver) {
    background.createSprite(320, 240);
    background.fillSprite(TFT_WHITE);

    scroll_ground();
    updateDino();

    background.pushSprite(0, 0);
    background.deleteSprite();
  }
}

void scroll_ground() {
  groundPosition -= gameSpeed;

  if (groundPosition <= -ground_width) {
    groundPosition = 0;
  }

  if (groundPosition <= -ground_width + 320) {
    ground.pushToSprite(&background, groundPosition, 222, TFT_BLACK);
    ground.pushToSprite(&background, groundPosition + ground_width, 222, TFT_BLACK);
  } else {
    ground.pushToSprite(&background, groundPosition, 222, TFT_BLACK);
  }
}

void updateDino() {
  if (buttonPressed && !inJump) {
    walkFrame = 0;
    inJump = 1;
  }

  if (!inJump) {
    if (walkFrame >= 4) {
      walkFrame = 0;
    }

    if (walkFrame < 2) {
      walk1Dino.pushToSprite(&background, dinoX, dinoY, TFT_BLACK);
    } else {
      walk2Dino.pushToSprite(&background, dinoX, dinoY, TFT_BLACK);
    }
  } else {
    if (walkFrame < jumpLength) {
      jumpPosition += jumpHeight;
    } else if (walkFrame < jumpLength + jumpHover) {
      // do nothing to stay in the air for 2 frames
    } else if (walkFrame < jumpLength * 2 + jumpHover) {
      jumpPosition -= jumpHeight;
    } else {
      inJump = 0;
      jumpPosition = 0;
    }

    stillDino.pushToSprite(&background, dinoX, dinoY - jumpPosition, TFT_BLACK);
  }

  walkFrame++;
}