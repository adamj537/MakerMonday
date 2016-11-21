#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN			6	// pin the pixels are connected to
#define PIXEL_COUNT			18	// how many pixels we have
#define PIXEL_BRIGHTNESS	80	// how bright to make the pixels (0-255)
#define SHORT_DELAY			20	// a small amount of time to wait for rainbows [ms]
#define LONG_DELAY			100	// time to wait for other effects [ms]

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	strip.begin();
	
	strip.setBrightness(PIXEL_BRIGHTNESS);
	
	strip.show();
}

void loop()
{
	theaterChase(strip.Color(127, 127, 127));	// White
	theaterChase(strip.Color(127, 0, 0));		// Red
	theaterChase(strip.Color(0, 0, 127));		// Blue
}

// Theatre-style crawling lights.
void theaterChase(uint32_t color)
{
	int j;
	int q;
	int i;
	
	// Do 10 cycles of chasing.
	for (j = 0; j < 10; j++)
	{
		for (q = 0; q < 3; q++)
		{
			// Turn every third pixel on.
			for (i = 0; i < PIXEL_COUNT; i = i + 3)
			{
				// Use the color we picked earlier.
				strip.setPixelColor(i + q, color);
			}

			// Update the pixels.
			strip.show();

			// Pause for effect.
			delay(LONG_DELAY);

			// Turn every third pixel off.
			for (i = 0; i < PIXEL_COUNT; i = i + 3)
			{
				strip.setPixelColor(i + q, 0);
			}
		}
	}
}
