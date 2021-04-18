# Greenhouse-intelligent-flower-watering-system

## RTES project

Our group is devoted to design a Greenhouse intelligent flower watering system based on Raspberry Pi. This system can real-time detect the environment parameters of Greenhouse and the humidity of soil. If the soil humidity is higher or lower than threshold, Raspberry Pi will control water pipe watering the plants. When greenhouse temperature is abnormal, the buzzer will be activated and send a message to user's e-mail. All the detecting(or detected) data will be sent to PC and be shown on a user Interface created by Qt.

### Prerequisites
-------------------
#### Decompression and install libghttp library on raspberry Pi
Zip file has been putted in project branch
```
tar -xzvf libghttp-1.0.9.tar.gz
cd libghttp-1.0.9
./configure
make
make install
```

#### Decompression and install wiringPi.h
```
$ cd
$ tar xfz wiringPi-98bcb20.tar.gz
$ cd wiringPi-98bcb20
$ ./build
```

### How to use
---------------
#### detect and upload data on cloud server
##### import
```
/*System library functions*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

/*Custom library functions*/
#include <constant.h>       //include definitions and virables.
#include <dht11.h>          //For Greenhouse Tempreture and Humidity detection.
#include <buzzer.h>         //For alarm system.
#include <http.h>           //Data upload to the cloud by using http format.
```

##### set pin mode
```
pinMode(SoilPin,INPUT);
pinMode(BeePin,OUTPUT);
pinMode(WaterPin,OUTPUT);
pinMode(pinNumber, OUTPUT); // set DHT11 tempareture and humidity sensor
```

##### set pin mode










