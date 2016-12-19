/******************************************************************************
 * Make an RGB LED display a rainbow of colors!
 *****************************************************************************/

#define RED_PIN			9				// pin the red LED is connected to
#define GREEN_PIN		10				// pin the green LED is connected to
#define BLUE_PIN		11				// pin the blue LED is connected to
#define DISPLAY_TIME	100				// how long to display each color [ms]

void setup()
{
	// Set up the LED pins as output. (Hint:  that's three lines of code.)
}

void loop()
{
	// Make a variable to count with.

	// Step through all the colors of the RGB LED.  How do we do that?
	// Use a loop to make your variable go from 0 to 767.

		// Call the ShowRGB function, and pass it a copy of your variable.
		
		// Wait a tiny bit (10 ms).
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

	// If the color is less than or equal to 255...

		// Red intensity equals color.
		
		// Green intensity equals 255 - color.
		
		// Blue is always off (and off means 255).
	
	// Else, if the color is less than or equal to 511...
	
		// Red is always 255 (off).
		
		// Green equals color - 256.
		
		// Blue equals 255 - (color - 256).
	
	// Else...
	
		// Red equals 255 - (color - 512).
		
		// Green is always 255 (off).
		
		// Blue equals color - 512.

	// Now update the LED color.  (Hint:  This is three lines of code.)
}
