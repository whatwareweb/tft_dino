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
int score = 0;

int groundPosition;
int gameSpeed;

bool buttonPressed;

const int dinoHitboxStart = 10;
const int dinoHitboxEnd = 27;
const int dinoX = 40;
const int dinoY = 191;
const int jumpLength = 11;
const int jumpHover = 8;
const int jumpHeight = 8;
bool inJump;
int jumpPosition;
int walkFrame;

TFT_eSprite cacti1Sprite = TFT_eSprite(&tft);
TFT_eSprite cacti2Sprite = TFT_eSprite(&tft);
TFT_eSprite cacti4Sprite = TFT_eSprite(&tft);

TFT_eSprite *cactusSprites[3] = {
  &cacti1Sprite,
  &cacti2Sprite,
  &cacti4Sprite
};

struct cactus {
  TFT_eSprite *sprite;
  int x;
  bool init;
};

const int cactiAmount = 4;
struct cactus cacti[cactiAmount];
const int cactiY = 185;

const int cactiHitboxX = 6;
const int cactiHitboxY = 10;

void setup() {
  pinMode(jumpButton, INPUT_PULLUP);

  gameOver = 1;

  groundPosition = 0;
  gameSpeed = 6;

  inJump = 0;
  jumpPosition = 0;
  walkFrame = 0;


  cactusSprites[0]->createSprite(cactus_width, cactus_height);
  cactusSprites[0]->drawXBitmap(0, 0, cactus_bits, cactus_width, cactus_height, TFT_DARKGREY, TFT_BLACK);

  cactusSprites[1]->createSprite(cacti2_width, cacti2_height);
  cactusSprites[1]->drawXBitmap(0, 0, cacti2_bits, cacti2_width, cacti2_height, TFT_DARKGREY, TFT_BLACK);

  cactusSprites[2]->createSprite(cacti4_width, cacti4_height);
  cactusSprites[2]->drawXBitmap(0, 0, cacti4_bits, cacti4_width, cacti4_height, TFT_DARKGREY, TFT_BLACK);


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

  background.createSprite(320, 240);
  background.fillSprite(TFT_WHITE);

  scroll_ground();
  updateDino();
  handleCacti();
  handleCollision();

  if (gameOver) {
    background.setTextSize(1);
    background.setTextFont(4);
    background.setTextColor(TFT_DARKGREY);
    background.setTextWrap(false);

    background.setCursor(100, 50);
    background.print("Game Over");

    background.setCursor(50, 90);
    background.print("Press Button to Start");

    background.pushSprite(0, 0);

    while (buttonPressed) {
      gameOver = 0;
      jumpPosition = 0;

      for (int i = 0; i < cactiAmount; i++) {
        cacti[i].init = 0;
      }

      delay(50);  // prevent ghost jump when starting game
      buttonPressed = !digitalRead(jumpButton);
    }
  }

  background.pushSprite(0, 0);
  background.deleteSprite();
}

void scroll_ground() {
  if (!gameOver) {
    groundPosition -= gameSpeed;

    if (groundPosition <= -ground_width) {
      groundPosition = 0;
    }
  }

  if (groundPosition <= -ground_width + 320) {
    ground.pushToSprite(&background, groundPosition, 222, TFT_BLACK);
    ground.pushToSprite(&background, groundPosition + ground_width, 222, TFT_BLACK);
  } else {
    ground.pushToSprite(&background, groundPosition, 222, TFT_BLACK);
  }
}

void updateDino() {
  if (!gameOver) {
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
        if (!buttonPressed) {
          walkFrame += jumpHover - (walkFrame - jumpLength);
        }
      } else if (walkFrame < jumpLength * 2 + jumpHover) {
        jumpPosition -= jumpHeight;
      } else {
        inJump = 0;
        jumpPosition = 0;
      }

      stillDino.pushToSprite(&background, dinoX, dinoY - jumpPosition, TFT_BLACK);
    }

    walkFrame++;
  } else {
    deadDino.pushToSprite(&background, dinoX, dinoY - jumpPosition, TFT_BLACK);
  }
}

void handleCacti() {
  if (!gameOver) {
    for (int i = 0; i < cactiAmount; i++) {
      if (cacti[i].x <= -cacti[i].sprite->width()) {
        cacti[i].x = 320 * cactiAmount + random(-50, 50);
        cacti[i].sprite = cactusSprites[random(3)];
      }
      cacti[i].x -= gameSpeed;

      if (cacti[i].x <= dinoX) {
        score++;
      }

      cacti[i].sprite->pushToSprite(&background, cacti[i].x, cactiY, TFT_BLACK);
    }
  } else {
    for (int i = 0; i < cactiAmount; i++) {
      if (!cacti[i].init) {
        cacti[i].sprite = cactusSprites[random(3)];
        cacti[i].x = 320 * (i + 2) + random(-50, 50);
        cacti[i].init = 1;
      }

      cacti[i].sprite->pushToSprite(&background, cacti[i].x, cactiY, TFT_BLACK);
    }
  }
}

void handleCollision() {
  if (!gameOver) {
    for (int i = 0; i < cactiAmount; i++) {
      if (
        dinoX + dinoHitboxStart < cacti[i].x + cacti[i].sprite->width() - cactiHitboxX &&
        dinoX + dinoHitboxEnd > cacti[i].x + cactiHitboxX &&
        dinoY - jumpPosition + dino_height > cactiY + cactiHitboxY
      ) {
        Serial.println(dinoY);
        Serial.println(cactiY);
        Serial.println();
        gameOver = 1;
      }
    }
  }
}