
//title: AIR CONDITIONER AND DEHUMIDIFIER
//name :joshua jayan and ashton chew
//admission number 2533580, 2516662
//class DCEP/FT/1A/09
//discription:
#include <Wire.h>

#include "RichShieldDHT.h"
#include "RichShieldTM1637.h"
#include "RichShieldPassiveBuzzer.h"
#include "PCA9685.h"

#define CLK 10
#define DIO 11
#define PassiveBuzzerPin 3
#define LED_GREEN 5
#define LED_BLUE 6
#define BUTTONK1 8
#define BUTTONK2 9

//musical notes
#define NOTE_L5  392
#define NOTE_M1  523
#define NOTE_M2  587
#define NOTE_M3  659
#define NOTE_M4  698
#define NOTE_M5  784
#define NOTE_M6  880

int LED[3] = {5,6}; //array for LED
int BUTTONS[3]={8,9}; //array fro BUTTONS

PCA9685 pwmController(Wire);
TM1637 disp(CLK,DIO);
PCA9685_ServoEval pwmServo1;
DHT dht;
PassiveBuzzer buz(PassiveBuzzerPin);


const static int doubleTiger[] =    //constructing of song interms of musical notes
{ 
 NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
 NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
 NOTE_M3,NOTE_M4,NOTE_M5, 
 NOTE_M3,NOTE_M4,NOTE_M5, 
 NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
 NOTE_M3,NOTE_M1, 
 NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
 NOTE_M3,NOTE_M1, 
 NOTE_M2,NOTE_L5,
 NOTE_M1,0,
 NOTE_M2,NOTE_L5,
 NOTE_M1,0
};

const static int tempo[] = //construction of song interms of tempo 1 represents a crotchet 2 represents a minium
{ 
 2,2,2,2, 
 2,2,2,2, 
 2,2,1, 
 2,2,1,  
 2,2,2,2,
 1,1,
 2,2,2,2,
 1,1,
 1,1,
 1,1,
 1,1,
 1,1
};

//initialisation of components
void setup()
{
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  pinMode(BUTTONK1,INPUT_PULLUP);
  pinMode(BUTTONK2,INPUT_PULLUP);
  disp.init();
  dht.begin();
}

int i, temperature;

void loop()
{
  //program for dehumidifier

  float h = dht.readHumidity();//reading humidity

  if( digitalRead(BUTTONS[0]) ==0 ) //if button is pressed heres what to do
  {
  delay(300);
  displayHumidity((int8_t)h);
  delay(3000);
   while(h>51) //if the humidity is greater than 51, turn on dehumidifier
   {  
     sing();
     displayHumidity((int8_t)h);
     delay(3000); 
   }
   displayHumidity((int8_t)h);
   delay(3000); 
   digitalWrite(LED[0],HIGH);

   while(digitalRead(BUTTONS[0])==0 );    // press and let go the the blue button once 

  }
else 
{

  int8_t dash[4]={16,16,16,16};   // 7 segment display will show (----) showing that dehumidifier is turned off
  disp.display(dash);                  
  delay(3000);

}
  // program for airconditioner
  
  float t = dht.readTemperature(); //reading temperature
  
  if(digitalRead(BUTTONS[1])==0) //if button is pressed heres what to do 
   {
    delay(300);
    displayTemperature((int8_t)t);
     while(t>27)  // airconditioner turns on when the temperature is greater than 27C
      {
       {
		    //Lower Servo (Channel 1) Control

    for (i = 0; i <= 90; i += 5) { //Slow Turn anti-clockwise (from 0 to 90 degree
        pwmController.setChannelPWM(1, pwmServo1.pwmForAngle(i));
        delay(250);  //longer delay for Slow turn movement
    }

    for (i = 90; i >= 0; i -= 5) { //Fast Turn clockwise (from 90 to 0 degree)
        pwmController.setChannelPWM(1, pwmServo1.pwmForAngle(i));
        delay(100); //shorter delay for faster turn movement
    }

    for (i = 0; i >= -90; i -= 5) { //Slow Turn clockwise (from 0 to -90 degree)
        pwmController.setChannelPWM(1, pwmServo1.pwmForAngle(i));
        delay(250); //longer delay for Slow turn movement
    }

    for (i = -90; i <= 0; i += 5) { //Fast Turn anti-clockwise (from -90 to 0 degree)
        pwmController.setChannelPWM(1, pwmServo1.pwmForAngle(i));
        delay(100); //shorter delay for faster turn movement
    }
     delay(3000);
  }


       displayTemperature((int8_t)t);
       delay(3000);
      }
      displayTemperature((int8_t)t);
      delay(3000);
      digitalWrite(LED[1],HIGH);

      while(digitalRead(BUTTONS[1])==0); //program runs when you press yellow button and let go
        

   }
else
  {
    int8_t dash[4]={16,16,16,16};  // 7 segment displays will show (----), meaning airconditioner is off
    disp.display(dash);        
    delay(3000);
  }


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
  disp.display(3,14); //display "E"
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

void sing() {                                                           //sing function declaration
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


