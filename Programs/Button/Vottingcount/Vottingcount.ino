#include <LiquidCrystal_I2C.h>

int btnSonim = 2;
int btnSobit = 3;
int btnSita = 4;
int btnResult = 5;

int Sonim = 0;
int Sobit = 0;
int Sita = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          
  lcd.backlight();     
  lcd.clear();        

  pinMode(btnSonim, INPUT_PULLUP);
  pinMode(btnSobit, INPUT_PULLUP);
  pinMode(btnSita, INPUT_PULLUP);
  pinMode(btnResult, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Voting Machine");
  delay(1000);
  lcd.clear();
}

void loop() {
  if (digitalRead(btnSonim) == LOW) {
    Sonim++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vote to: Sonim");
    lcd.setCursor(0, 1);
    lcd.print("Thank you");
    delay(5000);
  }
  else if (digitalRead(btnSobit) == LOW) {
    Sobit++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vote to: Sobit");
    lcd.setCursor(0, 1);
    lcd.print("Thank you");
    delay(5000);
  }
  else if (digitalRead(btnSita) == LOW) {
    Sita++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vote to: Sita");
    lcd.setCursor(0, 1);
    lcd.print("Thank you");
    delay(5000);
  }
  else if (digitalRead(btnResult) == LOW) {
    lcd.clear();

    String winner;
    if (Sonim >= Sobit && Sonim >= Sita) {
      winner = "Sonim";
    }
    else if (Sobit >= Sonim && Sobit >= Sita) {
      winner = "Sobit";
    }
    else {
      winner = "Sita";
    }

    int totalVotes = Sonim + Sobit + Sita;
    lcd.setCursor(0, 0);
    lcd.print("Win:");
    lcd.print(winner);
    lcd.print(" ");
    lcd.print(totalVotes);

    String voteLine = "S:" + String(Sonim) + " Sb:" + String(Sobit) + " Si:" + String(Sita) + " ";

    for (int i = 0; i < voteLine.length() - 15; i++) {
      lcd.setCursor(0, 1);
      lcd.print(voteLine.substring(i, i + 16)); 
      delay(400);
    }

    delay(1000);  
    lcd.clear();
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Voting Machine");
    delay(1000);
    lcd.clear();
  }
}
