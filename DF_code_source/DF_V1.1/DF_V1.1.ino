/*********Détecteur de fummé*********************
 * Classe: 2STM
 * Version: 1.1
 * Date: 08/03/2018
 * Heure: 23h00 
 ************************************************/
#include <Servo.h>

//************ OUTPUT ******************
#define LED_R 5 
#define LED_G 7
#define BUZER 8

#define IN1 3         //IN1 => Fermer
#define IN2 2         //IN2  => Ouvrir
#define EN_A 9      //Pin de moteur

#define EN_B 10      //Pin de ventilateur
#define IN3 11
#define IN4 12
//Les autres entrées(Sens1,Sense2) de ventilateur sont branchés avec (Vcc, GND)
//Car il a un seul sens de rotation.

#define SERVO_PIN 6   //pin de Servo moteur
Servo vanne;

/************** INPUT ******************/
#define MQ2 A0

/*********** PARAMETRES ****************/
#define F_HZ 800
#define VALEUR_GASE_EXSISTE_MIN 440
#define VALEUR_GASE_EXSISTE_MAX 480
#define EN_VALUE_OPENING 200
#define EN_VALUE_CLOSING 120
#define DELAY 100
#define OPENING_WINDOW_DELAY 900
#define SERVO_MAX 170
#define SERVO_MIN 15

/*********** Var globales ****************/
bool first_Time_if=true;


void setup() {
  Serial.begin(9600);
  vanne.attach(SERVO_PIN);
  
  pinMode(BUZER,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN_A,OUTPUT);

  pinMode(IN3,OUTPUT); digitalWrite(IN3,HIGH);
  pinMode(IN4,OUTPUT); digitalWrite(IN4,LOW);
  pinMode(EN_B,OUTPUT);

  pinMode(MQ2,INPUT);

  pinMode(13,OUTPUT); digitalWrite(13,HIGH);

  digitalWrite(LED_G,HIGH);
  digitalWrite(LED_R,LOW);
}

void loop() {
  Serial.println(analogRead(MQ2));
  if(analogRead(MQ2)>=VALEUR_GASE_EXSISTE_MAX && first_Time_if){Serial.println("Gaz existe");
    first_Time_if=false;
//Ventilateur en marche  
    digitalWrite(EN_B,HIGH);

    tone(BUZER,F_HZ);
    digitalWrite(LED_G,LOW);
    digitalWrite(LED_R,HIGH);

//fermeture de vanne & Overture de fenetre
  
  Serial.println("OPENING");
  vanne.write(SERVO_MIN);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(EN_A,255);
  delay(OPENING_WINDOW_DELAY);
  analogWrite(EN_A,0);
   
    
  }if(analogRead(MQ2)<VALEUR_GASE_EXSISTE_MIN && !first_Time_if){Serial.println("Gaz dont existe");
    first_Time_if=true;

//Ventilateur en arret
    digitalWrite(EN_B,LOW);
    
    noTone(BUZER);
    digitalWrite(LED_G,HIGH);
    digitalWrite(LED_R,LOW);

//overture de vanne & Fermeture de fenetre
  vanne.write(SERVO_MAX);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(EN_A,255);
  delay(OPENING_WINDOW_DELAY);
  analogWrite(EN_A,0);
  }
  
  delay(DELAY);
}


