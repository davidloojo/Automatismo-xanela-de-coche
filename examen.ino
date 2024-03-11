// Definir los pines del potenciómetro y el LED RGB
int POT = A0;
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int nivel = -1;
unsigned long nCores = (unsigned long) 256*256*256;
unsigned long colorValue = -1;
void setup() {
  // Inicializar el monitor serie
  Serial.begin(9600);
}

void loop() {
  // Leer el valor del potenciómetro
  int potValue = analogRead(POT);

  // Mapear el valor del potenciómetro al rango de 16250 a 75000
POT = analogRead(POT);
nivel = map(POT, 0, 1023, 0, 5);

colorValue = map(nivel, 0, 5, 0, nCores-1);

Serial.print("colorValue:"); Serial.println(colorValue);
  
POT = analogRead(POT);
nivel = map(POT, 0, 1023, 0, 4);

  // Calcular los componentes RGB en función del valor del potenciómetro
  int red = (colorValue >> 16) & 0xFF;
  int green = (colorValue >> 8) & 0xFF;
  int blue = colorValue & 0xFF;

  // Encender el LED RGB con los componentes calculados
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);

  // Imprimir los valores en el monitor serie
  Serial.print("Decimal: ");
  Serial.print(colorValue);
  Serial.print("\tHexadecimal: 0x");
  Serial.print(colorValue, HEX);
  Serial.print("\tBinario: ");
  Serial.println(colorValue, BIN);

  // Esperar un breve tiempo para evitar lecturas rápidas del potenciómetro
  delay(100);

  switch (nivel) {
    case 0:
     setVermello();
     break;
    case 1:
     setAmarelo();
     break;
    case 2:
     setVerde();
     break;
    case 3:
     setAzul();
     break;
    case 4:
     setBranco();
     break;
  }
}

// Función auxiliares
void setVermello() {
setColor(255, 0, 0);
}

void setVerde() {
setColor(0, 255, 0);
}

void setAmarelo() {
setColor(255, 191, 0);
}

void setAzul() {
setColor(0, 0, 255);
}

void setColor(int vermello, int verde, int azul) {
analogWrite(redPin, vermello);
analogWrite(greenPin, verde);
analogWrite(bluePin, azul);
}


void setBranco() {
setColor(255, 255, 255);
}
void setRGBoff() {
setColor(0, 0, 0);
}
