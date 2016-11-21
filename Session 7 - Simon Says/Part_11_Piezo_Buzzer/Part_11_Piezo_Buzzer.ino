/******************************************************************************
 *
 *	Filename:		Part_11_Piezo_Buzzer.ino
 *
 *	Description:	Use a piezo buzzer to play a song.
 *
 *	New Hardware:	Piezo buzzer
 *
 *****************************************************************************/

#include "notes.h"					// frequencies for all the notes

#define BUZZER_PIN		9			// pin with buzzer attached
#define SONG_LENGTH		18			// how many notes to play
#define SONG_TEMPO		150			// how fast to play the song

// notes to the song (a 0 represents a rest)
// our song is: cdfda ag cdfdg gf 
char notes[SONG_LENGTH] =
{
	NOTE_C4,
	NOTE_D4,
	NOTE_F4,
	NOTE_D4,
	NOTE_A4,
	0,
	NOTE_A4,
	NOTE_G4,
	0,
	NOTE_C4,
	NOTE_D4,
	NOTE_F4,
	NOTE_D4,
	NOTE_G4,
	0,
	NOTE_G4,
	NOTE_F4,
	0
};

// how many beats to hold each note
int beats[SONG_LENGTH] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// This function runs once, when the code starts.
void setup()
{
	pinMode(BUZZER_PIN, OUTPUT);		// Make the buzzer's pin an output.
}

// This function runs repeatedly forever.
void loop()
{
	int i;				// counter
	int duration;		// length of the song [milliseconds]

	// For each note/beat in the song...
	for (i = 0; i < SONG_LENGTH; i++)
	{
		// Calculate the length of note/rest in ms.
		duration = beats[i] * SONG_TEMPO;

		// If there's a note to play...
		if (notes[i] != 0)
		{
			// Play the note.
			tone(BUZZER_PIN, notes[i], duration);
		}

		// Wait for the note/rest to finish.
		delay(duration);
		
		// Pause briefly between notes.
		delay(SONG_TEMPO / 10);
	}

	// Wait here forever.
	while(true);
}

