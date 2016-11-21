/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>				// servo library

#define SERVO_PIN		9		// pin the servo is attached to
#define POT_PIN			0		// pin the potentiometer is attached to

Servo servo1;					// servo control object

void setup()
{
	// Attach the servo on pin 9 to the servo object.
	servo1.attach(SERVO_PIN);
}

void loop()
{
	int val;    // variable to read the value from the analog pin

	// Read the value of the potentiometer (value between 0 and 1023).
	val = analogRead(POT_PIN);

	// Scale it to use it with the servo (value between 0 and 180).
	val = map(val, 0, 1023, 0, 180);

	// Set the servo position according to the scaled value.
	servo1.write(val);

	// Wait for the servo to get there.
	delay(15);
}

