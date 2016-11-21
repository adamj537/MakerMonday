/*******************************************************************************
*
*	Filename:		Florabrella.ino
*
*	Author:			Adafruit, modified by Adam Johnson (adamj537@gmail.com)
*
*	Description:	This project takes an Arduino FLORA, a color sensor, a ton
*					of NeoPixels in a strip, and a clear umbrella.  There are
*					three modes; pressing the big black button changes the mode.
*					When you power it on, it starts in mode 1.
*					MODE 1:  sense a color, then make all pixels match.
*					MODE 2:  make a rainbow.
*					MODE 3:  make it look like it's raining.
*
*					Have fun!
*
*	Source:			The original version of this file is here:
*					https://learn.adafruit.com/florabrella
*					This code also requires Adafruit's color sensor library and
*					NeoPixel library.  Here's where to get them & how they work:
*					https://learn.adafruit.com/adafruit-color-sensors
*					https://learn.adafruit.com/adafruit-neopixel-uberguide
*
*	License:		Whatever Adafruit's original license was.
*
*******************************************************************************/

#include <Wire.h>						// I2C library (to talk to color sensor)
#include "Adafruit_TCS34725.h"			// color sensor code
#include <Adafruit_NeoPixel.h>			// NeoPixel code

#define	PIN_BUTTON			10			// pin the switch is connected to
#define PIN_PIXELS			6			// pin that the pixels are connected to
#define NUM_PIXELS			144			// num pixel in the umbrella
#define PIXEL_BRIGHTNESS	80			// how bright to make the pixels (0-255)
#define GAMMA_TABLE_SIZE	256			// size of gamma table
#define NUM_RAINDROPS		20			// how many raindrops to show

enum									// modes of operation
{
	LIGHT_STARTUP = 0,					// startup
	LIGHT_MODE_SENSE,					// MODE 1:  copy whatever color we see
	LIGHT_MODE_RAINBOW,					// MODE 2:  make a rainbow
	LIGHT_MODE_RAIN,					// MODE 3:  make it rain
//	LIGHT_MODE_RAINBOW2,				// MODE 4:  different rainbow
	NUM_MODES
};

int g_buttonState;						// variable to hold the button state
int g_lightMode = LIGHT_MODE_SENSE;		// what mode we're in
int g_lightModePrev = LIGHT_STARTUP;	// the last mode we were in
byte g_gammaTable[GAMMA_TABLE_SIZE];	// the color we saw
int rainPos[NUM_RAINDROPS];				// which pixel has a raindrop
int rainCounter;

// Create a NeoPixel object.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

// Create a color sensor object.
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// This code runs once, at startup.
void setup()
{
	// DEBUG:  Wait for a serial connection.
//	while (!Serial);
	
	// Set up serial communication at 9600 baud.
	Serial.begin(9600);
	
	// Set the button's pin as input with internal pull-up resistor.
	pinMode(PIN_BUTTON, INPUT_PULLUP);
	
	// Set the pixel pin as output.
	pinMode(PIN_PIXELS, OUTPUT);
	
	// Set the strip's brightness.
	strip.setBrightness(PIXEL_BRIGHTNESS);
	
	// Read the initial state of the switch.
	g_buttonState = digitalRead(PIN_BUTTON);
	
	// Initialize the pixels to 'off'.
	strip.begin();
	strip.show();
	
	// Try to set up the color sensor.
	// If it is working...
	if (tcs.begin())
	{
		// Let the user know.
		Serial.println("Found color sensor.");
	}
	// If it's broken...
	else
	{
		// Let the user know.
		Serial.println("No color sensor found ... check your connections.");
		
		// Stop here so the user knows there's a problem.
		while (1);
	}
	
	// Thanks PhilB for this gamma table!
	// It helps convert RGB colors to what humans see.
	// Here, we give it some initial values.
	// For every value in the table...
	for (int i = 0; i < GAMMA_TABLE_SIZE; i++)
	{
		// Calculate the value that should go in this spot of the table.
		float x = i;
		x /= 255;
		x = pow(x, 2.5);
		x *= 255;
		
		// Put the value into the table.
		g_gammaTable[i] = x;
	}
}

// This code runs over and over forever.
void loop()
{
	int val;	// variable for reading the button
	int val2;	// variable for debouncing the button
	
	// Read the button (twice, to debounce it).
	val = digitalRead(PIN_BUTTON);
	delay (20);
	val2 = digitalRead(PIN_BUTTON);
	
	// If the button has been pressed...
	if ((val == val2) && (val != g_buttonState) && (val == LOW))
	{
		// Change the mode.
		g_lightMode++;
		
		// If we've reached the last mode, start over (with one, not zero,
		// because zero is "startup").
		if (g_lightMode == NUM_MODES)
			g_lightMode = 1;
	}

	// Save the new state in our variable.
	g_buttonState = val;
	
	// If we've just entered a new light mode...
	if (g_lightModePrev != g_lightMode)
	{
		// Print the new mode.
		Serial.print("Light mode is: ");
		Serial.println(g_lightMode);
		
		// Do anything required when a mode starts.
		if (g_lightMode == LIGHT_MODE_SENSE)
			ColorCopy();
		else if (g_lightMode == LIGHT_MODE_RAINBOW)
			RainbowInit();
		else if (g_lightMode == LIGHT_MODE_RAIN)
			RainInit();
		
		// Ensure that this stuff only happens once.
		g_lightModePrev = g_lightMode;
	}

	// Do any recurring actions associated with the light mode.
	if (g_lightMode == LIGHT_MODE_SENSE)
	{
		strip.show();
	}
	if (g_lightMode == LIGHT_MODE_RAINBOW)
	{
		Rainbow(10);
		delay(20);
	}
	if (g_lightMode == LIGHT_MODE_RAIN)
	{
		RainProcess();
		delay(20);
	}
//	if (g_lightMode == LIGHT_MODE_RAINBOW2)
//	{
//		RainbowCycle(10);
//		delay(20);
//	}
}

/*******************************************************************************
*	Use the color sensor to sense a color, then send it to the pixels.
*******************************************************************************/

void ColorCopy(void)
{
	// Initialize the pixels to 'off'.
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		strip.setPixelColor(i, strip.Color(0, 0, 0));
	}
	strip.show();
	
	// Turn on the LED on the color sensor board.
	tcs.setInterrupt(false);
	
	// Flash the first pixel three times as a countdown to the color reading.
	for (int i = 0; i < 3; i++)
	{
		// Set pixel 0 (the first one) to a nice white.
		// Normal white is (255, 255, 255), but 255 for all three values makes
		// it blinding, so we use (188, 188, 188) to make it nicer.
		strip.setPixelColor(0, strip.Color(188, 188, 188));
		
		// Send the color to the pixel.
		strip.show();
		
		// Wait one second.
		delay(1000);
		
		// Set pixel 0's color to black/off.
		strip.setPixelColor (0, strip.Color(0, 0, 0));
		
		// Send the color to the pixel.
		strip.show();
		
		// Wait one second.
		delay(500);
	}
	
	uint16_t clear, red, green, blue;

	// Wait 60 ms, because it takes 50 ms to read the sensor.
	delay(60);
	
	// Fetch the color from the sensor.
	tcs.getRawData(&red, &green, &blue, &clear);
	
	// Turn off the LED on the color sensor board.
	tcs.setInterrupt(true);
	
	// Figure out some basic hex code for visualization.
	uint32_t sum = red;
	sum += green;
	sum += blue;
	sum = clear;
	
	float r, g, b;
	r = red;
	r /= sum;
	g = green;
	g /= sum;
	b = blue;
	b /= sum;
	
	r *= 256;
	g *= 256;
	b *= 256;
	
	// Print the hex values of the color.
	Serial.print("Found this color:");
	Serial.print("\tRed:\t0x");
	Serial.print((int)r, HEX);
	Serial.print("\tGreen:\t0x");
	Serial.print((int)g, HEX);
	Serial.print("\tBlue:\t0x");
	Serial.println((int)b, HEX);
	
	// Send the color to the pixels, with a cool swipey effect.
	ColorWipe(strip.Color(g_gammaTable[(int)r], g_gammaTable[(int)g], g_gammaTable[(int)b]), 0);
}

/*******************************************************************************
*	Fill the dots one after the other with a color.
*******************************************************************************/

void ColorWipe(uint32_t color, uint8_t wait)
{
	// For each pixel...
	for (uint16_t i = 0; i < strip.numPixels(); i++)
	{
		// Set the pixel's color.
		strip.setPixelColor(i, color);
		
		// Send the color to the pixels.
		strip.show();
		
		// Pause for effect.
		delay(20);
	}
}

/*******************************************************************************
*	Make the pixels look like it's raining.
*******************************************************************************/

void RainInit()
{
	rainCounter = 0;
	
	// Set each rain drop at the starting gate.
	// Signify by a position of -1
	for (int i = 0; i < NUM_RAINDROPS; i++)
	{
		rainPos[i] = -1;
	}
}

void RainProcess()
{
	// Turn all the pixels off.
	for (int i = 0; i < strip.numPixels(); i++)
	{
		strip.setPixelColor(i, 0);
	}

	// For each raindrop...
	for (int i = 0; i < NUM_RAINDROPS; i++)
	{
		// If the drop is out of the starting gate...
		if (rainPos[i] >= 0)
		{
			// Turn on the raindrop's LED.
			strip.setPixelColor(rainPos[i], strip.Color(0,0,127));
			
			// Move the drop down one row.
			rainPos[i] -= 7;
			
			// If the raindrop has fallen off the strip...
			if (rainPos[i] < 0)
			{
				// Put the drop back at the starting gate.
				rainPos[i]=-1;
			}
		}
		
		// If this drop is at the starting gate, randomly see if we should
		// start it falling.
		if (rainPos[i] == -1 && random(40) == 0 && rainCounter < 380)
		{
			// Pick one of the 6 starting spots to begin falling.
			rainPos[i] = 143 - random(6);
		}
		
		// Send new colors to the pixels.
		strip.show();
		
		// Wait a bit (2 ms).
		delay(2);
	}
}

/*******************************************************************************
*	Show a rainbow effect
*******************************************************************************/

uint16_t rainbowCounter;

void RainbowInit(void)
{
	rainbowCounter = 0;
}

void Rainbow(uint8_t wait)
{
	uint16_t i;		// counter for number of pixels
	
	// For each pixel...
	for (i = 0; i < strip.numPixels(); i++)
	{
		// Set the pixel to the next color of the rainbow.
		strip.setPixelColor(i, Wheel((i + rainbowCounter) & 255));
	}
	
	// Send the new colors to the pixels.
	strip.show();
	
	// Pause for effect (different values here change the rainbow's speed).
	delay(wait);
	
	// Do a cycle of all colors on wheel.
	if (rainbowCounter > 255)
	{
		rainbowCounter = 0;
	}
	else
	{
		rainbowCounter++;
	}
}

/*******************************************************************************
*	Show a rainbow effect - Equally distributed
*******************************************************************************/

void RainbowCycle(uint8_t wait)
{
	uint16_t i;		// counter for number of pixels
	
	// For each pixel...
	for (i = 0; i < strip.numPixels(); i++)
	{
		// Set the pixel to the next color of the rainbow.
		strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + rainbowCounter) & 255));
	}
	
	// Send the new colors to the pixels.
	strip.show();
	
	// Pause for effect (different values here change the rainbow's speed).
	delay(wait);
	
// Do a cycle of all colors on wheel.
	if (rainbowCounter > 256 * 5)
	{
		rainbowCounter = 0;
	}
	else
	{
		rainbowCounter++;
	}
}

/*******************************************************************************
*	Input a value 0 to 255 to get a color value.
*	The colours are a transition r - g - b - back to r.
*******************************************************************************/

uint32_t Wheel(byte WheelPos)
{
	if (WheelPos < 85)
	{
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
	else if (WheelPos < 170)
	{
		WheelPos -= 85;
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else
	{
		WheelPos -= 170;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

