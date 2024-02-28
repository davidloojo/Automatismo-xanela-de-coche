/* 
* O programa imita o funcionamento dunha xanela dun coche.
* Ao premer o botón unha vez acenderá un motor que leva o vidrio hacia arriba,
* e ao premer unha segunda vez levará o vidrio cara a abaixo.
*
* Autor: David Lojo Fernández
* Data: Febreiro de 2024
*/

// Declarar entradas e saídas
#define vidrioUP   11
#define vidrioDOWN 12 
#define PULS        7

// Declarar variables globais
bool estado = 0;
int contador = 0; // Contador para o número de impulsos ao motor

void setup() {
  pinMode(vidrioUP, OUTPUT);
  pinMode(vidrioDOWN, OUTPUT);
  pinMode(PULS, INPUT);
  Serial.begin(9600);
  int estado;
  Serial.println(estado);
}

void loop() {
  // Lectura do pulsador
  if(digitalRead(PULS)) {
    estado = !estado; 
    contador = 100;
    while(digitalRead(PULS)) {
      delay(20);
    }
  }
  // Fin da lectura do pulsador
  
  Serial.print("valor do contador: ");
  Serial.println(contador);
  
  // Accionamiento dos motores
  if(contador > 0) {
    if(estado == 0) {
      digitalWrite(vidrioUP, HIGH);
      digitalWrite(vidrioDOWN, LOW);
      delay(70);
      contador--;
    }
    else {
      digitalWrite(vidrioUP, LOW);
      digitalWrite(vidrioDOWN, HIGH);
      delay(70);
      contador--;
    }
  }
  else {             // Se non está o motor accionado, lee botón 10 veces/s
    delay(100);
  }
  // Fin de accionamentos dos motores
  delay(7);
  if (contador == 0) {
    digitalWrite(vidrioUP, LOW);
    digitalWrite(vidrioDOWN, LOW);
  }
}
