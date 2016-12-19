/******************************************************************************
 * Make a night light.
 * ...which means...
 * Use a photoresistor (light sensor) to control an LED's brightness.
 *****************************************************************************/

#define SENSOR_PIN		0		// pin with light sensor attached
#define LED_PIN			9		// pin with LED attached

// Make three variables:
// - one called "lightLevel" to save how much light we've detected,
// - one called "low" to save the highest level of light we've detected, and
// - one called "high" to save the lowest level of light we've detected.
// (Since these variables are not in any particular function, they're called
// "global," which means all our functions can share them.)

void setup()
{
	// Set up the LED pin to be an output.
	// (We don't need to do anything special to use the analog input.)

	// Set up the serial port.
	Serial.begin(9600);				// (I did this for you.)
}

void loop()
{
	// Measure the light detected by the light sensor (this is a number
	// between 0 and 1023) and save it to your global variable.

	// Print the value of your light-level variable to the computer.
	Serial.println(lightLevel);		// (I did this for you.)

	// Now use your other two global variables to remember the lowest and
	// highest light level detected.  Here's how:
	// If a new low value is read...

		// Save it to your "lowest level" variable.

	// If a new high value is read...

		// Save it to your "highest level" variable.

	
	// I've done the next two lines for you.  Can you figure out what they do?
	lightLevel = map(lightLevel, low + 30, high - 30, 0, 255);

	lightLevel = constrain(lightLevel, 0, 255);

	// Set the LED pin's value using the light level variable.
	// That will make the LED turn on when the light is on.
	// Make it a night-light by using 255 - the light level variable.
}


