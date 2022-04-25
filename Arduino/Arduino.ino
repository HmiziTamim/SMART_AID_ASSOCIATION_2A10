#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 11;
int moteur = 5;
int fanSpeed;
String stat;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  pinMode(moteur, OUTPUT);
  pinMode(pinDHT11, INPUT);
  Serial.begin(9600); //permet d’initialiser la liaison Série à 9600 bauds
  
}

void loop() {
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
    Serial.print((int)temperature ); Serial.println( "C");
     
//si message recu 
if(Serial.available())
  {    
    char data = Serial.read(); //récupérer le caractère recu
    if(data=='1')
    { 
        stat="ON";
      if(temperature <19) // if temp is lower than minimum temp
        {
          fanSpeed = 0; // fan is not spinning
          analogWrite(moteur, fanSpeed);
          digitalWrite(moteur, LOW);
          }
        if((temperature >= 19) && (temperature <= 30)) // if temperature is higher than minimum temp
           {
            digitalWrite(moteur, HIGH);
            }
     }
     else if(data=='4'){
       stat="OFF";
      digitalWrite(moteur, LOW);
     }
  }
  


   // lcd.begin();
   lcd.init();                       // initialize the lcd
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("temperature "); lcd.print((int)temperature);
  lcd.setCursor(15,0);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("System  ");lcd.print((String)stat);
  delay(2000);
}
