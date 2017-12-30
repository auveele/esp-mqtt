
/*########################
##########################

  strip_main.ino

  Este archivo contiene los elementos básicos de La tira LED

##########################
########################*/

Ticker ledsTimer;

void setup_strip() {
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(Brightness);
  ledsTimer.once(0.025, loop_strip);
}

void loop_strip() {
  leds_clear();
  ledsTimer.once(0.01, draw_animation);
}

void draw_animation(){
  switch (ANIMATION) {
    case 1:
      CylonBounce(255, 0, 0, 0, 4, 5, 50);
      break;
    case 2:
      Sparkle(255,255,255,255,30);
      break;
    default:
      setAll(0,0,0,0);
  }
  showStrip();
  ledsTimer.once(0.025, loop_strip);
}

/*
 *  RELLENO COMPLETO RGBW
 */
void setRed()   { setAll(255,0,0,0); }
void setGreen() { setAll(0,255,0,0); }
void setBlue()  { setAll(0,0,255,0); }
void setWhite() { setAll(0,0,0,255); }

/*
 * AUXILIARES
 */
void leds_clear() { setAll(0,0,0,0); }
void showStrip() { FastLED.show(); }
void setPixel(byte p, byte r, byte g, byte b, byte w) { leds[p] = CRGBW(r, g, b, w); }

void setAll(byte red, byte green, byte blue, byte white ) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue, white); 
  }
}




