/******************************************************************************
 *
 *	Description:	Test a sonar sensor!
 *
 *	Notes:			This test is for a 4-pin sonar sensor:  Power, Ground,
 *					Trigger, and Echo.
 *
 *****************************************************************************/

#define PIN_SONAR_TRIGGER	2	// pin to start sonar sensor
#define PIN_SONAR_ECHO		3	// pin to read pulse from sonar sensor

void setup()
{
	// Set up the serial port so we can see what's happening.
	Serial.begin(9600);

	pinMode(PIN_SONAR_TRIGGER, OUTPUT);
	pinMode(PIN_SONAR_ECHO, INPUT);
}

void loop()
{
	long duration;	// duration of a ping
	float inches;	// distance to nearest object in inches
	float cm;		// distance to nearest object in cm

	// Trigger the sonar module by a HIGH pulse of at least 10 microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_SONAR_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);

	// The distance from the sensor is read by a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	duration = pulseIn(PIN_SONAR_ECHO, HIGH);

	// convert the time into a distance.
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);

	// Print how far away the nearest object is.
	Serial.print("Distance: ");
	Serial.print(duration);
	Serial.print(" duration, ");
	Serial.print(inches);
	Serial.print(" in, ");
	Serial.print(cm);
	Serial.println(" cm");

	// Wait 500 ms.
	delay(500);
}

float microsecondsToInches(long microseconds)
{
	// According to Parallax's datasheet for the PING))), there are
	// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
	// second).  This gives the distance travelled by the ping, outbound
	// and return, so we divide by 2 to get the distance of the obstacle.
	// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
	return microseconds / 74.0 / 2.0;
}

float microsecondsToCentimeters(long microseconds)
{
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29.0 / 2.0;
}
