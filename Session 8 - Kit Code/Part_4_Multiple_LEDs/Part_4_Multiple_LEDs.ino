/******************************************************************************
 * Make eight LEDs dance.  Dance LEDs, dance!
 * We're going to learn how to use an array.
 *****************************************************************************/

int ledPins[] = {2,3,4,5,6,7,8,9};		// array of pins with LEDs attached

void setup()
{
	// Make a variable to do some math.

	// Use a loop to set up the LEDs.  Here's how:
	// Make a loop that makes your variable go from 0 to 7.
	// For each value of your variable...

		// Set the pin as an output.
}

// This function is already done for you :)
void loop()
{
	OneAfterAnother();					// Light up all the LEDs in turn.

	OneOnAtATime();						// Scroll through the LEDs one at a time.

	PingPong();							// Go back and forth.

	Marquee();							// Chase lights like you see on signs.

	RandomLED();						// Blink LEDs randomly.
}


/******************************************************************************
 * Light one LED, delay for delayTime, then light the next LED, and repeat
 * until all the LEDs are on.  Then turn them off in the reverse order.
 *****************************************************************************/

void OneAfterAnother()
{
	// Make a variable to count in a loop.

	// Turn all the LEDs on, one at a time.  Here's how:
	// Use a loop to make your variable go from 0 to 7
	// (putting "++" after a variable means add one to it)
	// and then use digitalWrite() to turn that LED on.

		// Turn an LED on, using your variable to control which one.

		// Delay for a bit (100 ms).


	// Turn all the LEDs off, one at a time.  Here's how:
	// Use a loop to make your variable go from 7 to 0
	// (putting "--" after a variable means subtract one from it)
	// and then use digitalWrite() to turn that LED off.

		// Turn an LED off, using your variable to control which one.

		// Delay for a bit (100 ms).
}


/******************************************************************************
 * Step through the LEDs, lighting only one at at time.
 *****************************************************************************/

void OneOnAtATime()
{
	// Make a variable to count in a loop.
  
	// Use a loop to make your variable go from 0 to 7.
	// For each value of your variable...
	
		// Turn an LED on, using your variable to control which one.
		
		// Delay for a bit (100 ms).
		
		// Turn the LED off, using the variable again.
}


/******************************************************************************
 * Make a "ping pong" effect by stepping through the LEDs, lighting one at a
 * time in both directions.
 *****************************************************************************/

void PingPong()
{
	// Make a variable to count in a loop.
  
	// Use a loop to make your variable go from 0 to 7.
	// For each value of your variable...
	
		// Turn an LED on, using your variable to control which one.
		
		// Delay for a bit (100 ms).
		
		// Turn the LED off, using the variable again.


	// Use a loop to make your variable go from 7 to 0.
	// For each value of your variable...
	
		// Turn an LED on, using your variable to control which one.
		
		// Delay for a bit (100 ms).
		
		// Turn the LED off, using the variable again.
}


/******************************************************************************
 * Mimic "theater lights" like those around signs.
 *****************************************************************************/

void Marquee()
{
	// Make a variable to count in a loop.
  
	// We'll light every 4th LED, and then change which ones are lit.
	// Use a loop to make your variable go from 0 to 3.

		// Turn an LED on, using your variable to control which one.
		
		// Now skip 4, and turn that LED on too (use variable + 4).
		
		// Delay for a bit (200 ms).
		
		// Turn the LED off, using the variable again.
		
		// Now turn the other LED off.
}


/******************************************************************************
 * Turn on random LEDs.
 *
 * Bonus:  Can you modify it so it also lights them for random times?
 *****************************************************************************/

void RandomLED()
{
	// Make a variable to count in a loop.

	// The random() function will return a semi-random number each time it is
	// called. See http://arduino.cc/en/Reference/Random to learn how it works
	// and then use it to give your variable a random number between 0 and 7.

	// Turn an LED on, using your variable to control which one.

	// Delay for a bit (100 ms).

	// Turn the LED off, using the variable again.
}

