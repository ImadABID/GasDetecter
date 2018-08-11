#define BUZER 8
void setup() {

  pinMode(BUZER,OUTPUT);

}

void loop() {

  tone(BUZER,800);
  delay(100);
  noTone(BUZER);
  delay(100);

}
