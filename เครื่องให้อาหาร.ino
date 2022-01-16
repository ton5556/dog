#define fill 155 
#define empty 20 
#define potPin A0 

#include <Servo.h> 
Servo mainServo; 
int trigger = 0;
int potIn = 0;
int count = 1;
void setup(){
  mainServo.attach(3);
  pinMode(4, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(10, LOW);
}
void loop(){
  potIn = analogRead(potPin);
  if(!trigger)
{
mainServo.write(fill);
for(;count>=0;count--)
{
for(;potIn>0;potIn=potIn-20)
{
digitalWrite(11,HIGH); 
delay(100+potIn);
digitalWrite(11,LOW);
delay(100+potIn);
}
}
count = 1;
trigger = 1;
digitalWrite(11,LOW); 
}
else if(trigger)
{
mainServo.write(empty); 
delay(1000); 
trigger = 0;
}
}
