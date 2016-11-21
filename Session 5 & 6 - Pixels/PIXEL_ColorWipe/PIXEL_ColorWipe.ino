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
	colorWipe(strip.Color(0, 0, 0));	// Black/off
	colorWipe(strip.Color(255, 0, 0));	// Red
	colorWipe(strip.Color(0, 255, 0));	// Green
	colorWipe(strip.Color(0, 0, 255));	// Blue
}

// Fill the dots one after the other with a color.
void colorWipe(uint32_t color)
{
	uint16_t i;
	
	// For each pixel...
	for (i = 0; i < PIXEL_COUNT; i++)
	{
		// Set the pixel's color.
		strip.setPixelColor(i, color);

		// Update the pixels.
		strip.show();

		// Pause for effect.
		delay(LONG_DELAY);
	}
}
