unsigned long timer; // Time variable to adjust the workflow 
unsigned long mydelay = 1000;
unsigned long ratio = 3000;
unsigned long rest = 250;
int bla;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer = millis();
  while((timer + mydelay)> millis())

  if(((timer+mydelay)%ratio) < rest){
    delay(1000);
  }
  
  Serial.print("   ");
  Serial.print(timer);
  Serial.print("   ");
  Serial.println(millis());
}
