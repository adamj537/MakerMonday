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

#define DISTANCE_MIN		8	// how close to get before going around [cm]

long duration;	// duration of a ping
long inches;	// distance to nearest object in inches
long cm;		// distance to nearest object in cm

void setup()
{  
	// Set up the serial port so we can see what's happening.
	Serial.begin(9600);
} 

void loop() 
{
	// Trigger the sonar module by a HIGH pulse of at least 10 microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(PIN_SONAR_TRIGGER, OUTPUT);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_SONAR_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);

	// The distance from the sensor is read by a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(PIN_SONAR_ECHO, INPUT);
	duration = pulseIn(PIN_SONAR_ECHO, HIGH);

	// convert the time into a distance.
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);

	// Long distances will cause the servos to misbehave... cap at 50 cm.
/*	if (cm > 50)
	{
		cm = 50;
		inches = 20;
	}
*/
	// Print how far away the nearest object is.
	Serial.print("Distance: ");
	Serial.print(inches);
	Serial.print(" in, ");
	Serial.print(cm);
	Serial.println(" cm");

	// If we're too close to an object...
	if (cm < DISTANCE_MIN)
	{
		// DISTANCE_BACK * delay(15) = distance the rover will back-up during
		// obstacle avoidance.
		Serial.println("Back up!");
	}

	// Wait 500 ms.
	delay(500);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
