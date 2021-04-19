# Greenhouse-intelligent-flower-watering-system

## About project
Our group is devoted to design a Greenhouse intelligent flower watering system based on Raspberry Pi. This system can real-time detect the environment parameters of Greenhouse and the humidity of soil. If the soil humidity is higher or lower than threshold, Raspberry Pi will control water pipe watering the plants. When greenhouse temperature is abnormal, the buzzer will be activated and send a message to user's e-mail. All the detecting(or detected) data will be sent to PC and be shown on a user Interface created by Qt.

## Prerequisites
### Supporting Hardware
Raspberry Pi 3b+  
DHT11  
soilmoisture sensor  
buzzer  

### Supporting Software
Qt creator  
Geany IDE(for C)  
Onenet cloud server  

### Decompression and install libghttp library on raspberry Pi
Zip file has been putted in project branch
```
tar -xzvf libghttp-1.0.9.tar.gz
cd libghttp-1.0.9
./configure
make
make install
```

### Decompression and install wiringPi.h
```
$ cd
$ tar xfz wiringPi-98bcb20.tar.gz
$ cd wiringPi-98bcb20
$ ./build
```
## How to use
Setup hardware as below:  

Dataflow diagram:  
![image](https://github.com/Su996/Greenhouse-intelligent-flower-watering-system/blob/main/Flowchart.jpg)  

Sign up an account for Onenet cloud service: https://open.iot.10086.cn/passport/login/  
Create a HTTP protocol interface and add the device  
Here is the url and API key of your device: Device list -> Device details  

Run main.c on the raspberry Pi.   
```
./main
```
Python3 is required, also make sure python install urllib and import it:
```
import urllib.request
```
For Qt project, you can:  
1) Open Monitor.pro with Qt Creator (version 5.9 or higher) and run the project.  
2) Use qmake and mingw32-make to build the project, it will produce an executable file under “release” folder, run it.
```
qmake
mingw23-make
release/Monitor.exe
```
##### Important Notice:  
1) Please place python script "getdata.py" under build and debug folder, mine is
```
E:\Eric\Qt files\build-Monitor-Desktop_Qt_5_9_9_MinGW_32bit-Debug
```
You can also right click project in Qt Creator and select add existing file (file above) into the project.  
  
2) Must undefine "slots" in object.h which you can find under "include" folder of python directory. You can find the following code in line 201-207 (python3.9.4).
```
typedef struct{
    const char* name;
    int basicsize;
    int itemsize;
    unsigned int flags;
    PyType_Slot *slots; /* terminated by slot==0. */
} PyType_Spec;
```
Turn it to:  
```
typedef struct{
    const char* name;
    int basicsize;
    int itemsize;
    unsigned int flags;
    #undef slots  /* add here */
    PyType_Slot *slots; /* terminated by slot==0. */
    #define slots Q_SLOTS  /* add here */
} PyType_Spec;
```
3) Also if you want, please change direction of "logo.jpg", it's in widget.cpp line 46. You can place any logo you like.
## Code Description
### detect and upload data on cloud server
#### import
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

#### set pin mode
```
pinMode(SoilPin,INPUT);
pinMode(BeePin,OUTPUT);
pinMode(WaterPin,OUTPUT);
pinMode(pinNumber, OUTPUT); // set DHT11 tempareture and humidity sensor
```

#### Get greenhouse temprature and humidity data
```
readSensorData()
```
readSensorData() is used to get greenhouse temprature and humidity data from DHT11 to Raspberry Pi

#### Threshold and Buzzer
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

#### Soil humidity detection
```
SoilPin()
```
The soil humidity threshold is adjusted by knob on soil detector chip.
When soil humidity below the limit, the detector DO will output low voltage signal.

#### Watering system
```
WaterPin()
```
Water pin will output signal based on soil detector signal.
The electric water valve will under control of water pin signal.
#### data uploaded to cloud server
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
### QT UI interface design
#### include
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
#### python script "getdata.py"
Add a new python script into Qt project named "getdata.py".  
Python has a package which can get real-time data from Onenet cloud service by using a unique API key and url (You can find them in Onenet web page after you add a device to your Onenet account).
```
import urllib.request

API_KEY='gnzeKv***************UWtw='        #API key of our device
def http_get_data():
    url='http://api.heclouds.com/devices/686117008/datapoints'  #url of our Onenet cloud service
    request = urllib.request.Request(url)
    request.add_header('api-key',API_KEY)
    request.get_method = lambda:'GET'           # Set HTTP method
    request = urllib.request.urlopen(request)
    return request.read()
post = str(http_get_data())
```
"post" is a string that contains your latest data on Onenet.  
Then extract the data we want (in this case, humidity and temperature) from "post" and save in "RH" and "TMP" as integer:
```
RH=post.split('datapoints":')[1].split('"value":')[1].split('}')[0]
TMP=post.split('datapoints":')[2].split('"value":')[1].split('}')[0]
RH = int(RH)
TMP = int(TMP)
```
Define two functions to get the return value in widget.cpp:
```
def getRH():
    return RH
def getTMP():
    return TMP
```
#### widget.cpp
Set a decent UI first.

Qt has a useful class "QTimer". It can help us do real-time monitor. Connect a QTimer signal with repaint function, so when the time runs out, it calls repaint function and triggers paint event in Qt.
```
QTimer *timer = new QTimer(this);
connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
timer->start(2000);  #2000ms
```
Rewrite paint event in Qt. Everytime the UI repaint, paint event function gets latest data from Onenet cloud and show it.  
The following functions are used for calling python script. Use PyObject to achieve all we need.
```
void Widget::paintEvent(QPaintEvent *ev)
{
    Py_Initialize();
    ...
    PyObject* pModule = PyImport_ImportModule("getdata");  // getdata.py is the python script
    ...
    PyObject* pFungetRH= PyObject_GetAttrString(pModule,"getRH");  // function in python script
    PyObject* pFungetTMP= PyObject_GetAttrString(pModule,"getTMP");
```
Also use PyObject to get the return value:  
```
    PyObject* v1 = PyObject_CallFunction(pFungetRH,NULL);
    PyObject* v2 = PyObject_CallFunction(pFungetTMP,NULL);
    int RH,TMP;
    PyArg_Parse(v1, "i", &RH);
    PyArg_Parse(v2, "i", &TMP);  // now we get two integer RH and TMP
```
Turn two integer into string and set label text, Now we can see what is going on of our plant!
## Troubleshooting

## Contributors
Haoyuan Su(2289042S)  
Boxiang Ma(2549544M)  
Yijie Sun(2569607S)  
