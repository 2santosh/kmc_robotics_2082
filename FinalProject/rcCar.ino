#include <Servo.h>

Servo frontServo;
Servo backServo;

const int trigFront = A4;
const int echoFront = A5;
const int trigBack = A2;
const int echoBack = A3;

const int servoFrontPin = 6;
const int servoBackPin = 7;

const int buzzerPin = 8;

const int redLeft1 = A6;
const int redLeft2 = A7;


const int redRight1 = A0;
const int redRight2 = A1;
const int greenRight1 = 13;
const int greenRight2 = A8;

const int distanceThreshold = 20; 

void setup() {
  Serial.begin(9600);

  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);

  pinMode(buzzerPin, OUTPUT);

  int ledPins[] = {redLeft1, redLeft2, greenLeft1, greenLeft2, redRight1, redRight2, greenRight1, greenRight2};
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  frontServo.attach(servoFrontPin);
  backServo.attach(servoBackPin);
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; 
  return distance;
}

void indicateStatus(bool frontClear, bool backClear) {

  digitalWrite(redLeft1, !frontClear);
  digitalWrite(redLeft2, !frontClear);
  digitalWrite(greenLeft1, frontClear);
  digitalWrite(greenLeft2, frontClear);

  digitalWrite(redRight1, !backClear);
  digitalWrite(redRight2, !backClear);
  digitalWrite(greenRight1, backClear);
  digitalWrite(greenRight2, backClear);
}

void moveForward(int speed = 150) {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

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

void loop() {
 
  frontServo.write(90); delay(300);
  long frontDist = measureDistance(trigFront, echoFront);

  backServo.write(90); delay(300);
  long backDist = measureDistance(trigBack, echoBack);

  Serial.print("Front: "); Serial.print(frontDist); Serial.print(" cm | ");
  Serial.print("Back: "); Serial.print(backDist); Serial.println(" cm");

  bool frontClear = frontDist > distanceThreshold;
  bool backClear = backDist > distanceThreshold;

  indicateStatus(frontClear, backClear);

  if (!frontClear || !backClear) {
    tone(buzzerPin, 1000); 
    stopMotors();         
  } else {
    noTone(buzzerPin);   
    moveForward(150);  
  }

  delay(200);
}
