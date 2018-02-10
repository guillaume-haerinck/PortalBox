#include <LiquidCrystal.h>

// LCD screen pins
const int rs = 12,
          en = 11,
          d4 = 5,
          d5 = 4,
          d6 = 3,
          d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char *lcdTop[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
const char *lcdBottom[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Text d'intro");
  delay(3000);
  lcd.clear();
}

void loop()
{
  int potOne = map(analogRead(A0), 0, 1023, 0, 9);
  int potTwo = map(analogRead(A1), 0, 1023, 0, 9);
  
  if ((potOne == 3) && (potTwo == 6))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bravo");
    delay(3000);
    lcd.clear();
  }
  else 
  {
    lcd.setCursor(0, 0);
    lcd.print(lcdTop[potOne]);
    lcd.setCursor(0, 1);
    lcd.print(lcdBottom[potTwo]);
  }
}
