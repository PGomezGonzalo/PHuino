// initialization of the variables

const int pHSensorPin = A0;

int pH_Digital;
float pH_Voltage;
float pH_Control;

float Patron_1_V; 
float Patron_1_pH;

float Patron_2_V;
float Patron_2_pH;

float m;
float n;
float pH_Value;


void setup() {
Serial.begin(9600);
pinMode(2, OUTPUT); // Indico que pin 2 es salida
digitalWrite(2, LOW); // Valor inicial = LOW
pH_Control = 5;

//Patron_1_V = 3.24;
//Patron_1_pH = 4.0;

//Patron_2_V = 2.81;
//Patron_2_pH = 7.00;

Serial.print("Enter first calibration pH: ");
while (Serial.available() == 0);
Patron_1_pH = Serial.parseFloat();
Serial.println(Patron_1_pH);
pH_Digital = analogRead(pHSensorPin);
Patron_1_V = 5*pH_Digital/1024.0;
delay(500);

Serial.print("Enter second calibration pH: ");
while (Serial.available() == 0);
Patron_2_pH = Serial.parseFloat(); 
pH_Digital = analogRead(pHSensorPin);
Patron_2_V = 5*pH_Digital/1024.0;
Serial.println(Patron_2_pH);
delay(500);

}

void loop() {

pH_Digital = analogRead(pHSensorPin);
pH_Voltage = 5*pH_Digital/1024.0;
m = (Patron_2_pH - Patron_1_pH)/(Patron_2_V - Patron_1_V);
n = Patron_1_pH-m*Patron_1_V;
pH_Value = pH_Voltage*m + n;

Serial.print("pH Digital Read: ");
Serial.println(pH_Digital);
delay(500);
Serial.print("pH Voltage: ");
Serial.println(pH_Voltage, 2);
delay(500);
Serial.print("pH Value: ");
Serial.println(pH_Value, 2);
Serial.println(" ");

if (pH_Value > pH_Control){
  digitalWrite(2, HIGH);
  Serial.println(" -- Readjusting pH -- ");
  Serial.println(" ");
  delay(250);
  digitalWrite(2, LOW);
  delay(2000);
}

delay(2000);

}

