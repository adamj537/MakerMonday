/******************************************************************************
 *
 *	Filename:		Simon_Says.ino
 *
 *	Description:	Make a Simon Says game!
 *
 *****************************************************************************/

#include "notes.h"						// frequencies for all the notes

#define CHOICE_NONE			0
#define CHOICE_RED			(1 << 0)
#define CHOICE_GREEN		(1 << 1)
#define CHOICE_BLUE			(1 << 2)
#define CHOICE_YELLOW		(1 << 3)

// Which pins are used for what:
#define PIN_LED_RED			2			// red LED
#define PIN_LED_GREEN		5			// green LED
#define PIN_LED_BLUE		10			// blue LED
#define PIN_LED_YELLOW		13			// yellow LED
#define PIN_BUTTON_RED		3			// red button pin
#define PIN_BUTTON_GREEN	4			// green button pin
#define PIN_BUTTON_BLUE		11			// blue button pin
#define PIN_BUTTON_YELLOW	12			// yellow button pin
#define PIN_BUZZER1			8			// buzzer pin 1
#define PIN_BUZZER2			9			// buzzer pin 2

// Game settings:
#define ROUNDS_TO_WIN		5			// rounds to play before you win
#define ENTRY_TIME_LIMIT	3000		// time to press a button [ms]
#define TONE_LENGTH_SHORT	150			// time per button tone [ms]
#define TONE_LENGTH_LONG	255			// time per win/lose tone [ms]

void setup()
{

}

void loop()
{

}

// Play the memory game.
// Returns false if player loses, or true if player wins
boolean PlayMemory(void)
{

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions control the hardware

// Lights a given LEDs
// Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc.
void SetLEDs(byte leds)
{
	if ((leds & CHOICE_RED) != 0)
		digitalWrite(PIN_LED_RED, HIGH);
	else
		digitalWrite(PIN_LED_RED, LOW);

	if ((leds & CHOICE_GREEN) != 0)
		digitalWrite(PIN_LED_GREEN, HIGH);
	else
		digitalWrite(PIN_LED_GREEN, LOW);

	if ((leds & CHOICE_BLUE) != 0)
		digitalWrite(PIN_LED_BLUE, HIGH);
	else
		digitalWrite(PIN_LED_BLUE, LOW);

	if ((leds & CHOICE_YELLOW) != 0)
		digitalWrite(PIN_LED_YELLOW, HIGH);
	else
		digitalWrite(PIN_LED_YELLOW, LOW);
}

// Wait for a button to be pressed. 
// Returns one of LED colors (LED_RED, etc.) if successful, CHOICE_NONE if timed out
byte WaitForButton(void)
{
	// Remember the time we started waiting.
	long startTime = millis();

	// Loop until too much time has passed.
	while ((millis() - startTime) < ENTRY_TIME_LIMIT)
	{
		// See if a button was pressed.
		byte button = CheckButton();

		// If a button was pressed...
		if (button != CHOICE_NONE)
		{
			// Play the button the user just pressed.
			PlayChoice(button);

			// Wait for user to release button.
			while(CheckButton() != CHOICE_NONE);

			// This delay helps with debouncing and accidental double taps.
			delay(10);

			return button;
		}
	}

	return CHOICE_NONE; // If we get here, we've timed out!
}

// Returns a '1' bit in the position corresponding to CHOICE_RED, CHOICE_GREEN, etc.
byte CheckButton(void)
{
	byte choice;	// the player's choice of button
	
	// Figure out what button is pressed.
	if (digitalRead(PIN_BUTTON_RED) == 0)
		choice = CHOICE_RED;
	else if (digitalRead(PIN_BUTTON_GREEN) == 0)
		choice = CHOICE_GREEN;
	else if (digitalRead(PIN_BUTTON_BLUE) == 0)
		choice = CHOICE_BLUE;
	else if (digitalRead(PIN_BUTTON_YELLOW) == 0)
		choice = CHOICE_YELLOW;
	else
		choice = CHOICE_NONE;

	// Return the color corresponding to the user's choice.
	return choice;
}

// Light an LED and play tone
// Red:		440Hz - NOTE_A4
// Green:	880Hz - NOTE_A5
// Blue:	587.33Hz - NOTE_D5
// Yellow:	784Hz - NOTE_G5
void PlayChoice(byte choice)
{
	SetLEDs(choice); //Turn on a given LED

	//Play the sound associated with the given LED
	if (choice == CHOICE_RED)
	{
		tone(PIN_BUZZER2, NOTE_A4, TONE_LENGTH_SHORT);
		delay(TONE_LENGTH_SHORT);
	}
	else if (choice == CHOICE_GREEN)
	{
		tone(PIN_BUZZER2, NOTE_A5, TONE_LENGTH_SHORT);
		delay(TONE_LENGTH_SHORT);
	}
	else if (choice == CHOICE_BLUE)
	{
		tone(PIN_BUZZER2, NOTE_D5, TONE_LENGTH_SHORT);
		delay(TONE_LENGTH_SHORT);
	}
	else if (choice == CHOICE_YELLOW)
	{
		tone(PIN_BUZZER2, NOTE_G5, TONE_LENGTH_SHORT);
		delay(TONE_LENGTH_SHORT);
	}

	SetLEDs(CHOICE_NONE); // Turn off all LEDs
}

// Play the winner sound and lights
void PlayWinnerAction(void)
{
	SetLEDs(CHOICE_GREEN | CHOICE_BLUE);
	Chirp();
	SetLEDs(CHOICE_RED | CHOICE_YELLOW);
	Chirp();
	SetLEDs(CHOICE_GREEN | CHOICE_BLUE);
	Chirp();
	SetLEDs(CHOICE_RED | CHOICE_YELLOW);
	Chirp();
}

// Play a weird chirp sound.
void Chirp(void)
{
  // Toggle the buzzer at various speeds
  for (byte x = 250 ; x > 70 ; x--)
  {
    for (byte y = 0 ; y < 3 ; y++)
    {
      digitalWrite(PIN_BUZZER2, HIGH);
      digitalWrite(PIN_BUZZER1, LOW);
      delayMicroseconds(x);

      digitalWrite(PIN_BUZZER2, LOW);
      digitalWrite(PIN_BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

// Play the loser sound/lights
void PlayLoserAction(void)
{
	SetLEDs(CHOICE_RED | CHOICE_GREEN);
	tone(PIN_BUZZER2, NOTE_E4);
	delay(TONE_LENGTH_LONG);
	noTone(PIN_BUZZER2);

	SetLEDs(CHOICE_BLUE | CHOICE_YELLOW);
	tone(PIN_BUZZER2, NOTE_E4);
	delay(TONE_LENGTH_LONG);
	noTone(PIN_BUZZER2);
	
	SetLEDs(CHOICE_RED | CHOICE_GREEN);
	tone(PIN_BUZZER2, NOTE_E4);
	delay(TONE_LENGTH_LONG);
	noTone(PIN_BUZZER2);

	SetLEDs(CHOICE_BLUE | CHOICE_YELLOW);
	tone(PIN_BUZZER2, NOTE_E4);
	delay(TONE_LENGTH_LONG);
	noTone(PIN_BUZZER2);
}

// Show an "attract mode" display while waiting for user to press button.
void AttractMode(void)
{
  while (1)
  {
    SetLEDs(CHOICE_RED);
    delay(100);
    if (CheckButton() != CHOICE_NONE) return;

    SetLEDs(CHOICE_BLUE);
    delay(100);
    if (CheckButton() != CHOICE_NONE) return;

    SetLEDs(CHOICE_GREEN);
    delay(100);
    if (CheckButton() != CHOICE_NONE) return;

    SetLEDs(CHOICE_YELLOW);
    delay(100);
    if (CheckButton() != CHOICE_NONE) return;
  }
}


