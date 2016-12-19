/******************************************************************************
 * Control a servo position using a potentiometer (variable resistor).
 *****************************************************************************/

#include <Servo.h>				// servo library

#define SERVO_PIN		9		// pin the servo is attached to
#define POT_PIN			0		// pin the potentiometer is attached to

Servo servo1;					// servo control object

void setup()
{
	// Attach the servo on pin 9 to the servo object.
}

void loop()
{
	// Make a variable to read the value from the analog pin

	// Read the value of the potentiometer (value between 0 and 1023) and save
	// it to your variable.

	// Scale the value to use it with the servo (value between 0 and 180).
	// You'll need to use the map function, the original range (0 - 1023), and
	// the new range (0 - 180).

	// Set the servo position using your scaled value.

	// Wait for the servo to get there (by delaying 15 ms).
}

