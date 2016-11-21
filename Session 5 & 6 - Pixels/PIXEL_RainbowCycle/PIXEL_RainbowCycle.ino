#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN			6	// pin the pixels are connected to
#define PIXEL_COUNT			18	// how many pixels we have
#define PIXEL_BRIGHTNESS	80	// how bright to make the pixels (0-255)
#define SHORT_DELAY			20	// a small amount of time to wait for rainbows [ms]
#define LONG_DELAY			50	// time to wait for other effects [ms]

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	strip.begin();
	
	strip.setBrightness(PIXEL_BRIGHTNESS);
	
	strip.show();
}

void loop()
{
	rainbowCycle();
}

// Slightly different, this makes the rainbow equally distributed throughout.
void rainbowCycle()
{
	uint16_t i;
	uint16_t j;
	uint32_t color;

	// 5 cycles of all colors on wheel
	for (j = 0; j < 256 * 5; j++)
	{
		// For each pixel...
		for (i = 0; i < strip.numPixels(); i++)
		{
			// Pick a new color.
			color = Wheel(((i * 256 / strip.numPixels()) + j) & 255);

			// Set the pixel to the new color.
			strip.setPixelColor(i, color);
		}

		// Update the pixels.
		strip.show();

		// Pause (briefly) for effect.
		delay(SHORT_DELAY);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
	WheelPos = 255 - WheelPos;
	
	if (WheelPos < 85)
	{
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	
	if (WheelPos < 170)
	{
		WheelPos -= 85;

		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	
	WheelPos -= 170;

	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
