#include <FastLED.h>
#define NUM_LEDS 6

CRGBArray<NUM_LEDS> leds;

void setup() {
  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS);
}

int del = 100, dimres = 10, frameswitchspeed = 200, x, x2, u, u2, i, j, g, h, y;  //i = led number , u = fade value
// (dimres) sets the smoothness of the fades.
// (del) sets the animation speed(ms), the overall speed is also affected by (dimres)

long frontcolor = CRGB::Brown, backcolor = CRGB::Teal, flaircolor = CRGB::White, c1, c2 ;  // set desired acrylic animation colors.


void loop () {
  // Remove the "//" to run one of the four animation presets (one at a time)
  // =======================================================================
  
  // addframe () ;
  // frameswitch () ;
  // framecolorswap () ;
  // flair () ;
}


void flair () {

  // function to move the flaircolor across the front and the back acrylic.
  // call this function in the main loop to use the FLAIR ANIMATION.

  leds((NUM_LEDS / 2) - 1, 0) = frontcolor;
  leds(NUM_LEDS, NUM_LEDS / 2) = backcolor;
  delay(300);      //sets how frequently the flair occurs.
  int j = 0;
  for (j = 0; j < NUM_LEDS / 2; j++) {   //moves accros the frontcolor first
    i = j;
    if (j == NUM_LEDS / 2 - 1) {
      c1toc2dualtrans();
    }
    else {
      c1 = frontcolor, c2 = flaircolor ;
      c1toc2dual();
    }
  }
  for (j = NUM_LEDS / 2; j >= NUM_LEDS / 2  && j <= NUM_LEDS; j++) {  //move accros the backcolor
    c1 = backcolor, c2 = flaircolor ;
    i = j;
    c1toc2dual();
    leds((NUM_LEDS / 2) - 1, 0) = frontcolor;
  }
}

void frameswitch () {

  // function to switch visibility between the front and back acrylic.
  // call this function in the main loop to use the FRAME SWITCH ANIMATION.

  c1 = frontcolor, c2 = backcolor ;
  frontupdown();
  backupdown();
}

void addframe () {

  // function to fade on and off the back acrylic while keeping the front acrylic on.
  // call this function in the main loop to use the ADD FRAME ANIMATION.

  c1 = frontcolor, c2 = backcolor ;
  leds((NUM_LEDS / 2) - 1, 0) = frontcolor;
  backupbackdown();
}

void framecolorswap () {

  // function to simultaneously switch colors between the front and back acrylic.
  // call this function in the main loop to use the FRAME COLOR SWAP ANIMATION.

  c1 = frontcolor, c2 = backcolor;
  frontandbackcolorswap();
}

void c1toc2dual() {   //function to simultaneously fade two leds from one color to another.
  x = 0;
  x2 = dimres - 1;
  while (x < dimres) {     //fadedown
    u = 256 * x / dimres;
    u2 = 256 * x2 / dimres;
    leds[i] = c2;
    leds[i].fadeToBlackBy(u);
    leds[i + 1] = c1;
    leds[i + 1].fadeToBlackBy(u);
    FastLED.show();
    delay(del);
    x++;
    x2--;
  }
  x = dimres - 1;
  x2 = 0;
  while (x > 0) {       //fadeup
    u = 256 * x / dimres;
    u2 = 256 * x2 / dimres;
    leds[i] = c1;
    leds[i].fadeToBlackBy(u);
    leds[i + 1] = c2;
    leds[i + 1].fadeToBlackBy(u);
    FastLED.show();
    delay(del);
    x--;
    x2++;
  }
}

void c1toc2dualtrans() {   //function to transition flair from the front color to the back color
  x = 0;
  x2 = dimres - 1;
  while (x < dimres) {     //fadedown
    u = 256 * x / dimres;
    u2 = 256 * x2 / dimres;
    leds[i] = c2;
    leds[i].fadeToBlackBy(u);
    leds[i + 1] = backcolor;
    leds[i + 1].fadeToBlackBy(u);
    FastLED.show();
    delay(del);
    x++;
    x2--;
  }
  x = dimres - 1;
  x2 = 0;
  while (x > 0) {       //fadeup
    u = 256 * x / dimres;
    u2 = 256 * x2 / dimres;
    leds[i] = frontcolor;
    leds[i].fadeToBlackBy(u);
    leds[i + 1] = c2;
    leds[i + 1].fadeToBlackBy(u);
    FastLED.show();
    delay(del);
    x--;
    x2++;
  }
}

void frontupdown() {  //fades front acrylic in and out
  for (g = dimres - 1; g > 0; g--) { //fadeup front
    u = 256 * g / dimres;
    h = 0;
    delay(del);
    while (h < NUM_LEDS / 2) {
      i = h;
      leds[i] = c1;
      leds[i].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
    }
  }
  delay(frameswitchspeed);
  g = 0;
  while (g <= dimres) {   //fadedown front
    u = 255 * g / dimres;
    h = 0;
    delay(del);
    while (h < NUM_LEDS / 2) {
      i = h;
      leds[i] = c1;
      leds[i].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
    } g++;
  }
}

void backupdown() { //fades back acrylic in and out
  int g, h ;
  for (g = dimres - 1; g > 0; g--) { //fadeup back
    u = 256 * g / dimres;
    h = NUM_LEDS / 2;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      leds[i] = c2;
      leds[i].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
    }
  }
  delay(frameswitchspeed);
  g = 0;
  while (g <= dimres) {   //fadedown back
    u = 255 * g / dimres;
    h = NUM_LEDS / 2;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      leds[i] = c2;
      leds[i].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
    } g++;
  }
}

void backupbackdown() { //fades back acrylic in and out
  int g, h ;
  for (g = dimres - 1; g > 0; g--) { //fadeup back
    u = 256 * g / dimres;
    h = NUM_LEDS / 2;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      leds[i] = c2;
      leds[i].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
    }
  }
  delay(frameswitchspeed);
  g = 0;
  while (g <= dimres) {   //fadedown back
    u = 255 * g / dimres;
    h = NUM_LEDS / 2;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      leds[i] = c2;
      leds[i].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
    } g++;
  } delay(frameswitchspeed);
}

void frontandbackcolorswap() {  //fades and swaps the colors of the front and back acrylic

  for (g = 0; g < dimres; g++) {  //fadedown back and front
    u = 256 * g / dimres;
    h = NUM_LEDS / 2;
    y = 0;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      j = y;
      leds[i] = c2;
      leds[i].fadeToBlackBy(u);
      leds[j] = c1;
      leds[j].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
      y++;
    }
  }
  for (g = dimres - 1; g > 0; g--) { //fadeup back and front
    u = 256 * g / dimres;
    h = NUM_LEDS / 2;
    y = 0;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      j = y;
      leds[i] = c1;
      leds[i].fadeToBlackBy(u);
      leds[j] = c2;
      leds[j].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
      y++;
    }
  }
  for (g = 0; g < dimres; g++) {  //fadedown back and front
    u = 256 * g / dimres;
    h = NUM_LEDS / 2;
    y = 0;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      j = y;
      leds[i] = c1;
      leds[i].fadeToBlackBy(u);
      leds[j] = c2;
      leds[j].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
      y++;
    }
  }
  for (g = dimres - 1; g > 0; g--) { //fadeup back and front
    u = 256 * g / dimres;
    h = NUM_LEDS / 2;
    y = 0;
    delay(del);
    while (h < NUM_LEDS && h >= NUM_LEDS / 2) {
      i = h;
      j = y;
      leds[i] = c2;
      leds[i].fadeToBlackBy(u);
      leds[j] = c1;
      leds[j].fadeToBlackBy(u);
      FastLED.show();
      h++;
      i++;
      y++;
    }
  }
}
