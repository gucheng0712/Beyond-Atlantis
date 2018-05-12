# Serial sending messages from TouchDesigner to Arduino
This is a tutorial about sending messages from TouchDesigner to Arduino

## 1. Download & Install Arduino IDE
Download it from [Arduino’s main download page](https://www.arduino.cc/en/Main/Software) and install it.

## 2. Download & install TeensyDuino 
Be sure your Arduino IDE is not running. Go to [PJRC’s Teensyduino download link](https://www.pjrc.com/teensy/td_download.html) to download correct verison, and install it.

## 3. Download <Adafruit_NeoPixel.h> Library> in Arduino
In Arduino, Go to `Sketch` --> `Include Library` --> `Manage Library`, search for `"Adafruit_NeoPixel"`, and install it.

## 4. Write Code in Arduino for Receiving Messages
```
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 824 // The number of Led Lights
#define DIN_PIN 6 // The Pin Number of your Led (Din)wire

uint32_t pix[NUM_PIXELS];
char input[NUM_PIXELS * 3 ]; // total input value, led num * 3 (each led has r, g, b three value)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  Serial.begin(1382400); //Baud Rate
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
/*-------------------Important: the serial print will slow down the message sending speed----------------------*/
      //Serial.print("input was.. ");  
      //Serial.print(r);
      //Serial.println(g);
      //Serial.println(b);
    }
    strip.show();
  }
}

```

## 5. Write Code to Send message from TouchDesigner to Arduino
In TouchDesigner there is an Excute DAT, will give you a function `onFrameEnd()`, which will call this method every frame. Using that to send message from TouchDesigner to Arduino by Serial.

For example:
    I want to send a whole chan's values from a chop, I can do like this:
```
def onFrameEnd(frame):
    num = op("THE NAME OF THE CHOP")
    op("THE NAME OF THE CHOP").sendBytes(*num[0].vals)
    return
```

## Successfully Receive message
