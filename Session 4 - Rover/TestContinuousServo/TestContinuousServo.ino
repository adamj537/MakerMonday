#include <Servo.h>

#define PIN_SERVO_LEFT		4	// pin for left wheel servo (orange wire)
#define PIN_SERVO_RIGHT		5	// pin for right wheel servo (orange wire)

// 90 is no movement; 180 is full speed one way; 0 is full speed the other way
#define SPEED_LEFT			80	// backwards speed for left servo
#define SPEED_RIGHT			150	// backwards speed for right servo

Servo servoLeft;
Servo servoRight;

void setup()
{
	// Set up the servos.
	servoLeft.attach(PIN_SERVO_LEFT);
	servoRight.attach(PIN_SERVO_RIGHT);
	
	// Back up.
	servoLeft.write(SPEED_LEFT);
	servoRight.write(SPEED_RIGHT);
}

void loop()
{

}
