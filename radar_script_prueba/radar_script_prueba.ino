#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
long duracion;
int distancia;


Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

void setup() {
  myservo.attach(12);  // attaches the servo on pin 9 to the Servo object
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion * 0.034) / 2;
  Serial.println(distancia);
  delay(500);
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

