#define MQ2 A0


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MQ2,INPUT);

}

void loop() {
  Serial.println("\n");
  Serial.print("La valeur de MQ2:"); Serial.print(analogRead(MQ2));
  delay(100);
  
}

