#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
long duracion;
int distancia;

Servo myservo;  // Crea un objeto Servo

void setup() {
  myservo.attach(12);  // Conecta el servo al pin 12
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Mide la distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion * 0.034) / 2;

  // Envía la distancia al puerto serie
  Serial.println(distancia);
  
  // Mueve el servo de acuerdo con la distancia
  int pos = map(distancia, 0, 25, 0, 180); // Ajusta los rangos según tu sensor
  pos = constrain(pos, 100, 90); // Limita el rango del servo
  myservo.write(pos); // Mueve el servo
  delay(2500); // Espera medio segundo antes de la siguiente lectura
}
