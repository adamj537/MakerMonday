/******************************************************************************
 *
 *	Filename:		Part_11_Piezo_Buzzer.ino
 *
 *	Description:	Use a piezo buzzer to play a song.
 *
 *	New Hardware:	Piezo buzzer
 *
 *****************************************************************************/

#define BUZZER_PIN		9			// pin with buzzer attached
#define SONG_LENGTH		18			// how many notes to play

// notes to the song (a space represents a rest)
char notes[] = "cdfda ag cdfdg gf ";

// how many beats to hold each note
int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// how fast to play the song
int tempo = 150;

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
		duration = beats[i] * tempo;

		// If this is a rest...
		if (notes[i] == ' ')
		{
			// Pause for a moment.
			delay(duration);
		}
		// Otherwise...
		else
		{
			// Play the note.
			tone(BUZZER_PIN, frequency(notes[i]), duration);
			
			// Wait for the note to finish.
			delay(duration);
		}
		
		// Pause briefly between notes.
		delay(tempo / 10);
	}

	// Wait here forever.
	while(true);
}

/******************************************************************************
 *
 *	Function:		Frequency
 *
 *	Description:	Takes a note character (a-g), and returns the corresponding 
 *					frequency in Hz for the tone() function.
 *
 ******************************************************************************/
int frequency(char note)
{
	int i;								// counter
	const int numNotes = 8;				// number of notes we're storing
	char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };		// note characters
	int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};	// note frequencies

	// Now we'll search through the letters in the array, and if
	// we find it, we'll return the frequency for that note.

	// For each note...
	for (i = 0; i < numNotes; i++)
	{
		// If this is the right note...
		if (names[i] == note)
		{
			// Return the note's frequency.
			return(frequencies[i]);
		}
	}
	
	// We looked through everything and didn't find it, but we still need to
	// return a value, so return 0.
	return(0);
}

