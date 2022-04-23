
#include <Servo.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SPI.h>
#include <Wire.h>
#define pas  20 // incrément de l'intensité
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
Servo sg90;

#define SS_PIN 10
#define RST_PIN 9
#define LED_G 7 //define green LED pin
#define LED_R 6 //define red LED
#define BUZZER 5 //buzzer pinr
char data; // variable contenant le caractère lu
int x; // variable contenant l'intensité de la deuxième lampe

void setup() {

  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  sg90.attach(8); //servo pin
  sg90.write( 90 );
  delay(300);
  sg90.write( 0 );
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();
  x=0; // Intialiser l'intensité de la deuxième lampe 

}



void loop() {

 verif();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
   

    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

   
  if (Serial.available())
  {     
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='1') //si le caractère lu est égale à 1
    {
      
 
  
  content.toUpperCase();



  if (content.substring(1) == "2A 2E C0 48") //change here the UID of the card/cards that you want to give access

  {
 

    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
   
    sg90.write(90);
    delay(3000);
    sg90.write(0);
    delay(1000);
    digitalWrite(LED_G, LOW);
 Serial.write('1'); //envoyer le nouvel état de la lampe  
  }
  else
  {
 digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);

    
  }

 }
      
     }  
    
  }


void verif()
{
 if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
   

     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message : ");


  
  content.toUpperCase();



  if (content.substring(1) == "2A 2E C0 48") //change here the UID of the card/cards that you want to give access

  {
   
 

    
    Serial.println("Authorized access");
    Serial.println();
     

    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
   
    sg90.write(90);
    delay(3000);
    sg90.write(0);
    delay(1000);
    digitalWrite(LED_G, LOW);
 
  }
 
 else   {
    
   
   
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
     
  }




}
