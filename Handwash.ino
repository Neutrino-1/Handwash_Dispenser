#include <Wire.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DS1307RTC.h>

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define DS1307_CTRL_ID 0x68
# define LED 10

volatile bool dis = false;
volatile unsigned int count = 0;

bool night = false;
bool done = false;

Servo servo;
SoftwareSerial DFplayer(8,9);
tmElements_t tm;

void setup () {
Serial.begin(9600);
pinMode(3,INPUT);
DFplayer.begin (9600);
playFirst();
pinMode(LED,OUTPUT);
attachInterrupt(digitalPinToInterrupt(3),dispense, RISING);
attachInterrupt(digitalPinToInterrupt(2),counter, FALLING);
setSQW(0x10);
}

void loop () { 

  if(dis)
  {
    digitalWrite(LED,HIGH);
    Serial.println("Dispensing handwash!"); 
    selectTrack(2);
    play();
    delay(3000);
    servoControl();
    digitalWrite(LED,LOW);
    dis = false;
    done = true;
    count = 0;
  }

  if(count >= 30) //7200 = 2hrs
  {
    if(currentTime() > 22 && currentTime() < 7)
    {
      night = true;
    }
    else
    {
      night = false;  
    }
    if(!night)
    {
      selectTrack(1);
      play();
    }
    count = 0;
  }

  if(done && count >= 5)
  {
    selectTrack(4);
    play();
    delay(2000);
    selectTrack(3);
    done = false;
  }

if(Serial.available())
{
  int a = Serial.parseInt();  
  Serial.println(a);
  servo.write(a);
  delay(200);
  servo.write(90);
}

}

void servoControl()
{
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

void dispense()
{
    dis = true;
}

void counter()
{
  count++;  
}
