int x;

void GreenToBlue();
void BlueToRed();
void RedToGreen();

void setup()
{
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
}

void loop()
{
    RedToGreen();

    GreenToBlue();

    BlueToRed();
}

void BlueToRed()
{
    for (x = 0; x < 256; x++)
    {
        analogWrite(9 , (255 - x));
        analogWrite(10 , 255);
        analogWrite(11 , x);
        delay(10);
    }
}

void GreenToBlue()
{
    for (x = 0; x < 256; x++)
    {
        analogWrite(9 , 255);
        analogWrite(10 , x);
        analogWrite(11 , (255 - x));
        delay(10);
    }
}

void RedToGreen()
{
    for (x = 0; x < 256; x++)
    {
        analogWrite(9 , x);
        analogWrite(10 , (255 - x));
        analogWrite(11 , 255);
        delay(10);
    }
}


