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
	
	theaterChase(strip.Color(127, 127, 127));	// White
	theaterChase(strip.Color(127, 0, 0));		// Red
	theaterChase(strip.Color(0, 0, 127));		// Blue
	
	rainbow();
	rainbowCycle();
	theaterChaseRainbow();
}

// Fill the dots one after the other with a color.
void colorWipe(uint32_t color)
{
	uint16_t i;
	
	// For each pixel...
	for (i = 0; i < strip.numPixels(); i++)
	{
		// Set the pixel's color.
		strip.setPixelColor(i, color);

		// Update the pixels.
		strip.show();

		// Pause for effect.
		delay(LONG_DELAY);
	}
}

// Make a rainbow.
void rainbow()
{
	uint16_t i;
	uint16_t j;
	uint32_t color;

	// Repeat this for all possible colors.
	for (j = 0; j < 256; j++)
	{
		// For each pixel...
		for (i = 0; i < strip.numPixels(); i++)
		{
			// Pick a new color.
			color = Wheel((i + j) & 255);
			
			// Set the pixel to the new color.
			strip.setPixelColor(i, color);
		}

		// Update the pixel.
		strip.show();

		// Pause (briefly) for effect.
		delay(SHORT_DELAY);
	}
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
			for (i = 0; i < strip.numPixels(); i = i + 3)
			{
				// Use the color we picked earlier.
				strip.setPixelColor(i + q, color);
			}

			// Update the pixels.
			strip.show();

			// Pause for effect.
			delay(LONG_DELAY);

			// Turn every third pixel off.
			for (i = 0; i < strip.numPixels(); i = i + 3)
			{
				strip.setPixelColor(i + q, 0);
			}
		}
	}
}

// Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow()
{
	int j;
	int q;
	int i;
	uint32_t color;
	
	// Cycle all 256 colors in the wheel.
	for (j = 0; j < 256; j++)
	{
		for (q = 0; q < 3; q++)
		{
			// Turn every third pixel on.
			for (i = 0; i < strip.numPixels(); i = i + 3)
			{
				color = Wheel((i + j) % 255);
				
				strip.setPixelColor(i + q, color);
			}

			// Update the pixels.
			strip.show();

			// Pause for effect.
			delay(LONG_DELAY);

			// Turn every third pixel off.
			for (i = 0; i < strip.numPixels(); i = i + 3)
			{
				strip.setPixelColor(i + q, 0);
			}
		}
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
