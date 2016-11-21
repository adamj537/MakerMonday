/******************************************************************************
 *
 *	Description:	The rover!  It goes forward until it gets close to an
 *					object, then backs up and goes around.
 *
 *	Notes:			Given the orientation of the servos, one will be going
 *					forward, and the other backward. You may need to adjust 
 *					SPEED_LEFT and SPEED_RIGHT slightly to get the rover to
 *					move straight forward.  Also, the rover will always back up
 *					the same direction. Can you think of a better way to
 *					navigate obstacles?
 *
 *****************************************************************************/

#include <Adafruit_SoftServo.h>

#define PIN_SERVO_LEFT		0	// pin for left wheel servo (orange wire)
#define PIN_SERVO_RIGHT		1	// pin for right wheel servo (orange wire)
#define PIN_SONAR			2	// pin for sonar sensor

#define SPEED_LEFT			75	// forward speed for left servo
#define SPEED_RIGHT			90	// forward speed for right servo
#define SPEED_BACK_LEFT		150	// backwards speed for left servo
#define SPEED_BACK_RIGHT	50	// backwards speed for right servo

#define DISTANCE_MIN		8	// how close to get before going around [cm]
#define DISTANCE_BACK 		100	// multiplier for how far to back up to go around

Adafruit_SoftServo servoLeft;
Adafruit_SoftServo servoRight;

long duration;	// duration of a ping
long inches;	// distance in inches
long cm;		// distance converted to cm.

void setup() 
{  
  // Set up the servos.
  servoLeft.attach(PIN_SERVO_LEFT);
  servoRight.attach(PIN_SERVO_RIGHT);
} 

void loop() 
{
	int i;		// counter
	
	// Make the servos move.
	servoLeft.write(SPEED_LEFT - cm);
	servoLeft.refresh();
	servoRight.write(SPEED_RIGHT + cm);
	servoRight.refresh();

	// Wait a bit (15 microseconds).
	delay(15);

	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(PIN_SONAR, OUTPUT);
	digitalWrite(PIN_SONAR, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_SONAR, HIGH);
	delayMicroseconds(5);
	digitalWrite(PIN_SONAR, LOW);

	// The same pin is used to read the signal from the PING))): a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(PIN_SONAR, INPUT);
	duration = pulseIn(PIN_SONAR, HIGH);

	// convert the time into a distance.
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);  

	// Long distances will cause the servos to misbehave... cap at 50 cm.
	if (cm > 50)
	{
		cm = 50;
	}

	// If we're too close to an object...
	if (cm < DISTANCE_MIN)
	{
		// DISTANCE_BACK * delay(15) = distance the rover will back-up during
		// obstacle avoidance.
		for (i = 0; i < DISTANCE_BACK; i++)
		{
			// Back up.
			servoLeft.write(SPEED_BACK_LEFT);
			servoLeft.refresh();
			servoRight.write(SPEED_BACK_RIGHT);
			servoRight.refresh();
			
			// Wait a bit (15 milliseconds).
			delay(15);
		}
	}
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