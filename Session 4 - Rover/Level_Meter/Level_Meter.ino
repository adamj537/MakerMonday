/* Water Level Meter

Measuring water level with ultrasonic sensor HR S04.

Arduino IDE 1.5.8
*/

#define PIN_TRIGGER	12
#define PIN_ECHO	11

void setup()
{
	// Set up the serial port.
	Serial.begin(9600);
	
	// Initialize the ultrasonic distance sensor.
	pinMode(PIN_TRIGGER, OUTPUT);
	pinMode(PIN_ECHO, INPUT);
}

void loop()
{
	long time = 0;		// time for ultrasonic signal to return [us]
	long distance = 0;	// distance (height) from sensor to water level [cm]
	long level = 0;		// liquid level [cm]

	// Transmitting pulse
	digitalWrite(PIN_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_TRIGGER, LOW);

	// Waiting for pulse.  This gives the time it took for the ultrasonic pulse
	// to return to the sensor.
	time = pulseIn(PIN_ECHO, HIGH);

	// Calculating distance from time.
	distance = time / 58;

	// Correct for offset in level.
	distance -= 6;
	
	// Calculate water level, 0 - 50 cm.
	level = 50 - distance;

	// Sending to computer
	Serial.print(level);
	Serial.print(" cm\n");

	// Pause for effect.
	delay(1000);
}
