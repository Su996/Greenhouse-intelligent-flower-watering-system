#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void Beep(int interval)
{
    
    if((millis()-last)>interval)
    {
        digitalWrite(BeePin,!digitalRead(BeePin));
        last = millis();
    }
}
