#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // check https://create.arduino.cc/projecthub/najad/interfacing-lcd1602-with-arduino-764ec4 for information on 1602 LCD wiring


#include "IRremote.h"
/*-----( Declare Constants )-----*/
int receiver = 13; // pin 1 of IR receiver to Arduino digital pin 3
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
/*-----( Declare Variables )-----*/


int food; // Declare food type/time var
const int buzzer = 8; // Active buzzer pin assigned to Digital IO 8


void setup() {
  lcd.begin(16, 2);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Select Food 1-4");

  Serial.begin(9600);
  Serial.println("IR Receiver Raw Data + Button Decode Test");
  irrecv.enableIRIn(); // Start the receiver

  pinMode(buzzer,OUTPUT);
}

void loop()
{
  Serial.println(cooking);
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
//    Serial.println(results.value, HEX); // UN Comment to see raw values
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}


void translateIR() // takes action based on IR code received
{
  switch(results.value)
  {


  case 0xFF30CF: // 1 on IR Remote
  food = 30;  
    Serial.println(" Fish              ");
    lcd.begin(16, 2);
    lcd.print("Fish"); 
    break;

  case 0xFF18E7: // 2 on IR Remote
  food = 80; 
    Serial.println(" Trophy Fish              "); 
    lcd.begin(16, 2);
    lcd.print("Trophy Fish");
    break;

  case 0xFF7A85: // 3 on IR Remote
  food = 50;  
    Serial.println(" Meat              ");
    lcd.begin(16, 2);
    lcd.print("Meat"); 
    break;

  case 0xFF10EF: // 4 on IR Remote
  food = 100;  
    Serial.println(" Monster              "); 
    lcd.begin(16, 2);
    lcd.print("Monster");
    break;

  case 0xFF02FD: // Play/Pause on IR Remote
    Serial.println(" --COOKING START--           ");
    lcd.begin(16, 2);
    lcd.print("COOKING START");
      delay(food*1000);
      digitalWrite(buzzer, HIGH);
      delay(1500);                // buzzer beeps, and screen displays COOKING DONE
      digitalWrite(buzzer, LOW);
      lcd.begin(16, 2);
      lcd.print("");
      lcd.print("COOKING DONE");
      lcd.print("");
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("Select Food 1-4");
      
    break;
  
  }
  delay(500);
}
