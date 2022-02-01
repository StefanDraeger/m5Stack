#define NUM_LEDS 1
#define DATA_PIN 27

CRGB leds[NUM_LEDS];

int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int brightnessValue = 10;

void updateRgbLed() {
  leds[0].red = redValue;
  leds[0].green = greenValue;
  leds[0].blue = blueValue;
  FastLED.setBrightness(map(brightnessValue,0,100,1,255));
  FastLED.show();
}
