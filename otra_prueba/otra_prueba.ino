#include <Servo.h>

const int trigPin = 10;   // Pin del Trigger
const int echoPin = 11;   // Pin del Echo
long duracion;            // Variable para la duración del pulso
int distancia;            // Variable para la distancia medida

Servo myservo;            // Crea un objeto Servo

int pos = 0;              // Variable para almacenar la posición del servo
bool moving = false;      // Variable para verificar si el servo ya se está moviendo

void setup() {
  myservo.attach(12);     // Conecta el servo al pin 12
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);     // Inicializa la comunicación serie
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

  Serial.println( distancia); // Imprime la distancia medida en el monitor serie

  // Si la distancia es menor a 30 cm y el servo no se está moviendo
  if (distancia < 30 && !moving) {
    moving = false; // Indica que el servo está en movimiento
    // Mueve el servo de 0 a 90 grados
    for (pos = 0; pos <= 90; pos += 1) { 
      myservo.write(pos);
      delay(150); // Espera un poco para que el servo llegue a la posición
    }
    delay(100); // Espera medio segundo en la posición 90

    // Mueve el servo de 90 a 0 grados
    for (pos = 90; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15); // Espera un poco para que el servo llegue a la posición
    }

    moving = false; // Indica que el servo ha terminado de moverse
    delay(1000); // Espera un segundo antes de medir de nuevo
  }

  delay(100); // Pequeña pausa antes de la próxima lectura
}
