#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;
 
/* WiringPi Pin Setup */
#define HIGH_TIME 32
#define SoilPin 0
#define pinNumber 1
#define BeePin 2
#define WaterPin 3

/* dht11 Temp and Humi detection */
uint32 databuf;
int MaxHum = 60;
int MaxTem = 25;
int minHum = 20;
int minTem = 10;
long last;
int humidity_bit;
int temperature_bit;
int humidity_point_bit;
int temperature_point_bit;

/* URI setting and related api-key*/
char *uri = "http://api.heclouds.com/devices/686117008/datapoints";
char *APIKEY = "gnzeKvd5HGejpFUHOCW2FspUWtw=";
