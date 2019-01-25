// initialization of the variables


int phmeters_number; // Up to 4 pH-meters are supported in this program.

const int pHAnPin[4] = {A0, A1, A2, A3};  // Each pH-meter has an analog imput. 
                                          // FUTURE WORK: Improve measure through voltage normalization
const int pHDigPin[4] = {2,3,4,5};

// Variables for operation
float pH_Control[4]; // Target pH value. An electrovalve should be open if needed.
float m[4];   // pH = m * (measure) + n
float n[4];
float pH_Value[4]; //pH value: from 0[-] to 14[-]
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

InizialicePHmeters(phmeters_number, pHDigPin); // Set the pins in digital, low mode.

for (int i=0; i<phmeters_number; i++){
  Serial.println((String)"Enter "+i+" calibration pH:");

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



void InizialicePHmeters(int number, int pin[4]){
  for (int i=0; i < number; i++){
    pinMode(pin[i], OUTPUT); // pin is set to digital output
    digitalWrite(pin[i], LOW); // Starts in LOW mode
  }
}
