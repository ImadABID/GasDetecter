//teste de moteur
#define IN1 2         //IN1 => Fermer
#define IN2 3         //IN2  => Ouvrir
#define EN_A 9 


#include <Servo.h>
#define SERVO_PIN 6   //pin de Servo moteur
Servo vanne;
void setup() {
  vanne.attach(SERVO_PIN);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN_A,OUTPUT);

  vanne.write(15);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(EN_A,255);
  delay(1000);
  analogWrite(EN_A,0);

 delay(1000);

  vanne.write(170);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(EN_A,255);
  delay(1000);
  analogWrite(EN_A,0);

}

void loop() {
  analogWrite(EN_A,255);

  /*
  delay(1000);

  digitalWrite(M_G,HIGH);
  digitalWrite(M_D,LOW);
  analogWrite(EN_PIN_M,170);
  delay(1000);
  analogWrite(EN_PIN_M,0);*/
  

}
