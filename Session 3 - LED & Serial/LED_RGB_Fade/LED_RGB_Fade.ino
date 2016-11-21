int x;

void setup()
{
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

}

void loop()
{
    for (x = 0; x < 256; x++)
    {
        analogWrite(9 , x);
        analogWrite(10 , (255 - x));
        delay(10);
    }
}


