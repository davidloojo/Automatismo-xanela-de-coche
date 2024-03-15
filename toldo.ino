/* TOLDO
 Por tanto, o funcionamento actual da montaxe será como se indica a seguir: 
 (a) ao iniciar o programa o toldo recóllese, 
 (b) ao premer o pulsador unha vez, actívase ou desactívase o motor en correspondencia co estado actual do sistema, 
 (c) o motor permanece activo até que o fin de carreira correspondente detecta a chegada do toldo, momento no que o motor para, 
 (d) en calquera momento intermedio, o pulsador pode parar o toldo (unha pulsación) ou invertir o movemento (seguinte pulsación), 
 (e) cando o motor se está movendo, a velocidade ven dada polo sensor de luminosidade. 
 Por suposto, os FCs só interveñen en detectar a posición nos extremos do percorrido, non teñen efecto no resto dos casos. É dicir: se o toldo prega, o fin de carreira de despregado non ten ningún efecto, e se desprega o fin de carreira de pregado non afecta ao movemento. 
 Polo de agora non se detectan pulsacións longas e o sensor de luminosidade non pode parar ou invertir o movemento. Tampouco é válido usar o criterio dos 7 s.
*/

// Autor: David Lojo Fernández 
// Fecha: Marzo de 2024

//Pins E/S
#define FinalCarreira1 12      //Final de carrera superior
#define FinalCarreira2 9    //Final de carrera inferior
#define PULSADOR1 13   //  Pulsador de control
#define BajVentana 5    // Pin para que el motor baje la ventana
#define SubVentana 6   // Pin para que el motor suba la ventana
#define Activacion 3  // Pin para alimentar el motor

int estado = 0;     // Variable para el estado del botón
int Direccion = 1;  // Variable para la dirección del movimiento de la ventana
bool run = false;   // Variable para el estado de ejecución del motor
int valor = 0;      // Variable para almacenar el valor de la fotoresistencia
int fuerza = 0;     // Variable para la fuerza del motor basada en la lectura de la fotoresistencia

void setup() {
  pinMode(FinalCarreira1, INPUT);      // Configura el pin FinalCarreira1 como entrada
  pinMode(FinalCarreira2, INPUT);     // Pin FinalCarreira2 como entrada
  pinMode(PULSADOR1, INPUT);    // Pin del botón como entrada
  pinMode(SubVentana, OUTPUT);  // Pin de subir la ventana como salida
  pinMode(BajVentana, OUTPUT);   //Pin de bajar la ventana como salida
  Serial.begin(9600);       // Inicia la comunicación serial a 9600 baudios
}

void loop() {
  valor = analogRead(A0);   // Lee el valor de la fotoresistencia

  // Introduce el valor de la fotoresistencia en un rango de 0 a 5
  int resultado = map(valor, 6, 679, 0, 5);
  Serial.println(resultado);  // Imprime el resultado en el monitor serial

  if (resultado == 0) {
    fuerza = 12;
  }
  if (resultado == 1) {
    fuerza = 51;
  }
  if (resultado == 2) {
    fuerza = 102;
  }
  if (resultado == 3) {
    fuerza = 153;
  }
  if (resultado == 4) {
    fuerza = 204;
  }
  if (resultado == 5) {
    fuerza = 255;
  }
//Dependiendo del valor empleado el motor girara más rápido
  analogWrite(Activacion, fuerza);  
  while (digitalRead(PULSADOR1)) {
    estado = HIGH;  //El estado del motor es alto
  }

  if (estado == HIGH) {
    // Si el motor está en ejecución, detenlo y cambia la dirección
    if (run == true) {
      analogWrite(SubVentana, 0);  // Detiene el motor de subir
      analogWrite(BajVentana, 0);   // Detiene el motor de bajar
      run = false;              //Estado de ejecución como falso
      Direccion *= -1;         // Cambia la dirección
    } else {
      // Si el motor no está en ejecución, comienza a moverse en la dirección actual
      if (Direccion == 1) {
        digitalWrite(SubVentana, 1);  // Mueve el motor hacia arriba
      } else {
        digitalWrite(BajVentana, 1);   //Mueve el motor hacia abajo
      }
      run = true;                // Establece el estado de ejecución como verdadero
    }
    estado = LOW;  // Establece el estado como bajo
  }

  if (digitalRead(FinalCarreira1) && Direccion == 1) {
    digitalWrite(SubVentana, 0);  // Detiene el motor de subir
    run = false;               //Estado de ejecución como falso
    Direccion *= -1;          // Cambia la dirección
  }

  if (digitalRead(FinalCarreira2) && Direccion == -1) {
    digitalWrite(BajVentana, 0);   // Detiene el motor de bajar
    run = false;              //Estado de ejecución como falso
    Direccion *= -1;         // Cambia la dirección
  }
}
