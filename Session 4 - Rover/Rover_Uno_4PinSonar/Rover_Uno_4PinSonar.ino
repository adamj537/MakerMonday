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

#include <Servo.h>

#define PIN_SERVO_LEFT		4	// pin for left wheel servo (orange wire)
#define PIN_SERVO_RIGHT		5	// pin for right wheel servo (orange wire)
#define PIN_SONAR_TRIGGER	2	// pin to start sonar sensor
#define PIN_SONAR_ECHO		3	// pin to read pulse from sonar sensor

#define SPEED_LEFT			130	// forward speed for left servo
#define SPEED_RIGHT			50	// forward speed for right servo
#define SPEED_BACK_LEFT		80	// backwards speed for left servo
#define SPEED_BACK_RIGHT	150	// backwards speed for right servo

#define DISTANCE_MIN		8	// how close to get before going around [cm]
#define DISTANCE_BACK 		100	// multiplier for how far to back up to go around

Servo servoLeft;
Servo servoRight;

long duration;	// duration of a ping
long inches;	// distance in inches
long cm = 0;	// distance in cm

void setup() 
{  
	// Set up the servos.
	servoLeft.attach(PIN_SERVO_LEFT);
	servoRight.attach(PIN_SERVO_RIGHT);

	// Set up the serial port so we can see what's happening.
	Serial.begin(9600);
} 

void loop() 
{
	int i;		// counter
	
	// Make the servos move.
//	servoLeft.write(SPEED_LEFT - cm);
//	servoRight.write(SPEED_RIGHT + cm);
	servoLeft.write(SPEED_LEFT);
	servoRight.write(SPEED_RIGHT);

	// Wait a bit (15 microseconds).
	delay(15);

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

	// Print how far away the nearest object is.
	Serial.println(inches);

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
			servoRight.write(SPEED_BACK_RIGHT);
			
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
