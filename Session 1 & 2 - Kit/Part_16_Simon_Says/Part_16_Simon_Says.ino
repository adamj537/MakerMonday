/******************************************************************************
 *
 *	Filename:		Part_16_Simon_Says.ino
 *
 *	Description:	Put everything together to make a Simon Says game!
 *
 *	New Software:	files, case statements
 *
 *****************************************************************************/

#include "notes.h"						// frequencies for all the notes

#define CHOICE_OFF			0			// used to control LEDs
#define CHOICE_NONE			0			// used to check buttons
#define CHOICE_RED			(1 << 0)
#define CHOICE_GREEN		(1 << 1)
#define CHOICE_BLUE			(1 << 2)
#define CHOICE_YELLOW		(1 << 3)

// Which pins are used for what:
#define LED_RED				2			// red LED
#define LED_GREEN			5			// green LED
#define LED_BLUE			10			// blue LED
#define LED_YELLOW			13			// yellow LED
#define BUTTON_RED			3			// red button pin
#define BUTTON_GREEN		4			// green button pin
#define BUTTON_BLUE			11			// blue button pin
#define BUTTON_YELLOW		12			// yellow button pin
#define BUZZER1				8			// buzzer pin 1
#define BUZZER2				9			// buzzer pin 2

// Game settings:
#define ROUNDS_TO_WIN		13			// rounds to play before you win
#define ENTRY_TIME_LIMIT	3000		// time to press a button [ms]

#define MODE_MEMORY			0
#define MODE_BATTLE			1
#define MODE_BEEGEES		2

// Game state variables
byte gameMode = MODE_MEMORY;			// By default, let's play the memory game
byte gameBoard[32];						// the combination of buttons
byte gameRound = 0;						// number of succesful rounds

void setup()
{
	// Set the button pins as inputs (with pullup resistors).
	pinMode(BUTTON_RED, INPUT_PULLUP);
	pinMode(BUTTON_GREEN, INPUT_PULLUP);
	pinMode(BUTTON_BLUE, INPUT_PULLUP);
	pinMode(BUTTON_YELLOW, INPUT_PULLUP);

	// Set the LED pins as outputs.
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);
	pinMode(LED_YELLOW, OUTPUT);

	// Set the buzzer pins as outputs.
	pinMode(BUZZER1, OUTPUT);
	pinMode(BUZZER2, OUTPUT);

	// Set the game mode.  By default, we'll play the memory game.
	gameMode = MODE_MEMORY;

	// If the upper right button is pressed...
	if (CheckButton() == CHOICE_GREEN)
	{
		// Put game into battle mode.
		gameMode = MODE_BATTLE;

		// Turn on the green LED.
		SetLEDs(CHOICE_GREEN);
		
		// Play the "green" tone.
		toner(CHOICE_GREEN, 150);

		// Turn on the other LEDs until you release button.
		SetLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);

		// Wait for user to stop pressing button.
		while(CheckButton() != CHOICE_NONE);

		// Now do nothing. Battle mode will be serviced in the main routine.
	}

	PlayVictoryTune(); // After setup is complete, say hello to the world
}

void loop()
{
	// Blink lights to get someone to press a button.
	AttractMode();

	// Indicate the start of game play.
	SetLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); // Turn all LEDs on
	
	// Wait one second.
	delay(1000);
	
	// Turn off LEDs.
	SetLEDs(CHOICE_OFF);
	
	// Wait 1/4 second.
	delay(250);

	if (gameMode == MODE_MEMORY)
	{
		// Play memory game and handle result
		if (PlayMemory() == true) 
			PlayVictoryTune(); // Player won, play winner tones
		else 
			PlayLoserSound(); // Player lost, play loser tones
	}

	if (gameMode == MODE_BATTLE)
	{
		// Play game until someone loses.
		PlayBattle();

		// Player lost, play loser tones.
		PlayLoserSound();
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions are related to game play only

// Play the regular memory game
// Returns 0 if player loses, or 1 if player wins
boolean PlayMemory(void)
{
	// Seed the random generator with random amount of millis().
	randomSeed(millis());

	// Reset the game to the beginning.
	gameRound = 0;

	// Keep playing until you've won...
	while (gameRound < ROUNDS_TO_WIN) 
	{
		// Add a button to the current moves, then play them back
		AddToMoves();

		// Play back the current game board
		PlayMoves();

		// Require the player to repeat the sequence.
		for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
		{
			// See what button the user presses.
			byte choice = WaitForButton();

			// If wait timed out, player loses.
			if (choice == 0)
				return false;

			// If the choice is incorrect, player loses.
			if (choice != gameBoard[currentMove])
				return false;
		}

		// Player was correct, delay before playing moves.
		delay(1000);
	}

	// Player made it through all the rounds to win!
	return true;
}

// Play the special 2 player battle mode
// A player begins by pressing a button then handing it to the other player
// That player repeats the button and adds one, then passes back.
// This function returns when someone loses
boolean PlayBattle(void)
{
	// Reset the game frame back to one frame.
	gameRound = 0;

	// Loop until someone fails.
	while (1)
	{
		// Wait for user to input next move.
		byte newButton = WaitForButton();
		
		// Add this new button to the game array.
		gameBoard[gameRound++] = newButton;

		// Then require the player to repeat the sequence.
		for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
		{
			byte choice = WaitForButton();

			// If wait timed out, player loses.
			if (choice == 0)
				return false;

			// If the choice is incorect, player loses.
			if (choice != gameBoard[currentMove])
				return false;
		}

		// Give the user an extra 100ms to hand the game to the other player.
		delay(100);
	}

	// We should never get here.
	return true;
}

// Plays the current contents of the game moves.
void PlayMoves(void)
{
  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) 
  {
    toner(gameBoard[currentMove], 150);

    // Wait some amount of time between button playback.
    // Shorten this to make game harder.
	// 150 works well. 75 gets fast.
    delay(150);
  }
}

// Adds a new random button to the game sequence, by sampling the timer
void AddToMoves(void)
{
	byte newButton = random(0, 4); // min (included), max (exluded)

	// We have to convert this number, 0 to 3, to CHOICEs.
	if(newButton == 0) newButton = CHOICE_RED;
	else if(newButton == 1) newButton = CHOICE_GREEN;
	else if(newButton == 2) newButton = CHOICE_BLUE;
	else if(newButton == 3) newButton = CHOICE_YELLOW;

	// Add this new button to the game array.
	gameBoard[gameRound++] = newButton;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions control the hardware

// Lights a given LEDs
// Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc
void SetLEDs(byte leds)
{
	if ((leds & CHOICE_RED) != 0)
		digitalWrite(LED_RED, HIGH);
	else
		digitalWrite(LED_RED, LOW);

	if ((leds & CHOICE_GREEN) != 0)
		digitalWrite(LED_GREEN, HIGH);
	else
		digitalWrite(LED_GREEN, LOW);

	if ((leds & CHOICE_BLUE) != 0)
		digitalWrite(LED_BLUE, HIGH);
	else
		digitalWrite(LED_BLUE, LOW);

	if ((leds & CHOICE_YELLOW) != 0)
		digitalWrite(LED_YELLOW, HIGH);
	else
		digitalWrite(LED_YELLOW, LOW);
}

// Wait for a button to be pressed. 
// Returns one of LED colors (LED_RED, etc.) if successful, 0 if timed out
byte WaitForButton(void)
{
	// Remember the time we started the this loop.
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
			toner(button, 150);

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
	// If a button is pressed...				...return the button.
	if (digitalRead(BUTTON_RED) == 0)			return(CHOICE_RED); 
	else if (digitalRead(BUTTON_GREEN) == 0)	return(CHOICE_GREEN); 
	else if (digitalRead(BUTTON_BLUE) == 0)		return(CHOICE_BLUE); 
	else if (digitalRead(BUTTON_YELLOW) == 0)	return(CHOICE_YELLOW);

	// If no button is pressed, return none.
	return(CHOICE_NONE);
}

// Light an LED and play tone
// Red, upper left:     440Hz - 2.272ms - 1.136ms pulse
// Green, upper right:  880Hz - 1.136ms - 0.568ms pulse
// Blue, lower left:    587.33Hz - 1.702ms - 0.851ms pulse
// Yellow, lower right: 784Hz - 1.276ms - 0.638ms pulse
void toner(byte which, int buzz_length_ms)
{
	SetLEDs(which); //Turn on a given LED

	//Play the sound associated with the given LED
	switch(which) 
	{
	case CHOICE_RED:
		buzz_sound(buzz_length_ms, 1136); 
	break;
	case CHOICE_GREEN:
		buzz_sound(buzz_length_ms, 568); 
	break;
	case CHOICE_BLUE:
		buzz_sound(buzz_length_ms, 851); 
	break;
	case CHOICE_YELLOW:
		buzz_sound(buzz_length_ms, 638); 
	break;
	}

	SetLEDs(CHOICE_OFF); // Turn off all LEDs
}

// Toggle buzzer every buzz_delay_us, for a duration of buzz_length_ms.
void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  // Convert total play time from milliseconds to microseconds
  long buzz_length_us = buzz_length_ms * (long)1000;

  // Loop until the remaining play time is less than a single buzz_delay_us
  while (buzz_length_us > (buzz_delay_us * 2))
  {
    buzz_length_us -= buzz_delay_us * 2; //Decrease the remaining play time

    // Toggle the buzzer at various speeds
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);

    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

// Play the winner sound and lights
void PlayVictoryTune(void)
{
	SetLEDs(CHOICE_GREEN | CHOICE_BLUE);
	PlayWinnerSound();
	SetLEDs(CHOICE_RED | CHOICE_YELLOW);
	PlayWinnerSound();
	SetLEDs(CHOICE_GREEN | CHOICE_BLUE);
	PlayWinnerSound();
	SetLEDs(CHOICE_RED | CHOICE_YELLOW);
	PlayWinnerSound();
}

// Play the winner sound
// This is just a unique (annoying) sound we came up with, there is no magic to it
void PlayWinnerSound(void)
{
  // Toggle the buzzer at various speeds
  for (byte x = 250 ; x > 70 ; x--)
  {
    for (byte y = 0 ; y < 3 ; y++)
    {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);

      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

// Play the loser sound/lights
void PlayLoserSound(void)
{
  SetLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);

  SetLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);

  SetLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);

  SetLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
}

// Show an "attract mode" display while waiting for user to press button.
void AttractMode(void)
{
  while(1) 
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


