/******************************************************************************
 *
 *	Filename:		Part_5_Push_Buttons.ino
 *
 *	Description:	Use pushbuttons.
 *	
 *	New Hardware:	pushbutton, pull-up resistor
 *
 *****************************************************************************/

#define BUTTON_1_PIN		2			// pushbutton 1 pin
#define BUTTON_2_PIN		3			// pushbutton 2 pin
#define LED_PIN				9			// LED pin

// This function runs once, when the code starts.
void setup()
{
	// Set up the pushbutton pins to be inputs.
	pinMode(BUTTON_1_PIN, INPUT);
	pinMode(BUTTON_2_PIN, INPUT);

	// Set up the LED pin to be outputs.
	pinMode(LED_PIN, OUTPUT);
}

// This function runs repeatedly forever.
void loop()
{
	int button1State;		// state of 1st pushbutton
	int button2State;		// state of 2nd pushbutton

	// Find out whether the pushbuttons are being pushed or not.
	button1State = digitalRead(BUTTON_1_PIN);
	button2State = digitalRead(BUTTON_2_PIN);

	// If we're pushing button 1 OR button 2, AND
	// we're NOT pushing button 1 AND button 2...
	if (((button1State == LOW) || (button2State == LOW)) &&
		!((button1State == LOW) && (button2State == LOW)))
	{
		// Turn the LED on.
		digitalWrite(LED_PIN, HIGH);
	}
	else
	{
		// Turn the LED off.
		digitalWrite(LED_PIN, LOW);
	}
}
