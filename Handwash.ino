#include <Wire.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DS1307RTC.h>

//Constants for sending data to DFplayer
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

//RTC I2C address for real time clock
# define DS1307_CTRL_ID 0x68
//Servo on and off indication led
# define LED 10
//IR sensor
# define IRSENSOR 3

//to tirgger the dispenser
volatile bool dis = false;
//to count the square wave from RTC
volatile unsigned int count = 0;

//variable to keep track of day and night
bool night = false;
//TO play the thank you message
bool done = false;


Servo servo;
//DFplayer initialization
SoftwareSerial DFplayer(8,9);
//Object for RTC
tmElements_t tm;


void setup () {
//Initializing IRSENSOR
pinMode(IRSENSOR,INPUT);

//Initializing DFPlayer
DFplayer.begin (9600);
playFirst();

//Initializing servo led
pinMode(LED,OUTPUT);

//interrupt for IR sensor trigger and square wave from RTC
attachInterrupt(digitalPinToInterrupt(3),dispense, RISING);
attachInterrupt(digitalPinToInterrupt(2),counter, FALLING);

//Setting the RTC to produce 1HZ signal
setSQW(0x10);
}

void loop () { 

/*Checking if the sensor is interrupted, then the servo is triggered and the audio file is played*/
  if(dis)
  {
    digitalWrite(LED,HIGH);
    //Selecting the file to play (filename : 0002.mp3)
    selectTrack(2);
    //palying the audio
    play();
    delay(3000);
    //move the servo up and down 
    servoControl();
    digitalWrite(LED,LOW);
    //reseting the value for next interrupt
    dis = false;
    done = true;
    count = 0;
  }

  if(count >= 7200) //7200 = 2hrs
  {
    //checking if it's day or night
    if(currentTime() > 22 && currentTime() < 7)
    {
      night = true;
    }
    else
    {
      night = false;  
    }
    //playing the reminder track if it's not night
    if(!night)
    {
      selectTrack(1);
      play();
    }
    //reset the clock counter
    count = 0;
  }

  //Playing the thank you message
  if(done && count >= 5)
  {
    selectTrack(4);
    play();
    delay(2000);
    selectTrack(3);
    done = false;
  }
}

void servoControl()
{
  //use this code if you are not using a 360 degree servo
  /*servo.attach(4);
   *servo.write(60);
   *delay(200);
   *servo.write(90);
   *servo.detach();
   */
   
  //for 360 degree servo
  servo.attach(4); 
  servo.write(120);
  delay(200);
  servo.write(90);
  delay(1000);
  servo.write(60);
  delay(200);
  servo.write(90); 
  servo.detach();
}

void dispense() //interrupt function for IRsenor
{
    dis = true;
}

void counter()//interrupt for RTC
{
  count++;  
}
