/******************************************************************************
 *
 *	Filename:		Part_7_Temperature_Sensor.ino
 *
 *	Description:	Measure the temperature, and display it on the computer.
 *					Other things we could try with this code:
 *					Turn on an LED if the temperature is above or below a value.
 *					Read that threshold value from a potentiometer - now you've
 *					created a thermostat!
 *
 *	New Hardware:	sensor, serial port
 *	New Software:	floating point variables
 *
 *****************************************************************************/

#define	TEMPERATURE_PIN		0		// pin the sensor is connected to

// This function runs once, when the code starts.
void setup()
{
	// Set up the serial port's speed.
	Serial.begin(9600);
}

// This function runs repeatedly forever.
void loop()
{
	float voltage;		// voltage from the temperature sensor
	float degreesC;		// temperature in Celcius
	float degreesF;		// temperature in Fahrenheit
	
	// Measure the voltage at the sensor pin.  Then convert the 0 to 1023 value
	// that analogRead() returns, into a 0.0 to 5.0 value that is the true
	// voltage being read at that pin.
	voltage = analogRead(TEMPERATURE_PIN) * 0.004882814;
	
	// Convert the voltage to degrees Celsius.
	// This formula comes from the temperature sensor datasheet.
	degreesC = (voltage - 0.5) * 100.0;
	
	// Convert degrees Celsius to Fahrenheit.
	// This is the classic C to F conversion formula.
	degreesF = degreesC * (9.0/5.0) + 32.0;
	
	// Use the serial port to print these values to the serial monitor.
	// These statements will print lines of data like this:
	// "voltage: 0.73 deg C: 22.75 deg F: 72.96"
	Serial.print("voltage: ");
	Serial.print(voltage);
	Serial.print("  deg C: ");
	Serial.print(degreesC);
	Serial.print("  deg F: ");
	Serial.println(degreesF);

	// Wait one second.
	delay(1000);
}

