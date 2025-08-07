
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
#define LED_GREEN 5
#define LED_BLUE 6
#define KEY1_PIN 9
#define KEY2_PIN 8


TM1637 disp(CLK,DIO);

DHT dht;

void setup() 
{
	disp.init();  
	dht.begin();
	Serial.begin(9600)
	pinMode (LED_BLUE,OUTPUT);
	pinMode (LED_GREEN,OUTPUT);
	disp.init();
	disp.display(count);
}

void loop()
{
        digitalWrite(LED_BLUE,LOW);
        digitalWrite(LED_GREEN,LOW);
	float current_humidity ;
	current_humidity = dht.readHumidity();
        float current_temp;
	current_humidity= dht.readTemperature();
		
}

void displayTemperature(init8_t temperature)
{
   init8_t temp[];
if (temperature >=25)
{
  
}
else 
{

  display (--)
}

void displayHumidity( init8_t humidity)
{
 init8_t temp[];
if (humidity >= 70)
{
turn on dehimidifier 
turn on light 
display current humidity on 4 bit display
else
{ 
	display(--)

}






