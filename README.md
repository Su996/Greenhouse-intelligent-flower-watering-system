# Greenhouse-intelligent-flower-watering-system

## RTES project

Our group is devoted to design a Greenhouse intelligent flower watering system based on Raspberry Pi. This system can real-time detect the environment parameters of Greenhouse and the humidity of soil. If the soil humidity is higher or lower than threshold, Raspberry Pi will control water pipe watering the plants. When greenhouse temperature is abnormal, the buzzer will be activated and send a message to user's e-mail. All the detecting(or detected) data will be sent to PC and be shown on a user Interface created by Qt.

### Prerequisites
-------------------
#### Supporting Hardware
Raspberry Pi 3b+  
DHT11  
soilmoisture sensor  
buzzer  

#### Supporting Software
Qt creator  
Geany IDE(for C)  
Onenet cloud server  

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

##### Get greenhouse temprature and humidity data
```
readSensorData()
```
readSensorData() is used to get greenhouse temprature and humidity data from DHT11 to Raspberry Pi

##### Threshold and Buzzer
```
Beep()
```
Beep(ms) is used to control buzzer to beep
When the temprature and humidity data is over the threshold, beep() will run.
The threshold is shown below:
```
int MaxHum = 60;
int MaxTem = 25;
int minHum = 20;
int minTem = 10;
```

##### Soil humidity detection
```
SoilPin()
```
The soil humidity threshold is adjusted by knob on soil detector chip.
When soil humidity below the limit, the detector DO will output low voltage signal.

##### Watering system
```
WaterPin()
```
Water pin will output signal based on soil detector signal.
The electric water valve will under control of water pin signal.
##### data uploaded to cloud server
```
http(temperature_bit, humidity_bit);
```
Using HTTP protocol to send HTTP messages to the cloud server
Request method: Post
Example of HTTP request header:
```
POST http://api.heclouds.com/devices/’device ID’/datastreams HTTP/1.1
```
HTTP Request body example:
```
{ 
    "id": "TMP", 
    "tags": ["temperature"], 
    "unit": "centigrade", 
    "unit_symbol": " ℃ " 
} 

{ 
    "id": "RH", 
    "tags": ["humidity"], 
    "unit": "percentage", 
    "unit_symbol": "% " 
} 
```
#### QT UI interface design
##### include
We create a Qt Widgets Application named "widget". In widget.cpp file include:
```
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <QTimer>
#include <QPixmap>
```
Because we need to call a python script to get data from Onenet cloud service, include:
```
#include <Python.h>
```
#### demo
Run main.c on the raspberry Pi and 加QT的代码啥的。 to make the data from seneor -> Raspberry Pi -> cloud server -> computer

### Troubleshooting
-------------------

### Contributors
-----------------
Haoyuan Su(2289042S)  
Boxiang Ma(2549544M)  
Yijie Sun(2569607S)  







