
//title: AIR CONDITIONER AND DEHUMIDIFIER
//name :joshua jayan and ashton chew
//admission number 2533580, 2516662
//class DCEP/FT/1A/09
//discription:
#include <Wire.h>
#include "RichShieldDHT.h"
#include "RichShieldTM1637.h"
#define CLK 10
#define DIO 11
TM1637 disp(CLK,DIO);

DHT dht;

void setup() 
{
	disp.init();  
	dht.begin();
}

float humidity = dht.readHumidity();
if (isnan(currentHumidity))
{
displayError();
}
else
{
display





