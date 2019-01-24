void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT); // Indico que pin 2 es salida
  digitalWrite(2, LOW); // Valor inicial = LOW

  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(1500);
  digitalWrite(2, LOW);
  delay(500);
}
