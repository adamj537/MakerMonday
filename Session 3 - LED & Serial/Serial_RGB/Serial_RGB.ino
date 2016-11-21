int value;

void setup()
{
    pinMode(11, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    Serial.print("Red value:");

    while (!(Serial.available()))
    {
    }


    value = Serial.parseInt();
    Serial.print(value);
    Serial.println();

    analogWrite(9 , value);

    Serial.print("Green value:");

    while (!(Serial.available()))
    {
    }


    value = Serial.parseInt();
    analogWrite(10 , value);

    Serial.print(value);
    Serial.println();

    Serial.print("Blue value:");

    while (!(Serial.available()))
    {
    }


    value = Serial.parseInt();
    analogWrite(11 , value);

    Serial.print(value);
    Serial.println();
}


