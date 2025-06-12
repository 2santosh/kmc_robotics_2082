#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String messages[] = {
  "Hello, Arduino!",
  "Random Message 1",
  "LCD Fun Time!",
  "I2C Display Test",
  "Scroll it out!",
  "Code is cool :)",
  "DIY Electronics!",
  "What's up, world?"
};

unsigned long lastChangeTime = 0;
unsigned long lastScrollTime = 0;
const int messageChangeInterval = 5000;
const int scrollInterval = 1000; 


void setup() {
  lcd.init();
  lcd.backlight();
  randomSeed(analogRead(0)); 
  showRandomMessage();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastScrollTime >= scrollInterval) {
    lcd.scrollDisplayLeft();
    lastScrollTime = currentTime;
  }

  if (currentTime - lastChangeTime >= messageChangeInterval) {
    lcd.clear();
    showRandomMessage();
    lastChangeTime = currentTime;
  }
}

void showRandomMessage() {
  int index = random(0, sizeof(messages) / sizeof(messages[0]));
  int index1 = random(1, sizeof(messages) / sizeof(messages[1]));

  lcd.setCursor(0, 0);
  delay(200);
  lcd.print(messages[index]);
  lcd.setCursor(0, 1);
  lcd.print(messages[index1]);
  delay(200);

}