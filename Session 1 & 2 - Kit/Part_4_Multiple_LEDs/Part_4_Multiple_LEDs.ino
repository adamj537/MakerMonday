/******************************************************************************
 *
 *	Filename:		Part_4_Multiple_LEDs.ino
 *
 *	Description:	Make eight LEDs dance.  Dance LEDs, dance!
 *
 *	New Software:	array, commented-out code
 *
 *****************************************************************************/

int ledPins[] = {2,3,4,5,6,7,8,9};		// array of pins with LEDs attached

// This function runs once, when the code starts.
void setup()
{
	int index;		// a counter

	// For each pin in the array...
	for (index = 0; index <= 7; index++)
	{
		// Set the pin as an output.
		pinMode(ledPins[index], OUTPUT);
	}
}

// This function runs repeatedly forever.
void loop()
{
	OneAfterAnother();					// Light up all the LEDs in turn.

	OneOnAtATime();						// Scroll through the LEDs one at a time.

	PingPong();							// Go back and forth.

	Marquee();							// Chase lights like you see on signs.

	RandomLED();						// Blink LEDs randomly.
}

/******************************************************************************
 *
 *	Function:		OneAfterAnother
 *
 *	Description:	This function will light one LED, delay for delayTime, then
 *					light the next LED, and repeat until all the LEDs are on.
 *					It will then turn them off in the reverse order.
 *
 *****************************************************************************/

void OneAfterAnother()
{
	int index;				// a counter
	int delayTime = 100;	// how long to pause between actions [ms]

	// Turn all the LEDs on:
	// This for() loop will step index from 0 to 7
	// (putting "++" after a variable means add one to it)
	// and will then use digitalWrite() to turn that LED on.
	for (index = 0; index <= 7; index++)
	{
		digitalWrite(ledPins[index], HIGH);
		delay(delayTime);                
	}

	// Turn all the LEDs off:

	// This for() loop will step index from 7 to 0
	// (putting "--" after a variable means subtract one from it)
	// and will then use digitalWrite() to turn that LED off.

	for (index = 7; index >= 0; index--)
	{
		digitalWrite(ledPins[index], LOW);
		delay(delayTime);
	}
}

 
/*
oneOnAtATime()

This function will step through the LEDs,
lighting only one at at time.
*/

void OneOnAtATime()
{
  int index;
  int delayTime = 100; // milliseconds to pause between LEDs
                       // make this smaller for faster switching
  
  // step through the LEDs, from 0 to 7
  
  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }
}

 
/*
pingPong()

This function will step through the LEDs,
lighting one at at time in both directions.
*/

void PingPong()
{
  int index;
  int delayTime = 100; // milliseconds to pause between LEDs
                       // make this smaller for faster switching
  
  // step through the LEDs, from 0 to 7
  
  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }

  // step through the LEDs, from 7 to 0
  
  for(index = 7; index >= 0; index--)
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }
}


/*
Marquee()

This function will mimic "chase lights" like those around signs.
*/

void Marquee()
{
  int index;
  int delayTime = 200; // milliseconds to pause between LEDs
                       // Make this smaller for faster switching
  
  // Step through the first four LEDs
  // (We'll light up one in the lower 4 and one in the upper 4)
  
  for(index = 0; index <= 3; index++) // Step from 0 to 3
  {
    digitalWrite(ledPins[index], HIGH);    // Turn a LED on
    digitalWrite(ledPins[index+4], HIGH);  // Skip four, and turn that LED on
    delay(delayTime);                      // Pause to slow down the sequence
    digitalWrite(ledPins[index], LOW);     // Turn the LED off
    digitalWrite(ledPins[index+4], LOW);   // Skip four, and turn that LED off
  }
}


/*
randomLED()

This function will turn on random LEDs. Can you modify it so it
also lights them for random times?
*/

void RandomLED()
{
  int index;
  int delayTime;
  
  // The random() function will return a semi-random number each
  // time it is called. See http://arduino.cc/en/Reference/Random
  // for tips on how to make random() even more random.
  
  index = random(8);	// pick a random number between 0 and 7
  delayTime = 100;
	
  digitalWrite(ledPins[index], HIGH);  // turn LED on
  delay(delayTime);                    // pause to slow down
  digitalWrite(ledPins[index], LOW);   // turn LED off
}

