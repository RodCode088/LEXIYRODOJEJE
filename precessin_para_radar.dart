import processing.serial.*;

Serial myPort;  // Objeto para la comunicación serie
int distancia = 0; // Variable para almacenar la distancia

void setup() {
  size(800, 800); // Tamaño de la ventana
  String portName = Serial.list()[0]; // Cambia el índice si es necesario
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(255); // Fondo blanco

  // Leer datos del puerto serie
  if (myPort.available() > 0) {
    String data = myPort.readStringUntil('\n'); // Leer hasta el salto de línea
    if (data != null) {
      distancia = int(trim(data)); // Convertir a entero y limpiar espacios
    }
  }

  // Dibujar el radar
  translate(width / 2, height / 2); // Mover el origen al centro
  stroke(0);
  noFill();
  ellipse(0, 0, 400, 400); // Círculo del radar

  // Calcular el ángulo (ajusta según sea necesario)
  float angle = map(distancia, 0, 400, 0, TWO_PI); // Mapea la distancia a un ángulo
  float x = 200 * cos(angle); // Coordenada x
  float y = 200 * sin(angle); // Coordenada y

  // Dibuja la línea del radar
  stroke(255, 0, 0); // Color rojo para la línea
  line(0, 0, x, y); // Dibuja la línea hacia la distancia medida

  // Mostrar la distancia en pantalla
  fill(0);
  textSize(32);
  textAlign(CENTER);
  text("Distancia: " + distancia + " cm", 0, 220);
}

