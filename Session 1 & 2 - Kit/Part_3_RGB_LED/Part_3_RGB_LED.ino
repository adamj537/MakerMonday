/******************************************************************************
 *
 *	Filename:		Part_3_RGB_LED.ino
 *
 *	Descriptiion:	Make an RGB LED display a rainbow of colors!
 *
 *	New Hardware:	RGB LED
 *	New Software:	for-loop, if/else-statement, making our own function
 *
 *****************************************************************************/

#define RED_PIN			9				// pin the red LED is connected to
#define GREEN_PIN		10				// pin the green LED is connected to
#define BLUE_PIN		11				// pin the blue LED is connected to
#define DISPLAY_TIME	100				// how long to display each color [ms]

// This function runs once, when the code starts.
void setup()
{
	// Set up the LED pins as output.
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);
}

// This function runs repeatedly forever.
void loop()
{
	int x;	// a counter; it controls the loop

	// Step through all the colors of the RGB LED.  How do we do that?
	// Repeat everything in brackets 768 times, with a different value of x
	// each time.
	for (x = 0; x < 768; x++)
	{
		// Show a new color.
		ShowRGB(x);
		
		// Wait a tiny bit (10 ms).
		delay(10);
	}
}

/******************************************************************************
 *
 *	Function:		ShowRGB
 *
 *	Description:	This function translates a number between 0 and 767 into a
 *					specific color on the RGB LED.  If you have this number
 *					count through the whole range (0 to 767), the LED will
 *					smoothly change color through the entire spectrum.
 *					For this common anode LED, 0 = OFF, 255 = ON.
 *					For a common cathode LED, 0 = ON, 255 = OFF.
 *					0 = red
 *					255 = green
 *					511 = blue
 *					767 = red (again)
 *					Anything between these numbers will blend two colors
 *					together.
 *
 *	Parameters:		color - a number between 0 and 767, representing a color
 *
 *****************************************************************************/

void ShowRGB(int color)
{
	int redIntensity;		// how bright to make the red LED
	int greenIntensity;		// how bright to make the green LED
	int blueIntensity;		// how bright to make the blue LED

	// If the color is less than 255...
	if (color <= 255)
	{
		// Red goes from on to off.
		redIntensity = color;
		
		// Green goes from off to on.
		greenIntensity = 255 - color;
		
		// Blue is always off.
		blueIntensity = 255;
	}
	
	// If the color is between 256 to 511...
	else if (color <= 511)
	{
		// Red is always off.
		redIntensity = 255;
		
		// Green goes from on to off.
		greenIntensity = (color - 256);
		
		// Blue goes from off to on.
		blueIntensity = 255 - (color - 256);
	}
	
	// If the color is 512 or greater...
	else
	{
		// Red goes from off to on.
		redIntensity = 255 - (color - 512);
		
		// Green is always off.
		greenIntensity = 255;
		
		// Blue goes from on to off.
		blueIntensity = (color - 512);
	}

	// Now update the LED color.
	analogWrite(RED_PIN, redIntensity);
	analogWrite(BLUE_PIN, blueIntensity);
	analogWrite(GREEN_PIN, greenIntensity);
}
