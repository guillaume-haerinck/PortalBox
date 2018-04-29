#include <LiquidCrystal.h>
#include <Servo.h>
#include "pitches.h"

// LCD screen pins
const int en = 12,
          rs = 13,
          d4 = 4,
          d5 = 5,
          d6 = 6,
          d7 = 7;

const int solenoidPin = 9;
const int buzzerPin = 8;
// Potentiometer at analog 0 and 1

double song[] = 
{
  // Fifth line
  NOTE_D3, 0.5, NOTE_C3, 0.5,
  NOTE_D3, 0.5, NOTE_F3, 0.5, NOTE_F3, 0.5, NOTE_E3, 1.0, NOTE_E3, 0.5, NOTE_FS3, 0.5, NOTE_FS3, 1.5,

  // End of song
  0.0, 0.0
};

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Ne pas depasser 9 charactere pour le haut et 7 pour le bas
const char *lcdTop[] = {"LOCK", "INGNR", "Ingenieur", "Genir", "ngenihel", "Ngnixeur", "geneHe&re", "jenr", "unJainr", "hunsgenr"};
const char *lcdBottom[] = {"LOCK", "&ahtf", "crheTa", "Krehaty", "aatife", "CRaIa", "Creatif", "Khratiz", "crAtie", "&tif"};

bool isOpen = false;

void setup()
{
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Quelle est la");
  lcd.setCursor(0, 1);
  lcd.print("Combinaison ?");
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

    if ((potOne == 2) && (potTwo == 6))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bravo a vous !");
      lcd.setCursor(0, 1);
      lcd.print("Porte ouverte");
      playSong();
      openBox();
      delay(3000);
      lcd.clear();
      isOpen = true;
    }
  }

  if (isOpen)
  {

    lcd.setCursor(0, 0);
    lcd.print("Tout a gauche");
    lcd.setCursor(0, 1);
    lcd.print("Pour refermer");

    if ((potOne == 0) && (potTwo == 0))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aurevoir,");
      lcd.setCursor(0, 1);
      lcd.print("Et a bientot");
      closeBox();
      delay(3000);
      lcd.clear();
      isOpen = false;
    }
  }
}

void openBox()
{
  digitalWrite(solenoidPin, HIGH);
}

void closeBox()
{
  digitalWrite(solenoidPin, LOW);
}

void playSong()
{
  double duration = 1;
  for (int i = 0; duration > 0.0; i += 2)
  {
    int note = song[i];
    duration = song[i + 1];

    int noteDuration = (1600.0 * (duration / 4));
    tone(8, note, noteDuration);

    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
