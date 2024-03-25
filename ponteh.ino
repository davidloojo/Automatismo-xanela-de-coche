/*
    Simulación de puente H con relés

    Descripción:
    Este programa controla un motor de corriente continua (CC) utilizando un puente H simulado con relés en TinkerCAD.
    Los relés S1, S2, S3 y S4 se activan o desactivan mediante los pines 8, 9, 10 y 11 de una placa Arduino.
    La alimentación del circuito se proporciona desde una pila de 9V.
    La velocidad del motor CC se regula mediante un potenciómetro independiente de la placa Arduino.
    Se conectan microinterruptores a los pines 4, 5, 6 y 7 de la placa Arduino para controlar el sentido de giro del motor.
    Se garantiza la protección de la placa Arduino para evitar que circulen más de 20 mA por los pines de entrada.

    Pinout:
    - Pins de entrada (microinterruptores): 4, 5, 6, 7
    - Pins de salida (relés): 8, 9, 10, 11

    Funcionamiento:
    El programa verifica el estado de los microinterruptores para determinar el sentido de giro del motor.
    Luego, activa o desactiva los relés correspondientes según el sentido de giro y la combinación de entradas segura para evitar cortocircuitos.
    La velocidad del motor se ajusta utilizando el potenciómetro.

    Autor: [David Lojo Fernández]
*/

// Definición de pines
#define pinS1 8
#define pinS2 9
#define pinS3 10
#define pinS4 11
#define pinMicro1 4
#define pinMicro2 5
#define pinMicro3 6
#define pinMicro4 7

void setup() {
  // Configurar pines de salida para relés
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinS4, OUTPUT);

  // Configurar pines de entrada para microinterruptores
  pinMode(pinMicro1, INPUT_PULLUP);
  pinMode(pinMicro2, INPUT_PULLUP);
  pinMode(pinMicro3, INPUT_PULLUP);
  pinMode(pinMicro4, INPUT_PULLUP);
}

void loop() {
  // Leer el estado de los microinterruptores
  int micro1 = digitalRead(pinMicro1);
  int micro2 = digitalRead(pinMicro2);
  int micro3 = digitalRead(pinMicro3);
  int micro4 = digitalRead(pinMicro4);

  // Determinar el sentido de giro del motor
  bool sentidoHorario = micro1 && !micro2 && !micro3 && micro4;
  bool sentidoAntihorario = !micro1 && micro2 && micro3 && !micro4;

  // Verificar el sentido de giro y activar los relés correspondientes
  if (sentidoHorario) {
    digitalWrite(pinS1, HIGH);
    digitalWrite(pinS2, LOW);
    digitalWrite(pinS3, LOW);
    digitalWrite(pinS4, HIGH);
  } else if (sentidoAntihorario) {
    digitalWrite(pinS1, LOW);
    digitalWrite(pinS2, HIGH);
    digitalWrite(pinS3, HIGH);
    digitalWrite(pinS4, LOW);
  } else {
    // Detener el motor si no se detecta un sentido de giro válido
    digitalWrite(pinS1, LOW);
    digitalWrite(pinS2, LOW);
    digitalWrite(pinS3, LOW);
    digitalWrite(pinS4, LOW);
  }
}
