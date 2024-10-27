#include <Servo.h>

Servo myServo; // Crear un objeto servo

const int trigPin = 10;  // Pin de Trigger del sensor
const int echoPin = 11;  // Pin de Echo del sensor

void setup() {
  myServo.attach(12);  // Conectar el servomotor al pin 11
  pinMode(trigPin, OUTPUT); // Configurar el pin de Trigger como salida
  pinMode(echoPin, INPUT);  // Configurar el pin de Echo como entrada
  myServo.write(90); // Posición inicial del servo (90 grados)
  Serial.begin(9600); // Inicializar la comunicación serial
}

void loop() {
  long duration, distance;

  // Enviar un pulso al sensor de ultrasonido
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer el tiempo del pulso de eco
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en cm
  distance = duration * 0.034 / 2;

  // Enviar la distancia al puerto serial
  Serial.println(distance);

  // Controlar el servomotor según la distancia
  if (distance >= 15) {
    myServo.write(135); // Mover 45 grados a la derecha
  } else {
    myServo.write(45); // Mover 45 grados a la izquierda
  }

  delay(500); // Esperar medio segundo antes de la siguiente lectura
}
