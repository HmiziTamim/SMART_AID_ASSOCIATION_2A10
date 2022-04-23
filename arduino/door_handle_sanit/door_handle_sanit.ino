#include <Servo.h>

const int trigPin = 4;
const int echoPin = 5;
long duration;
int distance;
char data;

Servo myServo;
void setup() {
myServo.attach(6);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
Serial.begin(9600);

}



void loop() {
  detec();
  if (Serial.available())
  {     
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='1') //si le caractère lu est égale à 1
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
      
     
     }  
     Serial.write('1'); //envoyer le nouvel état de la lampe  
  }
}
}

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

void detec()
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

}
else
myServo.detach();
}
