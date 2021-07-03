/*System library functions*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

/*Custom library functions*/
#include <constant.h>       //include definitions and virables.
#include <dht11.h>          //For Greenhouse Tempreture and Humidity detection.
#include <buzzer.h>         //For alarm system.
#include <http.h>           //Data upload to the cloud by using http format.

using namespace std;

class para
{
   public:
      int bit; 
      int point_bit; 
};

int main(void)
{
    FILE *TMP = NULL;
    FILE *HUMIDITY = NULL;
    cout << "PIN:" << pinNumber << endl;
        
    para temp;                          //temperature
    para humi;                          //humidity
    
    if (-1 == wiringPiSetup()) {
        cout << "Setup wiringPi failed!" << endl;
        return 1;
    }
  
    pinMode(pinNumber, OUTPUT);    // set mode to output
    digitalWrite(pinNumber, HIGH); // output a high level 
    pinMode(SoilPin,INPUT);
    pinMode(BeePin,OUTPUT);
    digitalWrite(BeePin, LOW); 
    pinMode(WaterPin,OUTPUT);
    digitalWrite(WaterPin, LOW); 
    
    cout << "Starting..." << endl;
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
                humi.bit = (databuf >> 24) & 0xff;
                humi.point_bit = (databuf >> 16) & 0xff;
                temp.bit = (databuf >> 8) & 0xff;
                temp.point_bit = databuf & 0xff;
                fprintf(TMP, "%d",temp.bit);
                fprintf(HUMIDITY, "%d",humi.bit);
                fclose(TMP);
                fclose(HUMIDITY);
                cout << "Sensor data read ok!" << endl;
                cout << "temperature :" << temp.bit << "." << temp.point_bit << endl;
                cout << "humidity :" << humi.bit << "." << humi.point_bit << endl;
                http(temp.bit, humi.bit);
            }
            else
            {
                cout << "Sensor dosent ans!" << endl;
                databuf = 0;
            }
            if(((humi.bit>MaxHum)||(temp.bit>MaxTem))||((humi.bit<minHum)||(temp.bit<minTem)))
            {
                Beep(500);
                cout << "Beep!" << endl;
            }
            else
            {
                digitalWrite(BeePin, LOW); 
                cout << "Do Not Beep!" << endl;
            }
            databuf = 0;
        }
        
        if(digitalRead(SoilPin)==LOW)
        {
            digitalWrite(WaterPin,HIGH);
            cout << "activate watering system" << endl;
        }
        else
        {
            digitalWrite(WaterPin,LOW);
        }
        delay(500);
    }
    return 0;
}
