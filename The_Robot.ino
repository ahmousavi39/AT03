//Libraries
#include <Servo.h>

//Ultrasonic connections
int trigPin = 12;
int echoPin = 11;

//Servo Connection
int servoPin = 9;
Servo myservo;

//LED Display
int latchPin = 3;
int clockPin = 13;
int dataPin = 2;

//Motor A
const int motorPinEnA = 4;  // Pin 8 of L293
const int motorPin1 = 5;  // Pin 14 of L293
const int motorPin2 = 6;  // Pin 10 of L293
//Motor B
const int motorPinEnB = 8;  // Pin 16 of L293
const int motorPin3 = 10; // Pin  7 of L293
const int motorPin4 = 7;  // Pin  2 of L293

//Varibles
long duration;
int distance;
bool shouldTurn = false;
//Digits Matrix - 0 a 9
byte seven_seg_digits[10] = { B11111101,  // = 0
                              B01100001,  // = 1
                              B11011011,  // = 2
                              B11110011,  // = 3
                              B01100111,  // = 4
                              B10110111,  // = 5
                              B10111111,  // = 6
                              B11100001,  // = 7
                              B11111111,  // = 8
                              B11100111   // = 9
                            };


void setup() {
  Serial.begin(9600);

  //Ultra Sonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Motors
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorPinEnA, OUTPUT);
  pinMode(motorPinEnB, OUTPUT);

  //Servo
  myservo.attach(servoPin);
  myservo.write(85);

  //LED Display
  pinMode(latchPin, OUTPUT); // Define the 3 digital pins as output
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
};



void getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Wie lange dauert es, bis das Signal zum Ziel und zurück geht
  duration = pulseIn(echoPin, HIGH);

  //Die Formel zur Umrechnung der Zeit in cm
  distance = duration * 0.034 / 2;

  //Wenn "Distance" kleiner oder gleich 50cm ist, setze die „shouldTurn“-Variable auf „false“
  //ansonsten auf "false" setzen
  if (distance < 45) {
    shouldTurn = true;
  } else {
    shouldTurn = false;
  };
};


void tires() {
  if (shouldTurn) {
    analogWrite(motorPinEnA, 150);
    analogWrite(motorPinEnB, 150);
  } else {
    analogWrite(motorPinEnA, 250);
    analogWrite(motorPinEnB, 250);
  };
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
};



void turn() {
  //Turn the Servo motor to 120 dreg.
  for (int i = 85; i < 120; i = i + 2) {
    myservo.write(i);
    delay(25);
  };
  delay(10);
  for (int i = 120; i > 85; i = i - 2) {
    myservo.write(i);
    delay(25);
  };
};


void LEDDisplay(int distance) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);

  // the original data (bit pattern)
  if (distance < 4) {
    shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[distance]);
  } else {
    shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[3]);
  };
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
  
  delay(1000);
};


//"loop" ist die Funktion, die bis zum Ende wiederholt und wiederholt ...
//wird
void loop() {
  //Zuerst brauchen wir den Abstand, um uns bewegen zu können
  getDistance();

  //Zeigen der Abstand
  LEDDisplay(static_cast<int>(distance / 100));

  //Die Reifen sollten sich die ganze Zeit bewegen
  tires();

  //Wenn "shouldTrun" gleich "true" ist, dann drehen
  //"ShouldTurn" heißt: drehen sollte
  //Bei einem Abstand von mehr als 50 cm wird „ShouldTurn“ ...
  //zu „false“ und bei weniger zu „true“
  if (shouldTurn == true) {
    turn();
  };
};
