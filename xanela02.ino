/* 
* O programa imita o funcionamento dunha xanela dun coche.
* Con un pulsador ao pulsar inicia un motor e ao volver a pulsar para o mesmo para que a o volver a pulsar inicie o outro motor.
* Os outros dous pulsadores imitan dous finales de carreira de cada motor, 
* ao premer unha vez para o motor correspondente e ao iniciar co pulsador normal comeza o outro motor a moverse.
*
* Autor: David Lojo Fernández
* Data: Marzo de 2024
*/

// Declarar entradas e saídas
const int pinEntrada = 13;
const int pinSalida1 = 8;
const int pinSalida2 = 7;
const int pinFinal1 = 11;
const int pinFinal2 = 12;


// Declarar variables globais
int estadoEntradaAnterior = LOW;
int salidaActiva = 0;
int estadoEntrada = 0;
int direccion = 0;
int valorPinFinal1 = 0;
int valorPinFinal2 = 0;

void setup() {
  pinMode(pinEntrada, INPUT);
  pinMode(pinFinal1, INPUT);
  pinMode(pinFinal2, INPUT);
  
  pinMode(pinSalida1, OUTPUT);
  pinMode(pinSalida2, OUTPUT);
 
  } 

void loop() {
  // Lectura do pulsador
  valorPinFinal1 = digitalRead(pinFinal1);
  valorPinFinal2 = digitalRead(pinFinal2);
  
  while(digitalRead(pinEntrada)){
    estadoEntrada = 1;
  }
  
  if (estadoEntrada){ // Si se detecta unha pulsación
    estadoEntrada = 0; // Resetea valor do pulsador
  if (salidaActiva) { // Revisa si se moven as vidrios
    direccion = !direccion; // Cambia a dirección
      
    digitalWrite(pinSalida1, LOW); // Apáganse os dous motores
    digitalWrite(pinSalida2, LOW);
      
    salidaActiva = 0; // Indica que non se move o vidrio
  } else { 
     salidaActiva = 1; // Indica que móvese o vidrio
    
    if (direccion) { // Dirección = 1 [arriba]
      digitalWrite(pinSalida1, HIGH); // Encéndese un motor
    } else { // Se non, abaixo
      digitalWrite(pinSalida2, HIGH); // Encéndese o outro motor
    }
   } 
 }   
  
  if (valorPinFinal1) { // Si se detecta a pulsación do FDC
    direccion = 0; // Cámbiase a dirección
    salidaActiva = 0; // Indica que déixase de mover a ventana
    digitalWrite(pinSalida1, LOW); // Apágase o motor
  }
   
  if (valorPinFinal2) { // Si se detecta a pulsación do FDC
    direccion = 1; // Cámbiase a dirección
    salidaActiva = 0; // Indica que déixase de mover a ventana
    digitalWrite(pinSalida2, LOW); // Apágase o motor
  }
  
  delay(10);
  
    estadoEntradaAnterior = estadoEntrada;
}
   
