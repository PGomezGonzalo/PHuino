// initialization of the variables


int phmeters_number; // Up to 4 pH-meters are supported in this program.

unsigned long timer; // Time variable to adjust the workflow 

const int pHAnPin[4] = {A0, A1, A2, A3};  // Each pH-meter has an analog imput. 
                                          // FUTURE WORK: Improve measure through voltage normalization
const int pHDigPin[4] = {2,3,4,5};

// Variables for operation
float pH_Control[4] = {6,6,6,6}; // Target pH value. An electrovalve should be open if needed.
float m[4];   // pH = m * (measure) + n
float n[4];
float pH_Value[4]; //pH value: from 0[-] to 14[-]
float tolerance = 0.01; // Between 0 and 1, should be a value of a minimun variable change to asume is stabilized


// Variables for calibration
float pH_Digital;  // pH value: from 0[-] to 1023[-] 

float Patron_1_pH;   // First known ph point 
float Patron_1_Dig;  // First digital point, for calibration purposes

float Patron_2_pH;   // Second known ph point
float Patron_2_Dig;  // Second digital point, for calibration purposes


// Auxiliar variables
float temp1; // Used to momentarily save some values

void setup() {
Serial.begin(9600);

Serial.print("Number of pH-meters?: \n");
while (Serial.available() == 0);
phmeters_number = Serial.parseInt();
while(phmeters_number > 4 || phmeters_number < 1) 
{
  Serial.print("Please, the number of pH-meteres should be between 1 and 4. Enter a new value: \n");
  while (Serial.available() == 0);
  phmeters_number = Serial.parseInt();
}

InizialicePHmeters(phmeters_number, pHDigPin); // Set the pins in digital, low mode.

for (int i=0; i<phmeters_number; i++){
// ---------------------------
//  NOTA: NO ESTAMOS INCLUYENDO 
//  ESTABILIZACIÓN DE LOS PUNTOS
// ---------------------------
  
  Serial.println((String)"Calibration of pHmeter number "+i+" :");
  Serial.print("Enter first calibration pH: \n");
  while (Serial.available() == 0);
  Patron_1_pH = Serial.parseFloat();
  Patron_1_Dig = ReadPh(pHAnPin[i]) ;
  Serial.println(Patron_1_pH);
   
  Serial.print("Enter second calibration pH: \n");
  while (Serial.available() == 0);
  Patron_2_pH = Serial.parseFloat(); 
  Patron_2_Dig = ReadPh(pHAnPin[i]);
  Serial.println(Patron_2_pH);
  delay(500);
  
  m[i] = (Patron_2_pH - Patron_1_pH)/(Patron_2_Dig - Patron_1_Dig);
  n[i] = Patron_1_pH-m[i]*Patron_1_Dig;
}
}

void loop() {
timer = millis();

Serial.print("\n");
Serial.print(timer);
for (int i=0; i<phmeters_number; i++){
  pH_Value[i]=m[i]*ReadPh(pHAnPin[i])+n[i];
  Serial.print(pH_Value[i]);
}
// Serial.print(pH_Value);

for (int i=0; i<phmeters_number; i++){
  if(pH_Value[i]>pH_Control[i]){
    digitalWrite(pHDigPin[i], HIGH);
    delay(1500);       // miliseconds the electrovalve should be open to correct pH. 
    digitalWrite(pHDigPin[i], LOW);
  }
}

while((timer+10000)<millis());
}



void InizialicePHmeters(int number, int pin[4]){ // Inizialice the required number of pins to an output, low mode. 
  for (int i=0; i < number; i++){
    pinMode(pin[i], OUTPUT); // pin is set to digital output
    digitalWrite(pin[i], LOW); // Starts in LOW mode
  }
}

 float ReadPh(int pin){ //Take 5 measures in a second a return the mean value
  float temp;
  for (int i=0; i<5;i++){ 
    temp += analogRead(pin);
    delay(200);
  }
  return(temp/5);
}
