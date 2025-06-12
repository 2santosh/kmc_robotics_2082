#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, Arduino!");
  delay(500);

  lcd.setCursor(0, 1);
  lcd.print("Hello, Arduino 2!");
  delay(1000);

}

void loop() {
  lcd.scrollDisplayLeft();
  delay(1000);
}
