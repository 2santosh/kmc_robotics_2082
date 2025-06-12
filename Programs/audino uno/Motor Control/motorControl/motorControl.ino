#include <Servo.h>

// ==== Servo Objects ====
Servo frontServo;
Servo backServo;

// ==== Ultrasonic Pins ====
const int trigFront = A4;
const int echoFront = A5;
const int trigBack = A2;
const int echoBack = A3;

// ==== Servo Pins ====
const int servoFrontPin = 6;
const int servoBackPin = 7;

// ==== Buzzer Pin ====
const int buzzerPin = 8;

// ==== LED Pins ====
const int redLeft1 = A6;
const int redLeft2 = A7;
const int greenLeft1 = 11;
const int greenLeft2 = 12;

const int redRight1 = A0;
const int redRight2 = A1;
const int greenRight1 = 13;
const int greenRight2 = A8;

// ==== Motor Driver Pins ====
int IN1 = 2;
int IN2 = 3;
int ENA = 9;
int IN3 = 4;
int IN4 = 5;
int ENB = 10;

// ==== Distance Threshold ====
const int distanceThreshold = 20; // cm

// ==== Setup ====
void setup() {
  Serial.begin(9600);

  // Ultrasonic pins
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);

  // Buzzer
  pinMode(buzzerPin, OUTPUT);

  // LEDs
  int ledPins[] = {redLeft1, redLeft2, greenLeft1, greenLeft2, redRight1, redRight2, greenRight1, greenRight2};
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Motor Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Servos
  frontServo.attach(servoFrontPin);
  backServo.attach(servoBackPin);
}

// ==== Measure Distance Function ====
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// ==== LED Indicator ====
void indicateStatus(bool frontClear, bool backClear) {
  // Left LEDs
  digitalWrite(redLeft1, !frontClear);
  digitalWrite(redLeft2, !frontClear);
  digitalWrite(greenLeft1, frontClear);
  digitalWrite(greenLeft2, frontClear);

  // Right LEDs
  digitalWrite(redRight1, !backClear);
  digitalWrite(redRight2, !backClear);
  digitalWrite(greenRight1, backClear);
  digitalWrite(greenRight2, backClear);
}

// ==== Motor Control ====
void moveForward(int speed = 150) {
  // Left Motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  // Right Motor
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

// ==== Main Loop ====
void loop() {
  // Sweep front servo and measure distance
  frontServo.write(90); delay(300);
  long frontDist = measureDistance(trigFront, echoFront);

  // Sweep back servo and measure distance
  backServo.write(90); delay(300);
  long backDist = measureDistance(trigBack, echoBack);

  // Display distances in Serial Monitor
  Serial.print("Front: "); Serial.print(frontDist); Serial.print(" cm | ");
  Serial.print("Back: "); Serial.print(backDist); Serial.println(" cm");

  // Check status
  bool frontClear = frontDist > distanceThreshold;
  bool backClear = backDist > distanceThreshold;

  indicateStatus(frontClear, backClear);

  if (!frontClear || !backClear) {
    tone(buzzerPin, 1000); // Buzzer ON
    stopMotors();          // Stop motors
  } else {
    noTone(buzzerPin);     // Buzzer OFF
    moveForward(150);      // Move forward
  }

  delay(200); // short delay
}
