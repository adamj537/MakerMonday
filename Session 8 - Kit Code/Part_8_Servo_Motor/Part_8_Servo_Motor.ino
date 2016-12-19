/******************************************************************************
 * Sweep a servo back and forth.  A servo is a motor that can move to specific
 * positions.  Basically a robot joint.
 *****************************************************************************/

#include <Servo.h>				// servo library

#define SERVO_PIN		9		// pin the servo is attached to

Servo servo1;					// servo control object

// This function runs once, when the code starts.
void setup()
{
	// "Attach" the servo1 object to digital pin 9.
}

// This function runs repeatedly forever.
void loop()
{
	// Make a variable representing the servo's position.
	
	// Move at full speed:
	// Tell servo to go to 90 degrees.
	// Pause (1000 ms) to get it time to move.
	// Tell servo to go to 180 degrees.
	// Pause (1000 ms) to get it time to move.
	// Tell servo to go to 0 degrees.
	// Pause (1000 ms) to get it time to move.
	
	// Move at a slower speed:
	// Tell servo to go to 180 degrees, moving 2 degrees at a time.
	// (Use a loop and the variable you created earlier.)
	// Don't forget to delay inside the loop (20 ms works fine).

	// Move even slower:
	// Tell servo to go to 0 degrees, stepping by one degree.
	// (Use a loop again.)
}

