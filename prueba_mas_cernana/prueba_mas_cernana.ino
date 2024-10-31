#include <Servo.h>

Servo myServo;  // Crea un objeto servo

const int trigPin = 10;  // Pin Trigger del sensor ultrasónico
const int echoPin = 11;  // Pin Echo del sensor ultrasónico

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serie
  myServo.attach(12);  // Conecta el servo al pin 12
  pinMode(trigPin, OUTPUT);  // Configura el pin de Trigger como salida
  pinMode(echoPin, INPUT);   // Configura el pin de Echo como entrada
}

void loop() {
  long duration, distance;

  // Limpia el pin de Trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Envía un pulso de 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lee el tiempo de duración del pulso
  duration = pulseIn(echoPin, HIGH);
  // Calcula la distancia en cm
  distance = duration * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Si la distancia es mayor a un umbral (por ejemplo, 20 cm)
  if (distance > 20) {
    // Mueve el servo hacia la dirección del objeto
    myServo.write(90);  // Cambia el ángulo según la dirección deseada
    delay(1000);  // Espera un segundo
  } else {
    myServo.write(0);  // Posición de reposo
  }

  delay(1500);  // Espera medio segundo antes de la siguiente lectura
}
