#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

uint32 databuf;
/* This function is used to get the Temperature and Humidity data which has been saved in databuf and crc */
uint8 readSensorData(void)
{
    uint8 crc;
    uint8 i;
    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, LOW); // output a high level 
    delay(25);
    digitalWrite(pinNumber, HIGH); // output a low level 
    pinMode(pinNumber, INPUT); // set mode to input
    pullUpDnControl(pinNumber, PUD_UP);
 
    delayMicroseconds(27);
    if (digitalRead(pinNumber) == LOW) //SENSOR ANS
    {
        while (!digitalRead(pinNumber))
            ; //wait to high
 
        for (i = 0; i < 32; i++)
        {
            while (digitalRead(pinNumber))
                ; //data clock start
            while (!digitalRead(pinNumber))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            databuf *= 2;
            if (digitalRead(pinNumber) == HIGH) //1
            {
                databuf++;
            }
        }
 
        for (i = 0; i < 8; i++)
        {
            while (digitalRead(pinNumber))
                ; //data clock start
            while (!digitalRead(pinNumber))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            crc *= 2;  
            if (digitalRead(pinNumber) == HIGH) //1
            {
                crc++;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
