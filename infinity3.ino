#include <FastLED.h>

#define LED_PIN     12
#define POT_IN      A0
#define AUDIO_IN_PIN A1
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    144

#define BRIGHTNESS  100
#define FRAMES_PER_SECOND 300

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

  //ledHue = map(audioInValue, 0, 1023, 0, BRIGHTNESS);

  for(int i = 0; i < NUM_LEDS; i++) {
    int audioInValue = analogRead(AUDIO_IN_PIN);
    int brightness = map(audioInValue, 0, 1023, BRIGHTNESS, 10);
    Serial.println(brightness);
    int potInValue = analogRead(POT_IN);
    int hue = map(potInValue, 0, 1023, 0, 255);
    leds[i].setHue( hue );
    FastLED.setBrightness( brightness );
    FastLED.show(); // display this frame
    delay(10);
  }

  //FastLED.delay(1000 / FRAMES_PER_SECOND);
}
