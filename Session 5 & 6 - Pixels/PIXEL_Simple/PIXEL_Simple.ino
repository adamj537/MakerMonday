#include <Adafruit_NeoPixel.h>

#define PIN			6		// pin the pixels are connected to
#define NUMPIXELS	18		// how many pixels we have
#define DELAY		500		// how long to wait between changes [ms]

// Tell the NeoPixel library how many of what kind exist on what pin.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	pixels.begin();
}

void loop()
{
	uint32_t color;
	
	for (int i = 0; i < NUMPIXELS; i++)
	{
		// This is a moderately bright green color.
		color = pixels.Color(0,150,0);
		
		pixels.setPixelColor(i, color);

		pixels.show();

		delay(DELAY);
	}
}
