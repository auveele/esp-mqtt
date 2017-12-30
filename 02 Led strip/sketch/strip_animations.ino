
/*########################
##########################

  strip_animationsn.ino

  Este archivo contiene las funciones de las animaciones para la tira LED

##########################
########################*/

int led_loop = 0;
boolean led_direction = HIGH;

/*
 * REBOTES
 */
void CylonBounce(byte red, byte green, byte blue, byte white, int EyeSize, int SpeedDelay, int ReturnDelay){
  // PINTAMOS PIXELES
  if (led_direction == HIGH) {
    if (led_loop < NUM_LEDS-EyeSize-2) {
      // CABEZA
      setPixel(led_loop, red/10, green/10, blue/10, white/10);
      // CUERPO
      for(int j = 1; j <= EyeSize; j++) {
        setPixel(led_loop+j, red, green, blue, white); 
      }
      // COLA
      setPixel(led_loop+EyeSize+1, red/10, green/10, blue/10, white/10);
      led_loop++;
    } else {
      led_direction = LOW;
    }
  } else {
    if (led_loop > 0) {
       // CABEZA
       setPixel(led_loop, red/10, green/10, blue/10, white/10);
       // CUERPO
       for(int j = 1; j <= EyeSize; j++) {
         setPixel(led_loop+j, red, green, blue, white); 
       }
       // COLA
       setPixel(led_loop+EyeSize+1, red/10, green/10, blue/10, white/10);
       led_loop--;
    } else {
       led_direction = HIGH;
    }    
  }
}

/*
 * SPARKLES
 */
void Sparkle(byte red, byte green, byte blue, byte white, int SpeedDelay) {
  int p = random(NUM_LEDS);
  setPixel(p,red,green,blue,white);
  showStrip();
  setPixel(p,red/10,green/10,blue/10,white/10);
}

