// WAP to mke a voting machine 3 buttins for canditates 1 btn for displaying result also display the messages in lcd accordingly 

#include <LiquidCrystal_I2C.h>

int btnPin = 3;
int btnPin2 = 4;
int btnPin3 = 4;
int btnPin3 = 5;

int Sonim = 0;
int Sobit = 0;
int Sita = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(btnPin2, INPUT_PULLUP);
  pinMode(btnPin3, INPUT_PULLUP);
  
  lcd.setCursor(0, 0);
  lcd.print("Votting: ");
}

void loop() {

  if (digitalRead(btnPin) == LOW && digitalRead(btnPin2) == HIGH) && digitalRead(btnPin3 == HIGH) {
    Sonim++;
    lcd.setCursor(0, 1);
    lcd.print("Sonim: ");
    lcd.print(Sonim);
    lcd.print("Btn: 0     ");
    delay(200);
  } 
  else if (digitalRead(btnPin) == LOW && digitalRead(btnPin2) == HIGH) && digitalRead(btnPin3 == HIGH) {
    Sobit++;
    lcd.setCursor(0, 1);
    lcd.print("Sobit: ");
    lcd.print(Sobit);
    delay(200);
  }
 else if (digitalRead(btnPin) == LOW && digitalRead(btnPin2) == HIGH) && digitalRead(btnPin3 == HIGH) {
    Sita++;
    lcd.setCursor(0, 1);
    lcd.print("Sita: ");
    lcd.print(Sita);
    delay(200);
  }
  else{
    delay(200);
  }
}


