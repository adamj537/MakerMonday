/******************************************************************************
 *
 *	Learn how an RGB LED works :)
 *
 *****************************************************************************/

#define RED_PIN			9				// pin the red LED is connected to
#define GREEN_PIN		10				// pin the green LED is connected to
#define BLUE_PIN		11				// pin the blue LED is connected to

void setup()
{
	pinMode(RED_PIN, OUTPUT);
}

void loop()
{
	int x;	// a counter; it controls the loop

	// Make the red LED get brighter.
	for (x = 0; x < 255; x++)
	{
		// Show a new color.
		analogWrite(RED_PIN, x);
		
		// Wait a tiny bit (10 ms).
		delay(10);
	}
}
