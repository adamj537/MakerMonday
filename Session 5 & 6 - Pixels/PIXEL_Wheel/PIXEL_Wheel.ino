#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN           6	// pin the pixels are connected to
#define PIXEL_COUNT 		18	// how many pixels we have
#define PIXEL_BRIGHTNESS    80	// how bright to make the pixels (0-255)
#define SHORT_DELAY			20	// a small amount of time to wait for rainbows [ms]
#define LONG_DELAY			50	// time to wait for other effects [ms]

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;

void setup()
{
	uint32_t color;
	
	strip.begin();

	strip.setBrightness(PIXEL_BRIGHTNESS);

	for (uint8_t i = 0; i < 255; i++)
	{
		color = Wheel(i);
	
		strip.setPixelColor(0, color);

		strip.show();

		delay(SHORT_DELAY);
	}
}

void loop()
{
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
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
