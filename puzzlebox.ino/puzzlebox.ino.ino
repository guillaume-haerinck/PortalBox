#include <LiquidCrystal.h>
#include <Servo.h> 

// LCD screen pins
const int rs = 12,
          en = 11,
          d4 = 5,
          d5 = 4,
          d6 = 3,
          d7 = 2;

const int servoPin = 10;
const int buzzerPin = 9;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char *lcdTop[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
const char *lcdBottom[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int pos = 0;    // variable to store the servo position 
Servo myservo;  // create servo object to control a servo

bool isOpen = false;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
  myservo.write(pos); // set the servo in position 0 
  
  lcd.setCursor(0, 0);
  lcd.print("Text d'intro");
  delay(3000);
  lcd.clear();
}

void loop()
{
  int potOne = map(analogRead(A0), 0, 1023, 0, 9);
  int potTwo = map(analogRead(A1), 0, 1023, 0, 9);
  
  if (!isOpen)
  {
    lcd.setCursor(0, 0);
    lcd.print(lcdTop[potOne]);
    lcd.setCursor(0, 1);
    lcd.print(lcdBottom[potTwo]);
  
    if ((potOne == 3) && (potTwo == 6))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bravo");
      openBox();
      delay(3000);
      lcd.clear();
      isOpen = true;
    }
  }
  
  if (isOpen)
  {
    
    lcd.setCursor(0, 0);
    lcd.print("Position 0");
    lcd.setCursor(0, 1);
    lcd.print("Pour refermer");
      
    if ((potOne == 0) && (potTwo == 0))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aurevoir");
      closeBox();
      delay(3000);
      lcd.clear();
      isOpen = false;
    }
  }
}

void openBox()
{
  for (pos = 0; pos <= 90; pos += 1)
  { // goes from 0 degrees to 90 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void closeBox()
{
  for (pos = 90; pos >= 0; pos -= 1)
  { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
