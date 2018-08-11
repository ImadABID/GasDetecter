/*********Détecteur de fummé*********************
 * Classe: 2STM
 * Version: 0.0
 * Date: 6/03/2018
 * Heure: 17h00 
 ************************************************/

 
#include <Servo.h> 

typedef enum {
  Closed,
  Opened,
  Midel  
}ETAT;

/*************Prorto type de fonctions*****************/
ETAT Window_Etat();

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
#define C1 A1 //C1=HIGH => Window Closed
#define C2 A2

/*********** PARAMETRES ****************/
#define F_HZ 440
#define VALEUR_GASE_EXSISTE 400
#define EN_VALUE 255  //La vitesse de moteur et de vontilateur est constat
#define DELAY 100

void setup() {
  Serial.begin(9600);
  vanne.attach(SERVO_PIN);
  
  pinMode(BUZER,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  
  pinMode(M_G,OUTPUT);
  pinMode(M_D,OUTPUT);
  pinMode(EN_PIN_M,OUTPUT);
  pinMode(EN_PIN_V,OUTPUT);

  pinMode(MQ2,INPUT);
  pinMode(C1,INPUT);
  pinMode(C2,INPUT);

  digitalWrite(LED_G,HIGH);
}

void loop() {

  Serial.println(analogRead(MQ2));
  if(analogRead(MQ2)>=VALEUR_GASE_EXSISTE){

    tone(BUZER,F_HZ);
    
    digitalWrite(LED_G,LOW);
    digitalWrite(LED_R,HIGH);

    // 0 degree => vanne fermmé.  180 => vanne overt
    vanne.write(0);

    if(Window_Etat()==Closed){
      digitalWrite(M_G,HIGH);
      digitalWrite(M_D,LOW);
      while(Window_Etat()!=Opened){
        analogWrite(EN_PIN_M,EN_VALUE);
      }
      analogWrite(EN_PIN_M,0);
    }

    digitalWrite(EN_PIN_V,HIGH);
   
    
  }else{
    noTone(BUZER);
    
    digitalWrite(LED_G,HIGH);
    digitalWrite(LED_R,LOW);

    // 0 degree => vanne fermmé.  180 => vanne overt
    vanne.write(180);

    if(Window_Etat()==Opened){
      digitalWrite(M_G,LOW);
      digitalWrite(M_D,HIGH);
      while(Window_Etat()!=Closed){
        analogWrite(EN_PIN_M,EN_VALUE);
      }
      analogWrite(EN_PIN_M,0);
    }

    digitalWrite(EN_PIN_V,LOW);
  
  }

  delay(DELAY);
}


ETAT Window_Etat(){
  if(digitalRead(C1)==HIGH) return Closed;
  if(digitalRead(C2)==HIGH) return Opened;
  return Midel;
}



