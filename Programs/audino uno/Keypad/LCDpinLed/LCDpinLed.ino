#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo servo1;
int ledPin = 10;  
int brightness = 0;
int fadeValue = 10;
bool pinMatched = false;
int servoPin = 13;

const byte ROWS = 4;
const byte COLS = 4;

LiquidCrystal_I2C lcd(0x27, 16, 2);

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String enteredPin = "";  
String correctPin = "123"; 

void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Enter your Pin:");

  keypad.setHoldTime(200);      
  keypad.setDebounceTime(50);   

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  servo1.attach(servoPin);
}

void loop() {
  char key = keypad.getKey();
  KeyState keyState = keypad.getState();
  servo1.write(0);

  if (key) {
    Serial.println(key);

    if (key == 'C') {
      enteredPin = "";
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }

    else if (key == 'D') {
      lcd.setCursor(0, 1);
      if (enteredPin.length() == correctPin.length()) {
        if (enteredPin == correctPin) {
          pinMatched = true;
          brightness = 100;  
          lcd.setCursor(0, 1);
          lcd.print("Pin Match!     ");
          delay(2000);
          lcd.clear();
          lcd.print("Control ON");
          
          servo1.write(90);
          delay(1000);
          servo1.write(0);
        } else {
          lcd.setCursor(0, 1);
          lcd.print("Wrong Pin!     ");
          delay(2000);
          lcd.setCursor(0, 1);
          lcd.print("                ");
        }
        enteredPin = "";
      }
    }

    else if ((key == '*' || key == '#') && pinMatched && 
             (keyState == HOLD || keyState == PRESSED)) {
      if (key == '*') {
        brightness += fadeValue;
        if (brightness > 255) brightness = 255;
        lcd.setCursor(0, 1);
        lcd.print("LED Brightness +       ");
      } 
      else if (key == '#') {
        brightness -= fadeValue;
        if (brightness < 0) brightness = 0;
        lcd.setCursor(0, 1);
        lcd.print("LED Brightness -       ");
      }
      analogWrite(ledPin, brightness);
      delay(100);  
    }


    else if (key != '*' && key != '#') {
      enteredPin += key;
      lcd.setCursor(0, 1);
      lcd.print("Pin: ");
      lcd.print(enteredPin);
    }
  }

  analogWrite(ledPin, brightness);
}
