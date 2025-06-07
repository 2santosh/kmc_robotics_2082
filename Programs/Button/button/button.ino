#include <LiquidCrystal_I2C.h>

int btnPin = 3;
int btnPin2 = 4;
int count = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(btnPin2, INPUT_PULLUP);
  
  lcd.setCursor(0, 0);
  lcd.print("Count: ");
  lcd.print(count);
  lcd.setCursor(0, 1);
  lcd.print("Btn: None");
}

void loop() {
  bool btn1 = digitalRead(btnPin) == LOW;
  bool btn2 = digitalRead(btnPin2) == LOW;

  if (btn1 && !btn2) {
    count++;
    lcd.setCursor(0, 0);
    lcd.print("Count: ");
    lcd.print(count);
    lcd.print("    "); 
    lcd.setCursor(0, 1);
    lcd.print("Btn: 0     ");
    delay(200);
  } 
  else if (!btn1 && btn2) {
    count--;
    lcd.setCursor(0, 0);
    lcd.print("Count: ");
    lcd.print(count);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print("Btn: 1     ");
    delay(200);
  }
}
