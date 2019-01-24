// initialization of the variables


int phmeters_number; // Up to 4 pH-meters are supported in this program.

const int pHAnPin1 = A0;  // Each pH-meter has an analog imput. 
const int pHAnPin2 = A1;  // FUTURE WORK: Improve measure through voltage normalization
const int pHAnPin3 = A2;
const int pHAnPin4 = A3;

const int pHDigPin1 = 2;
const int pHDigPin2 = 3;
const int pHDigPin3 = 4;
const int pHDigPin4 = 5;

// Variables for operation
float pH_Control1,pH_Control2,pH_Control3,pH_Control4;  // Target pH value. An electrovalve should be open if needed.
float m1, m2, m3, m4;   // pH = m * (measure) + n
float n1, n2, n3, n4;
float pH_Value1, pH_Value2, pH_Value3, pH_Value4; //pH value: from 0[-] to 14[-]
float tolerance = 0.01; // Between 0 and 1, should be a value of a minimun variable change to asume is stabilized


// Variables for calibration
float pH_Digital;  // pH value: from 0[-] to 1023[-] 
float pH_Voltage;  // pH value: from 0[V] to 5[V]


float Patron_1_pH; // First known ph point 
float Patron_1_V;  // First voltage point, for calibration purposes

float Patron_2_V;   // Second known ph point
float Patron_2_pH;  // Second voltage point, for calibration purposes


// Auxiliar variables
float temp1; // Used to momentarily save some values

void setup() {
Serial.begin(9600);

Serial.print("Number of pH-meters?: ");
while (Serial.available() == 0);
phmeters_number = Serial.parseInt();
while(phmeters_number > 4 || phmeters_number < 1) 
{
  Serial.print("Please, the number of pH-meteres should be between 1 and 4. Enter a new value:");
  while (Serial.available() == 0);
  phmeters_number = Serial.parseInt();
}

pinMode(pHDigPin1, OUTPUT); // First digital output
digitalWrite(pHDigPin1, LOW); // Starts in LOW mode

if(phmeters_number > 1)
{
  pinMode(pHDigPin2, OUTPUT); // Second digital output (only if needed)
  digitalWrite(pHDigPin2, LOW); // Starts in LOW mode
}

if(phmeters_number > 2)
{
  pinMode(pHDigPin3, OUTPUT); // Third digital output (only if needed)
  digitalWrite(pHDigPin3, LOW); // Starts in LOW mode
}

if(phmeters_number > 3)
{
  pinMode(pHDigPin4, OUTPUT); // Third digital output (only if needed)
  digitalWrite(pHDigPin4, LOW); // Starts in LOW mode
}

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
