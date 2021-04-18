# Greenhouse-intelligent-flower-watering-system

## RTES project
------------

![image](https://github.com/Su996/Greenhouse-intelligent-flower-watering-system/blob/main/images/GreenHouse.png)

Our group is devoted to design a Greenhouse intelligent flower watering system based on Raspberry Pi. This system can real-time detect the environment parameters of Greenhouse and the humidity of soil. If the soil humidity is higher or lower than threshold, Raspberry Pi will control water pipe watering the plants. When greenhouse temperature is abnormal, the buzzer will be activated and send a message to user's e-mail. All the detecting(or detected) data will be sent to PC and be shown on a user Interface created by Qt.

### Prerequisites

### install libghttp library on raspberry Pi
```
tar -xzvf libghttp-1.0.9.tar.gz
cd libghttp-1.0.9
./configure
make
make install
```
