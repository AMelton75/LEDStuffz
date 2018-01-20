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

int LSDBreath = 0;
bool LSDup = true;

int state = 2;
Adafruit_DotStar strip = Adafruit_DotStar(STRIP_LENGTH, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == 0) {
    wierdRainbow();
  }
  if (state == 1) {
    rainbow();
  }
  if (state == 2) {
    LSD();
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

void rainbow() {
  for (int i = 0; i < STRIP_LENGTH / 3; i++) {
    strip.setPixelColor((i * 3), r, g, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 1), r, g, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 2), r, g, b);
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
  if (LSDup == true && LSDBreath <= 100) {
    LSDBreath++;
  }
  else if(LSDup == true){
    LSDup = false;
  }
  if (LSDup == false && LSDBreath >= 10) {
    LSDBreath--;
  }
  else if(LSDup == false){
    LSDup = true;
  }
  strip.show();
}







