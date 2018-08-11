/*********Détecteur de fummé*********************
 * Classe: 2STM
 * Version: 1.0
 * Date: 7/03/2018
 * Heure: 10h00 
 ************************************************/
#include <Servo.h> 

//************ OUTPUT ******************
#define LED_R 5 
#define LED_G 7
#define BUZER 8

#define M_G 2         //LE sense gauche de moteur => Fermer
#define M_D 3         //LE sense droit de moteur  => Ouvrir
#define EN_PIN_M 9      //Pin de moteur

#define EN_PIN_V 10      //Pin de vontilateur
//Les autres entrées(Sens1,Sense2) de ventilateur sont branchés avec (Vcc, GND)
//Car il a un seul sens de rotation.

#define SERVO_PIN 6   //pin de Servo moteur
Servo vanne;

/************** INPUT ******************/
#define MQ2 A0

/*********** PARAMETRES ****************/
#define F_HZ 440
#define VALEUR_GASE_EXSISTE 500
#define EN_VALUE 255  //La vitesse de moteur et de vontilateur est constat
#define DELAY 100
#define OPENING_WINDOW_DELAY 3000

/*********** Var globales ****************/
bool first_Time_if=true;
bool first_Time_else=true;
void setup() {
  
  vanne.attach(SERVO_PIN);
  
  pinMode(BUZER,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  
  pinMode(M_G,OUTPUT);
  pinMode(M_D,OUTPUT);
  pinMode(EN_PIN_M,OUTPUT);
  pinMode(EN_PIN_V,OUTPUT);

  pinMode(MQ2,INPUT);

  digitalWrite(LED_G,HIGH);
}

void loop() {
  if(analogRead(MQ2)>=VALEUR_GASE_EXSISTE && first_Time_if){
    first_Time_if=false;
    first_Time_else=true;

//Ventilateur en marche  
    digitalWrite(EN_PIN_V,HIGH);

    tone(BUZER,F_HZ);
    digitalWrite(LED_G,LOW);
    digitalWrite(LED_R,HIGH);

 //fermeture de vanne
    vanne.write(15); /*0 degree => vanne fermmé.  180 => vanne overt*/

//Overture de fenetre
    digitalWrite(M_G,HIGH);
    digitalWrite(M_D,LOW);
    analogWrite(EN_PIN_M,EN_VALUE);
    delay(OPENING_WINDOW_DELAY);
    analogWrite(EN_PIN_M,0);
   
    
  }if(analogRead(MQ2)<VALEUR_GASE_EXSISTE && first_Time_else){
    first_Time_if=true;
    first_Time_else=false;

//Ventilateur en arret
    digitalWrite(EN_PIN_V,LOW);
    
    noTone(BUZER);
    digitalWrite(LED_G,HIGH);
    digitalWrite(LED_R,LOW);

//overture de vanne
    vanne.write(170);/*0 degree => vanne fermmé.  180 => vanne overt*/

//Fermeture de fenetre
    digitalWrite(M_G,LOW);
    digitalWrite(M_D,HIGH);
    analogWrite(EN_PIN_M,EN_VALUE);
    delay(OPENING_WINDOW_DELAY);
    analogWrite(EN_PIN_M,0);


  
  }

  delay(DELAY);
}


