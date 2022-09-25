//Libraries
#include <Servo.h>

//Ultrasonic connections
int trigPin = 12;
int echoPin = 11;

//Servo Connection
int servoPin = 2;
Servo myservo;

//Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

//Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

//Varibles
long duration;
int distance;
bool shouldTurn = false;


void setup() {
  Serial.begin(9600);

  //Ultra Sonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Motors
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Servo
  myservo.attach(servoPin);
  myservo.write(90);
};


void getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Wie lange dauert es, bis das Signal zum Ziel und zurück geht
  duration = pulseIn(echoPin, HIGH)

  //Die Formel zur Umrechnung der Zeit in cm
  distance = duration * 0.034 / 2;

  //Wenn "Distance" kleiner oder gleich 50cm ist, setze die „shouldTurn“-Variable auf „false“
  //ansonsten auf "false" setzen
  if (distance <= 50) {
    shouldTurn = true;
  } else {
    shouldTurn = false;
  }
};


void tires() {
  //Turn the tires on the front on
  analogWrite(enA, 255);
  //Turn the tires on the back on
  analogWrite(enB, 255);

  //Settings of the dc motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
};


void turn() {
  //Turn the Servo motor to 120 dreg.
  myservo.write(120);
};

void LEDDisplay() {

};

//"loop" ist die Funktion, die bis zum Ende wiederholt und wiederholt ...
//wird
void loop() {
  //Zuerst brauchen wir den Abstand, um uns bewegen zu können
  getDistance();

  //Die Reifen sollten sich die ganze Zeit bewegen
  tires();

  //Wenn "shouldTrun" gleich "true" ist, dann drehen
  //"ShouldTurn" heißt: drehen sollte
     //Bei einem Abstand von mehr als 50 cm wird „ShouldTurn“ ...
     //zu „false“ und bei weniger zu „true“
  if (shouldTurn == true) {
    turn();
  };
}
