/******************************************************************************
 *
 *	Filename:		Part_8_Servo_Motor.ino
 *
 *	Description:	Sweep a servo back and forth.  A servo is a motor that can
 *					move to specific positions.  Basically a robot joint.
 *
 *	New Hardware:	servo
 *	New Software:	library
 *
 *****************************************************************************/

#include <Servo.h>				// servo library

#define SERVO_PIN		9		// pin the servo is attached to

Servo servo1;					// servo control object

// This function runs once, when the code starts.
void setup()
{
	// "Attach" the servo1 object to digital pin 9.
	servo1.attach(SERVO_PIN);
}

// This function runs repeatedly forever.
void loop()
{
	int position;			// number representing the servo's position
	
	// Move at full speed:
	
	servo1.write(90);    // Tell servo to go to 90 degrees.
	delay(1000);         // Pause to get it time to move.
	servo1.write(180);   // Tell servo to go to 180 degrees.
	delay(1000);         // Pause to get it time to move.
	servo1.write(0);     // Tell servo to go to 0 degrees.
	delay(1000);         // Pause to get it time to move.
	
	// Move at a slower speed:
	
	// Tell servo to go to 180 degrees, moving 2 degrees at a time.
	for (position = 0; position < 180; position += 2)
	{
		servo1.write(position);  // Move to next position
		delay(20);               // Short pause to allow it to move
	}

	// Move even slower:
	
	// Tell servo to go to 0 degrees, stepping by one degree.
	for (position = 180; position >= 0; position -= 1)
	{                                
		servo1.write(position);  // Move to next position.
		delay(20);               // Short pause to allow it to move.
	}
}

