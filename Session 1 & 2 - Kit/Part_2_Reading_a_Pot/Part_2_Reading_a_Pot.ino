/******************************************************************************
 *
 *	Filename:		Part_2_Reading_a_Pot.ino
 *
 *	Description:	Measure the position of a potentiometer and use it to
 *					control the blink rate of an LED. Turn the knob to make it
 *					blink faster or slower!
 *
 *	New Hardware:	potentiometer, voltage divider
 *	New Software:	variable, define statement
 *
 *****************************************************************************/

#define POT_PIN			0				// pin the pot is connected to
#define LED_PIN			13				// pin the LED is connected to

// This function runs once, when the code starts.
void setup()
{
	pinMode(LED_PIN, OUTPUT);			// Set LED pin as an output.
}

// This function runs repeatedly forever.
void loop()
{
	int sensorValue;					// the pot's value

	sensorValue = analogRead(POT_PIN);	// Read the pot's value.

	digitalWrite(LED_PIN, HIGH);		// Turn the LED on

	delay(sensorValue);					// Wait a bit.

	digitalWrite(LED_PIN, LOW);			// Turn the LED off.

	delay(sensorValue);					// Wait a bit.
}

