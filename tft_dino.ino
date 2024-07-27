#include <TFT_eSPI.h>
#include "bitmaps.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
}

void loop() {

}
