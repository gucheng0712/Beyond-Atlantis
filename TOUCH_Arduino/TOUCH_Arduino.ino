#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 824
#define DIN_PIN 6

uint32_t pix[NUM_PIXELS];
char input[NUM_PIXELS * 3 ];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  Serial.begin(1382400);
}

void loop()
{
  int r, g, b;
  char charsRead;
  if (Serial.available() > 0)
  {
    charsRead = Serial.readBytes(input, NUM_PIXELS * 3);

    for (int i = 0; i < NUM_PIXELS; i++)
    {
      r = input[i * 3];
      g = input[i * 3 + 1];
      b = input[i * 3 + 2];

      pix[i] = strip.Color(r, g, b);
      strip.setPixelColor(i, pix[i]);
      //Serial.print("input was.. ");
      //Serial.print(r);
      //Serial.println(g);
      //Serial.println(b);
    }
    strip.show();
  }


  //Serial.print("Hex input was.. ");
  //Serial.println(input);
}


