int x;

void setup()
{
    pinMode(13, OUTPUT);

}

void loop()
{
    for (x = 0; x < 256; x++)
    {
        analogWrite(13 , x);
        delay(10);
    }

    delay(500);

    for (x = 0; x < 256; x++)
    {
        analogWrite(13 , (255 - x));
        delay(10);
    }
}


