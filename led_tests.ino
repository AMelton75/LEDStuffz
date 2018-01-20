#include <Adafruit_DotStar.h>
#include <SPI.h>
#define DATAPIN 4
#define CLOCKPIN 5

const int STRIP_LENGTH = 242;

int r = 0;
int g = 0;
int b = 0;

int ri = 1;
int gi;
int bi;

int light = 25;
int lightd = 1;

int LSDBreath = 0;
bool LSDup = true;

int snake = 0;
int state = 1;
Adafruit_DotStar strip = Adafruit_DotStar(STRIP_LENGTH, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

int current = millis();
int reset = millis();
void setup() {
  //put your setup code here, to run once:
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  current = millis();
  if (current - reset >= 30000) {
    state++;
    if (state >= 4) {
      state = 0;
    }
    reset = millis();
    r = 0;
    g = 0;
    b = 0;

    ri = 1;
    gi = 0;
    bi = 0;

    light = 25;
    lightd = 1;

    LSDBreath = 0;
    LSDup = true;

    snake = 0;
  }
  if (state == 0) {
    wierdRainbow();
  }
  if (state == 1) {
    rainbowSnake();
  }
  if (state == 2) {
    LSD();
  }
  if (state == 3) {
    rainbowCool();
  }


  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
}

void wierdRainbow() {
  for (int i = 0; i < STRIP_LENGTH / 3; i++) {
    strip.setPixelColor((i * 3), r, g, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 1), b, r, g);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 2), g, b, r);
  }
  strip.show();
  if (r >= 50) {
    ri = -1;
    gi = 1;
    bi = 0;
  }
  if (g >= 50) {
    gi = -1;
    bi = 1;
    ri = 0;
  }
  if (b >= 50) {
    bi = -1;
    ri = 1;
    gi = 0;
  }
  r += ri;
  g += gi;
  b += bi;
}

void rainbowSnake() {
  for (int i = 0; i < STRIP_LENGTH / 3; i++) {
    strip.setPixelColor((i * 3), r, g, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 1), r, g, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 2), r, g, b);
  }
  for (int i = 0; i < 50; i++) {
    strip.setPixelColor((snake - i), i + 5, i + 5, i + 5);
  }
  snake++;
  if (snake - 50 >= STRIP_LENGTH) {
    snake = 0;
  }
  strip.show();
  if (r >= 50) {
    ri = -1;
    gi = 1;
    bi = 0;
  }
  if (g >= 50) {
    gi = -1;
    bi = 1;
    ri = 0;
  }
  if (b >= 50) {
    bi = -1;
    ri = 1;
    gi = 0;
  }
  r += ri;
  g += gi;
  b += bi;
  delay(20);
}

void LSD() {
  for (int i = 0; i < STRIP_LENGTH; i++) {
    strip.setPixelColor((i), r, g, b);
    r = random(0, LSDBreath);
    g = random(0, LSDBreath);
    b = random(0, LSDBreath);
  }
  if (LSDup == true && LSDBreath <= 50) {
    LSDBreath++;
  }
  else if (LSDup == true) {
    LSDup = false;
  }
  if (LSDup == false && LSDBreath >= 10) {
    LSDBreath--;
  }
  else if (LSDup == false) {
    LSDup = true;
  }
  strip.show();
}

void rainbowCool() {
  for (int i = 0; i < STRIP_LENGTH; i++) {
    strip.setPixelColor((i), r * 25 / light, g * 25 / light, b * 25 / light);
  }
  strip.show();
  if (r >= 50) {
    ri = -1;
    gi = 1;
    bi = 0;
  }
  if (g >= 50) {
    gi = -1;
    bi = 1;
    ri = 0;
  }
  if (b >= 50) {
    bi = -1;
    ri = 1;
    gi = 0;
  }
  if (light >= 50 ) {
    lightd = -1;
  }
  if (light <= 25 ) {
    lightd = 1;
  }
  r += ri;
  g += gi;
  b += bi;
  light += lightd;
  delay(20);
}





