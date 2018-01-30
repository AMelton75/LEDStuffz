#include <Adafruit_DotStar.h>
#include <SPI.h>
#define DATAPIN 4
#define CLOCKPIN 5

const int STRIP_LENGTH = 240;

int r = 0;
int g = 0;
int b = 0;

int ri = 1;
int gi;
int bi;

int light = 25;
int lightd = 1;

int rstart=0;
int gstart=80;
int bstart=160;

int why;

int LSDBreath = 0;
bool LSDup = true;

int snake = 0;
int state = 7;

int ballX = 2;
int ballSpeed = 2;
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
  if (current - reset >= 3000000) {
    state++;
    if (state >= 8) {
      state = 5;
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

    rstart=0;
    gstart=80;
    bstart=160;

    LSDBreath = 0;
    LSDup = true;

    snake = 0;

    ballX = 2;
    ballSpeed = 2;
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
  if (state == 4){
    ball();  
  }
  if (state == 5){
    BetterSnake();  
  }
  if (state == 6){
    pink();  
  }
  if (state == 7){
    moveingrainbow();  
  } 
}

void wierdRainbow() {
  for (int i = 0; i < STRIP_LENGTH / 3; i++) {
    strip.setPixelColor((i * 3), g, r, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 1), b, g, r);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 2), r, b, g);
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
    strip.setPixelColor((i * 3), g, r, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 1), g, r, b);
  }
  for (int j = 0; j < STRIP_LENGTH / 3; j++) {
    strip.setPixelColor((j * 3 + 2), g, r, b);
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
    strip.setPixelColor((i), g, r, b);
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
    strip.setPixelColor((i), g * 25 / light, r * 25 / light, b * 25 / light);
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

void ball(){
  if(ballX >= STRIP_LENGTH || ballX <= 0){
    ballSpeed = ballSpeed*-1;  
  }
  ballX += ballSpeed;
  for(int i = 0; i < STRIP_LENGTH; i++){
    strip.setPixelColor((i), 0, 20 + ballX / 10, 5 + ballX / 20); 
  }
  strip.setPixelColor((ballX), 50, 50, 50);  
}

void BetterSnake(){

  for(int i = 1; i < 81; i++){
    strip.setPixelColor(((rstart+i)%STRIP_LENGTH),0,50,0);
  }
  for(int i = 1; i < 81; i++){
    strip.setPixelColor(((gstart+i)%STRIP_LENGTH),50,0,0);
  }
  for(int i = 1; i < 81; i++){
    strip.setPixelColor(((bstart+i)%STRIP_LENGTH),0,0,50);
  }
  
rstart++;
gstart++;
bstart++;
strip.show();
}

void whynot(){
why++;
if((why%3)==1){
for(int i = 0; i < STRIP_LENGTH; i++){
    strip.setPixelColor((i),5,25,15);
} }else if((why%3)==2){
  for(int i = 0; i < STRIP_LENGTH; i++){
    strip.setPixelColor((i),25,15,5);
  } }else if((why%3)==0){
  for(int i = 0; i < STRIP_LENGTH; i++){
    strip.setPixelColor((i),15,5,25);
  }
}
strip.show();
}

void pink(){
if (light >= 70 ) {
    lightd = -1;
  }
  if (light <= 30 ) {
    lightd = 1;
  }
  light += lightd;
  for (int i = 0; i < STRIP_LENGTH; i++) {
    strip.setPixelColor((i), 1, 40 * 50 / light, 24 * 50 / light);
  }

strip.show();
}

void moveingrainbow(){

for (int i = 0; i < 80; i++) {
    strip.setPixelColor(((i+rstart)%240),i/2,(80-i)/2,0);
  }
for (int i = 0; i < 80; i++) {
    strip.setPixelColor(((i+rstart+80)%240),(80-i)/2,0,i/2);
  }
for (int i = 0; i < 80; i++) {
    strip.setPixelColor(((i+rstart+160)%240),0,i/2,(80-i)/2);
  }
rstart++;
strip.show();
}

