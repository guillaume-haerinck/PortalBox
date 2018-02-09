#include <LiquidCrystal.h>

// LCD screen pins 
const int rs = 12, 
         en = 11, 
         d4 = 5, 
         d5 = 4, 
         d6 = 3, 
         d7 = 2; 
         
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

void setup() 
{
    Serial.begin(9600);  
    lcd.begin(16,2);
}

void loop()
{
   int PotOne = map(analogRead(A0), 0, 1023, 0, 9); 
   int PotTwo = map(analogRead(A1), 0, 1023, 0, 9); 
   int PotThree = map(analogRead(A2), 0, 1023, 0, 9); 
   
   lcd.setCursor(0, 0); 
   lcd.print(PotOne); 
   lcd.setCursor(2, 0); 
   lcd.print(PotTwo); 
   lcd.setCursor(4, 0); 
   lcd.print(PotThree); 
}
