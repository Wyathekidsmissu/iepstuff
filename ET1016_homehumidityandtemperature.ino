
//title: AIR CONDITIONER AND DEHUMIDIFIER
//name :joshua jayan and ashton chew
//admission number 2533580, 2516662
//class DCEP/FT/1A/09
//discription:
#include <Wire.h>

#include "RichShieldDHT.h"
#include "RichShieldTM1637.h"
#include "RichShieldPassiveBuzzer.h"


//components to be used
#define CLK 10
#define DIO 11
#define PassiveBuzzerPin 3
#define LED_GREEN 5
#define LED_BLUE 6
#define KEY1_PIN 9
#define KEY2_PIN 8
#define BUTTONK1 8
#define BUTTONK2 9

//declaring of musical notes
#define NOTE_L1  262
#define NOTE_L2  294
#define NOTE_L3  330
#define NOTE_L4  349
#define NOTE_L5  392
#define NOTE_L6  440
#define NOTE_L7  494
#define NOTE_M1  523
#define NOTE_M2  587
#define NOTE_M3  659
#define NOTE_M4  698
#define NOTE_M5  784
#define NOTE_M6  880
#define NOTE_M7  988
#define NOTE_H1  1046
#define NOTE_H2  1175
#define NOTE_H3  1318
#define NOTE_H4  1397
#define NOTE_H5  1568
#define NOTE_H6  1760
#define NOTE_H7  1976



TM1637 disp(CLK,DIO);

DHT dht;

void setup() 
{
	disp.init();  
	dht.begin();
	Serial.begin(9600)
	pinMode (LED_BLUE,OUTPUT);
	pinMode (LED_GREEN,OUTPUT);
	pinMode (BUTTONK1,INPUT_PULLUP);
	pinMode(BUTTONK2,INPUT_PULLUP);
	disp.init();
	disp.display(count);
}

void loop()
{
        digitalWrite(LED_BLUE,LOW); // blue led off 
        digitalWrite(LED_GREEN,LOW);//green led off
        float h = dht.readHumidity(); //reading humidity sensor
        float t = dht.readTemperature();// reading temperature sensor

	if(digitalRead BUTTONK1 == 0 )
	{
	  uint8_t dash = 0x40;
	  display.setSegments((uint8_t[]){dash, dash, dash, dash});
	}
	else 
	{ 
	  displayTemperature((int8_t)t);//display temperature
          delay(3000);
	}
		
}





void displayTemperature(int8_t temperature)
{
  int8_t temp[4];
  if(temperature < 0)
	{
		temp[0] = INDEX_NEGATIVE_SIGN;
		temperature = abs(temperature);
	}
	else if(temperature < 100)temp[0] = INDEX_BLANK;
	else temp[0] = temperature/100;
	temperature %= 100;
	temp[1] = temperature / 10;
	temp[2] = temperature % 10;
	temp[3] = 12;	          //index of 'C' for celsius degree symbol.
	disp.display(temp);
}

void displayHumidity(int8_t humi)
{
  int8_t temp[4];
  if(humi < 100)temp[0] = INDEX_BLANK;
  else temp[0] = humi/100;
  humi %= 100;
  temp[1] = humi / 10;
  temp[2] = humi % 10;
  temp[3] = 18;	          //index of 'H' for celsius degree symbol.
  disp.display(temp);
}

void displayError()
{
  disp.display(3,14);//display "E"
}

void sing() {
  // iterate over the notes of the melody:
    int size = sizeof(doubleTiger) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 500 / tempo[thisNote];//a beat for 0.5 second

      buz.playTone(doubleTiger[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 0.30;
      delay(pauseBetweenNotes);
    }
}
	






