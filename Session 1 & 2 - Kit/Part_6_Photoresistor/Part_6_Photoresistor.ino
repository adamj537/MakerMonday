/******************************************************************************
 *
 *	Filename:		Part_6_Photoresistor.ino
 *
 *	Description:	Use a photoresistor (light sensor) to control an LED's
 *					brightness.
 *
 *	New Hardware:	photoresistor
 *	New Software:	ADC
 *
 *****************************************************************************/

#define SENSOR_PIN		0		// pin with light sensor attached
#define LED_PIN			9		// pin with LED attached

int lightLevel;					// how much light we've detected
int high = 0;					// highest level of light we've detected
int low = 1023;					// lowest level of light we've detected

// This function runs once, when the code starts.
void setup()
{
	// We'll set up the LED pin to be an output.
	// (We don't need to do anything special to use the analog input.)
	pinMode(LED_PIN, OUTPUT);

	// Set up the serial port.
	Serial.begin(9600);
}

// This function runs repeatedly forever.
void loop()
{
	// Measure the voltage coming from the light sensor.
	// "lightLevel" is a number between 0 and 1023.
	lightLevel = analogRead(SENSOR_PIN);

	// Show the light level.
	Serial.println(lightLevel);

	// Change the range to between 0 and 255.  There are 3 ways to do this:
	
	// GOOD:
	lightLevel = map(lightLevel, 0, 1023, 0, 255);
	
	// BETTER:
//	lightLevel = map(lightLevel, 100, 700, 0, 255);

	// BEST:
/*	if (lightLevel < low)				// If a new low value is read...
	{
		low = lightLevel;				// Remember it.
	}
	if (lightLevel > high)				// If a new high value is read...
	{
		high = lightLevel;				// Remember it.
	}
	lightLevel = map(lightLevel, low+30, high-30, 0, 255);
*/
	// Clip out any numbers that are smaller than 0 or larger than 255.
	lightLevel = constrain(lightLevel, 0, 255);

	// Adjust the brightness of the LED.
	analogWrite(LED_PIN, lightLevel);
	
	// Make a night-light instead.
//	analogWrite(LED_PIN, 255 - lightLevel);
}


