#include <Servo.h>

const int trigPin = 4;
const int echoPin = 5;
long duration;
int distance;
char data;

Servo myServo;
void setup()
{
myServo.attach(6);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
Serial.begin(9600);
}

void loop() {



 while (Serial.available())
  {
    data =Serial.read();

    switch(data)
    {
      
      case 'v':
      verif();
      break;
     /* case 'n':
      off();
      break;*/
      
    }



}}


void verif()

{
distance = calculateDistance();
Serial.println(distance);

  if ( distance <48){
myServo.attach(6);
delay(3000);
myServo.write(0);
delay(500);
myServo.write(120);
delay(500);
myServo.write(0);
delay(500);
myServo.write(120);
delay(500);
myServo.write(0);
delay(500);
}}
/*void off()

{
distance = calculateDistance();
Serial.println(distance);

  if ( distance >=48){
myServo.detach();

}}*/
int calculateDistance(){

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
return distance;
}
