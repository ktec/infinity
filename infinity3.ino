#include <FastLED.h>

#define LED_PIN     12
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    144

#define BRIGHTNESS  50
#define FRAMES_PER_SECOND 300

float volume;
float our_signal;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {

  delay(3000); // sanity delay
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }

}

void loop() {
  volume = analogRead(A0);
  our_signal = 1023.0 - volume;
  Serial.println(our_signal);

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setHue(our_signal * 356/10);
    // FastLED.show(); // display this frame
    // delay(10);
  }

  FastLED.setBrightness( our_signal );
  FastLED.show(); // display this frame
  //FastLED.delay(1000 / FRAMES_PER_SECOND);
}
