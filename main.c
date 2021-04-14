/*System library functions*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

/*Custom library functions*/
#include <constant.h>       //include definations and virables.
#include <dht11.h>          //For Greenhouse Tempreture and Humidity detection.
#include <buzzer.h>         //For alarm system.
#include <SoilMoisture.h>   //For Soil Moisture detection.

int main(void)
{
    FILE *TMP = NULL;
    FILE *HUMIDITY = NULL;
    printf("PIN:%d\n", pinNumber);
    int humidity_bit;
    int humidity_point_bit;
    int temperature_bit;
    int temperature_point_bit;
    if (-1 == wiringPiSetup()) {
        printf("Setup wiringPi failed!");
        return 1;
    }
  
    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, HIGH); // output a high level 
    pinMode(SoilPin,INPUT);
    pinMode(BeePin,OUTPUT);
    digitalWrite(BeePin, LOW); 
    pinMode(WaterPin,OUTPUT);
    digitalWrite(WaterPin, LOW); 
    printf("Starting...\n");
    last = millis();
    while (1) 
    {
        if (readSensorData())
        {
            pinMode(pinNumber, OUTPUT); // set mode to output
            digitalWrite(pinNumber, 1); // output a high level 
            delay(3000);
            if (readSensorData())
            {
                TMP = fopen("/home/pi/tempreture.txt", "w");
                HUMIDITY = fopen("/home/pi/humidity.txt", "w");
                humidity_bit = (databuf >> 24) & 0xff;
                humidity_point_bit = (databuf >> 16) & 0xff;
                temperature_bit = (databuf >> 8) & 0xff;
                temperature_point_bit = databuf & 0xff;
                fprintf(TMP, "%d",temperature_bit);
                fprintf(HUMIDITY, "%d",humidity_bit);
                fclose(TMP);
                fclose(HUMIDITY);
                printf("Sensor data read ok!\n");
                printf("temperature :%d.%d\n", temperature_bit,temperature_point_bit);
                printf("humidity :%d.%d\n", humidity_bit,humidity_point_bit);
                
            }
            else
            {
                printf("Sensor dosent ans!\n");
                databuf = 0;
            }
            if((humidity_bit>MaxHum)||(temperature_bit>MaxTem))
            {
                Beep(500);
                printf("Beep\n");
            }
            else
            {
                digitalWrite(BeePin, LOW); 
                printf("Do Not Beep\n");
            }

            databuf = 0;
        }
        
        
        if(digitalRead(SoilPin)==LOW)
        {
            digitalWrite(WaterPin,HIGH);
            printf("soil....\n");
        }
        else
        {
            digitalWrite(WaterPin,LOW);
        }
        delay(500);
    }
    return 0;
}
