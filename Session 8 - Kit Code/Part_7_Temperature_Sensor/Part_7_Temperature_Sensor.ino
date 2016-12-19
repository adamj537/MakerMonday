/******************************************************************************
 * Measure the temperature, and display it on the computer.
 *
 * Other things we could try with this code:
 *	Turn on an LED if the temperature is above or below a value.
 *	Read that threshold value from a potentiometer - now you've
 *	created a thermostat!
 *****************************************************************************/

#define	TEMPERATURE_PIN		0		// pin the sensor is connected to

void setup()
{
	// Set up the serial port (this is the line that was done for you in the
	// last program).
}

void loop()
{
	float voltage;		// voltage from the temperature sensor
	float degreesC;		// temperature in Celcius
	float degreesF;		// temperature in Fahrenheit
	
	// Measure the voltage at the sensor pin, and do multiplication to convert
	// the 0 to 1023 value that analogRead() returns, into a 0.0 to 5.0 value
	// that is the true voltage being read at that pin (multiply by 5.0 and then
	// divide by 1024.0).
	
	// Convert the voltage to degrees Celsius.
	// The formula is C = (V - 0.5) * 100.0 (which comes from the temperature
	// sensor's datasheet).
	
	// Convert degrees Celsius to Fahrenheit.  If you don't know the formula,
	// look it up online.
	
	// Use the serial port to print these values to the computer.
	// To do this, use Serial.print().  Look online for how to use it.
	// Try to make it print lines of data like this:
	// "voltage: 0.73 deg C: 22.75 deg F: 72.96"

	// Wait one second.
}

