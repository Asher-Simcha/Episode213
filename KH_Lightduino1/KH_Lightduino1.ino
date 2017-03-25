
#include "FastLED.h"
#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    8
#define FRAMES_PER_SECOND  120

CRGB leds[NUM_LEDS];

int BRIGHTNESS;


void setup() {
  delay(3000); // 3 second delay for recovery
  
  Serial.begin(9600);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{

  int RedPot = analogRead(0); // This checks the pot connected to Analog Pin 7 and gives us a value between 0-1024
  int RedValue = map(RedPot, 70, 850, 0, 255); // This maps the value of the pot from 0-1020 to a value between 0-5
  if (RedValue > 255)
    RedValue = 255;
  if (RedValue < 0)
    RedValue = 0;
    
  int GreenPot = analogRead(1); // This checks the pot connected to Analog Pin 7 and gives us a value between 0-1024
  int GreenValue = map(GreenPot, 70, 850, 0, 255); // This maps the value of the pot from 0-1020 to a value between 0-
  if (GreenValue > 255)
    GreenValue = 255;
  if (GreenValue < 0)
    GreenValue = 0;    

  int BluePot = analogRead(2); // This checks the pot connected to Analog Pin 7 and gives us a value between 0-1024
  int BlueValue = map(BluePot, 70, 850, 0, 255); // This maps the value of the pot from 0-1020 to a value between 0-5
  if (BlueValue > 255)
    BlueValue = 255;
  if (BlueValue < 0)
    BlueValue = 0;

  BRIGHTNESS = analogRead(3); // This checks the pot connected to Analog Pin 7 and gives us a value between 0-1024
  int BrightValue = map(BRIGHTNESS, 70, 850, 0, 255); // This maps the value of the pot from 0-1020 to a value between 0-5
  if (BrightValue > 255)
    BrightValue = 255;
  if (BrightValue < 0)
    BrightValue = 0;

WriteDebug(RedPot, RedValue, GreenPot, GreenValue, BluePot, BlueValue);

LiteUpArray(RedValue, GreenValue, BlueValue, BrightValue);

//  leds[1].red = RedValue;
//  leds[1].green = GreenValue;
//  leds[1].blue = BlueValue;

}


void WriteDebug(int RedPot, int RedValue, int GreenPot, int GreenValue, int BluePot, int BlueValue)
{
  Serial.print(RedPot);
  Serial.print("//");
  Serial.print(RedValue); // debug -- Sends the value of the pot to the serial port
  Serial.print("\t");  // debug -- Sends a tab
  Serial.print(GreenPot);
  Serial.print("//");
  Serial.print(GreenValue); // debug -- Sends the value of the pot to the serial port
  Serial.print("\t");  // debug -- Sends a tab
  Serial.print(BluePot);
  Serial.print("//");
  Serial.print(BlueValue); // debug -- Sends the value of the pot to the serial port
  Serial.print("\t");  // debug -- Sends a tab
  Serial.print("\n");
}

void LiteUpArray(int RedValue, int GreenValue, int BlueValue, int BrightValue)
{
  for (int x = 0; x < NUM_LEDS; x++)
    leds[x].setRGB (RedValue, GreenValue, BlueValue);
   
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);
  FastLED.setBrightness(BrightValue);
}

