#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN           6	// pin the pixels are connected to
#define PIXEL_COUNT 		18	// how many pixels we have
#define PIXEL_BRIGHTNESS    80	// how bright to make the pixels (0-255)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	uint32_t color;
	
	strip.begin();

	strip.setBrightness(PIXEL_BRIGHTNESS);

	color = strip.Color(255, 0, 255);
	
	strip.setPixelColor(0, color);

	strip.show();
}

void loop()
{
}
