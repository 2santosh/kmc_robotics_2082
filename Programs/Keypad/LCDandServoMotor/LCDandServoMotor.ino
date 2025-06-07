#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>

const int ROWS = 4;
const int COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

int servoPin = 10;
int lockPos = 0;
int unlockPos = 90;

String inputPin = "";
bool isLocked = true;
bool alarmOn = false;
int screenState = 0;

int brightnessLevels[] = {0, 64, 128, 192, 255};
int currentBrightnessIndex = 2;

unsigned long lastActivityTime = 0;
const unsigned long timeoutDuration = 30000;

const int maxUsers = 3;
String users[maxUsers];
String userNames[maxUsers] = {"Kumar", "Santosh", "Nischal"};

const int eepromPinStart = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  doorServo.attach(servoPin);
  lockDoor();

  lcd.print("System Booting");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print("#");
    delay(125);
  }

  loadUsersFromEEPROM();

  lcd.clear();
  lcd.print("Enter PIN:");
  screenState = 0;

  lastActivityTime = millis();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lastActivityTime = millis();
    Serial.print("Key pressed: ");
    Serial.println(key);

    if (screenState == 0) {
      if (key >= '0' && key <= '9') {
        if (inputPin.length() < 10) {
          inputPin += key;
          updateDisplay();
        }
      }
      else if (key == 'A') {
        int userIndex = findUserIndex(inputPin);
        if (userIndex >= 0) {
          lcd.clear();
          lcd.print("Access Granted");
          lcd.setCursor(0, 1);
          lcd.print("Welcome ");
          lcd.print(userNames[userIndex]);
          unlockDoor();
          screenState = 1;
          delay(2000);
          lcd.clear();
          lcd.print("Welcome!");
        } else {
          lcd.clear();
          lcd.print(" Wrong PIN! ");
          delay(1500);
          lcd.clear();
          lcd.print("Enter PIN:");
          lockDoor();
        }
        inputPin = "";
      }
      else if (key == 'C') {
        if (inputPin.length() > 0) {
          inputPin.remove(inputPin.length() - 1);
          updateDisplay();
        }
      }
      else if (key == 'D') {
        lcd.clear();
        lcd.print("Set New PIN:");
        inputPin = "";
        while (true) {
          char newKey = keypad.getKey();
          if (newKey) {
            if (newKey >= '0' && newKey <= '9') {
              if (inputPin.length() < 10) {
                inputPin += newKey;
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print(inputPin);
              }
            }
            else if (newKey == 'A') {
              if (inputPin.length() > 0) {
                users[0] = inputPin;
                saveUserPinToEEPROM(0);
                lcd.clear();
                lcd.print("New PIN Set!");
                delay(1500);
              } else {
                lcd.clear();
                lcd.print("PIN Empty!");
                delay(1500);
              }
              lcd.clear();
              lcd.print("Enter PIN:");
              inputPin = "";
              break;
            }
            else if (newKey == 'C') {
              if (inputPin.length() > 0) {
                inputPin.remove(inputPin.length() - 1);
                lcd.setCursor(0, 1);
                lcd.print("                ");
                lcd.setCursor(0, 1);
                lcd.print(inputPin);
              }
            }
          }
        }
      }
    }

    if (key == 'B') {
      lcd.clear();
      lcd.print(" System Locked ");
      lockDoor();
      delay(1500);
      lcd.clear();
      lcd.print("Enter PIN:");
      inputPin = "";
      screenState = 0;
    }

    else if (key == '#') {
      alarmOn = !alarmOn;
      lcd.clear();
      lcd.print(alarmOn ? " Alarm ON  🔔 " : " Alarm OFF     ");
      delay(1500);
      if (screenState == 0) {
        lcd.clear();
        lcd.print("Enter PIN:");
        updateDisplay();
      }
    }

    else if (key == '*') {
      currentBrightnessIndex++;
      if (currentBrightnessIndex > 4) currentBrightnessIndex = 0;
      lcd.clear();
      lcd.print("Brightness:");
      int percent = map(brightnessLevels[currentBrightnessIndex], 0, 255, 0, 100);
      lcd.print(percent);
      lcd.print("%");
      delay(1500);
      if (screenState == 0) {
        lcd.clear();
        lcd.print("Enter PIN:");
        updateDisplay();
      }
    }
  }

  if (!isLocked && (millis() - lastActivityTime > timeoutDuration)) {
    lockDoor();
    lcd.clear();
    lcd.print("Auto Locked");
    delay(1500);
    lcd.clear();
    lcd.print("Enter PIN:");
    screenState = 0;
    inputPin = "";
  }
}

void updateDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  for (int i = 0; i < inputPin.length(); i++) lcd.print("*");
}

void unlockDoor() {
  doorServo.write(unlockPos);
  isLocked = false;
}

void lockDoor() {
  doorServo.write(lockPos);
  isLocked = true;
}

int findUserIndex(String pin) {
  for (int i = 0; i < maxUsers; i++) {
    if (users[i] == pin) return i;
  }
  return -1;
}

void saveUserPinToEEPROM(int userIndex) {
  int baseAddr = eepromPinStart + userIndex * 10;
  String pin = users[userIndex];
  for (int i = 0; i < 10; i++) {
    if (i < pin.length()) {
      EEPROM.write(baseAddr + i, pin[i]);
    } else {
      EEPROM.write(baseAddr + i, '\0');
    }
  }
}

String readUserPinFromEEPROM(int userIndex) {
  int baseAddr = eepromPinStart + userIndex * 10;
  String pin = "";
  for (int i = 0; i < 10; i++) {
    char c = EEPROM.read(baseAddr + i);
    if (c == '\0' || c == 255) break;
    pin += c;
  }
  return pin;
}

void loadUsersFromEEPROM() {
  for (int i = 0; i < maxUsers; i++) {
    String pin = readUserPinFromEEPROM(i);
    if (pin == "") {
      if (i == 0) pin = "123";
      else if (i == 1) pin = "456";
      else if (i == 2) pin = "789";
      users[i] = pin;
      saveUserPinToEEPROM(i);
    } else {
      users[i] = pin;
    }
  }
}