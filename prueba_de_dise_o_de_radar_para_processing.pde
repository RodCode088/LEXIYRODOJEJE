import processing.serial.*;

Serial myPort;  // Objeto para la comunicación serie
int distancia = 0; // Variable para almacenar la distancia
int maxDistance = 25; // Distancia máxima en cm para el sensor
float angleIncrement = 2; // Grados de incremento para el radar

void setup() {
  size(800, 800); // Tamaño de la ventana
  String portName = Serial.list()[0]; // Cambia el índice si es necesario
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(0); // Fondo negro

  // Radar
  translate(width / 2, height / 2); // Mover el origen al centro
  noFill();
  stroke(0, 100); // Color del fondo del radar
  ellipse(0, 0, 600, 600); // Círculo del radar

  // Leer datos del puerto serie
  if (myPort.available() > 0) {
    String data = myPort.readStringUntil('\n'); // Leer hasta el salto de línea
    if (data != null) {
      distancia = int(trim(data)); // Convertir a entero y limpiar espacios
    }
  }

  // Dibujar el radar
  stroke(0, 255, 0); // Color verde para el radar
  strokeWeight(2);
  for (float angle = 0; angle < 360; angle += angleIncrement) {
    float x = (distancia / (float)maxDistance) * 300 * cos(radians(angle));
    float y = (distancia / (float)maxDistance) * 300 * sin(radians(angle));
    line(0, 0, x, y); // Dibuja la línea del radar
  }

  // Mostrar la distancia en pantalla
  fill(0, 255, 0);
  textSize(32);
  textAlign(CENTER);
  text("Distancia: " + distancia + " cm", 0, 320);
}
