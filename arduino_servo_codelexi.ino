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
  Serial.print("Distancia: ");
  Serial.println(distancia);

  // Verifica la proximidad y muestra el mensaje correspondiente
  if (distancia < 10) {
    Serial.println("Cerca");
    moverServo(distancia);
  } else if (distancia >= 10 && distancia < 20) {
    Serial.println("Medio Cerca");
    moverServo(distancia);
  } else if (distancia >= 20 && distancia < 30) {
    Serial.println("Lejos");
    moverServo(distancia);
  } else {
    Serial.println("Nada");
    myservo.write(90); // Mantiene el servo en posición neutral
  }
  
  delay(250); // Espera un poco antes de la siguiente lectura
}

void moverServo(int distancia) {
  // Mueve el servo de acuerdo con la distancia
  int pos = map(distancia, 0, 30, 0, 180); // Ajusta los rangos según tu sensor
  pos = constrain(pos, 0, 180); // Limita el rango del servo

  // Ajusta la velocidad del servo
  myservo.write(pos); // Mueve el servo
  delay(map(distancia, 0, 30, 10, 100)); // Delay inversamente proporcional a la distancia
}
